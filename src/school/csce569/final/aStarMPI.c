/*   Parallel aStar algorithm
 * 
 *   Jonathan Chandler
 *
 *   April, 2009
 *
 *   Used struct sending algorithm from:
 *   http://t3as3r.wordpress.com/2008/11/10/sending-structures-containing-variable-length-arrays-with-mpi/
 */


#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>


typedef struct aStarNode aStarNode;
typedef struct heapNode heapNode;

const int DIMENSION = 1000;
enum{OPEN, CLOSED};
const int DIRS = 8;
const int DIR[][2] = {
   {1, 0},
   {1, 1},
   {0, 1},
   {-1, 1},
   {-1, 0},
   {-1, -1},
   {0, -1},
   {1, -1}
};


enum{ORTH, DIAG};
const int MOVE_COST[] = {1, M_SQRT2};

enum{X, Y, VALUE};
enum{false, true};

const int MAX_PROCS = DIRS + 1;
const int ROOT = 0;
enum{ADD, REPLACE, UPDATE, DELETE, SHUTDOWN, NOTHING};  // Tags
const char* tagName[] = {"add", "replace", "update", "delete", "shutdown", "nothing"};


int procs, rank;
MPI_Status status;

int buffer[3];
int nodeCount;
heapNode* head;
heapNode* tail;


struct aStarNode{
   int inProc;
   int loc[2];
   int priority;
   int estimate;
   int distance;
   int status;
   aStarNode* parent;
};

struct heapNode{
   heapNode* parent;
   heapNode* left;
   heapNode* right;
   int data[3];
};


void master();
void slave();

int min(int, int);
int findEstimate(int, int, int, int);
void printPath(aStarNode*);

void sendMsg(aStarNode*, int, int, int);
void recieveMsg();

void push();
void pushSub(heapNode*);
void replace(heapNode*);
int update(heapNode*);
void pop();
void popSub(heapNode*);
void reheap(heapNode*);
void freeMem(heapNode*);

void swap(heapNode*, heapNode*);
void shiftUp(heapNode*);
void shiftDown(heapNode*);



int main(int argc, char* argv[]){
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &procs);

   if(procs == 1)
      printf("Program must use at least 2 processors\n");
   else{
      if(rank == 0){
         if(procs > MAX_PROCS){
            printf("Only %i processes allowed, remaining will not be used\n", MAX_PROCS);
            procs = MAX_PROCS;
         } 
         master();
      }
      else if(rank < MAX_PROCS)
         slave();
   }

   MPI_Finalize();
   return 0;
}


void master(){
   int i;

   //Read input file
   FILE* file;
   file = fopen("map.txt", "r");
   int nodes[2];
//   nodes[X] = getc(file);
//   nodes[Y] = getc(file);
   nodes[X] = nodes[Y] = DIMENSION;
   int nodeCost[nodes[X]][nodes[Y]];
   for(i = 0; i < nodes[X]; i++){
      for(int j = 0; j < nodes[Y]; j++)
         nodeCost[i][j] = getc(file);
   }
   fclose(file);
   printf("Map size:  %ix%i\n\n", nodes[X], nodes[Y]);
  
   // Create node status
   aStarNode* node[nodes[X]][nodes[Y]];

   // Begin main loop - input query
   int start[2];
   int goal[2];
   while(true){      
      for(i = 0; i < nodes[X]; i++){
         for(int j = 0; j < nodes[Y]; j++)
            node[i][j] = NULL;
      }
      printf("Input start and goal nodes (x and y coordinates) or -1 to quit:");
      fflush(stdout);
      scanf("%i", &start[X]);
      if(start[X] == -1)
         break;
      scanf("%i", &start[Y]);
      scanf("%i", &goal[X]);
      scanf("%i", &goal[Y]);
      if(start[X] < 0 || start[X] >= nodes[X] || start[Y] < 0 || start[Y] >= nodes[Y])
         printf("Invalid start location (must be between 0 and %i)\n", nodes[X]-1);
      else if(goal[X] < 0 || goal[X] >= nodes[X] || goal[Y] < 0 || goal[Y] >= nodes[Y])
         printf("Invalid goal location (must be between 0 and %i)\n", nodes[Y]-1);
      else{  // Perform an A* search
         // Start timer
         double startTime = MPI_Wtime();

         // Create initial aStarNode 
         node[start[X]][start[Y]] = malloc(sizeof(aStarNode));
         aStarNode* n = node[start[X]][start[Y]];
         n->loc[X] = start[X];
         n->loc[Y] = start[Y];
         n->estimate = findEstimate(start[X], start[Y], goal[X], goal[Y]);         
         n->distance = 0;
         n->priority = n->distance + n->estimate;
         n->parent = NULL;

         // Push node to process 1
         nodeCount = 0;
         sendMsg(n, ADD, ROOT, 1); 
         n->inProc = 1;

         // Other
         int success = false;  	// boolean: if succeeded in finding goal node
         int add;		// boolean: if node was added for this direction
         int next[2];           // next node coordinates
         int diag1, diag2;      // values of diagonals
         int dist;              // distance to next node
         aStarNode* temp;       // temp node representing next node
         int changes;           // changes made (how many processes to listen for)
         int usedProc = 0;      // process that will recieve the next change
         int msg;               // message for process (add, delete, replace, etc)
         int deleted;           // boolean: if this process has deleted best node yet, disallows multiple deletions if same proc used twice+
         int count = 0;		// count of nodes iterated through, used for early outs


         recieveMsg();
         while(nodeCount != 0){                       
            changes = 0;
            deleted = false;
//            printf("\nNEW BASE NODE: %i %i from proc %i\n\n", n->loc[X], n->loc[Y], n->inProc);
//            fflush(stdout);
            //check if path was found
            if(n->loc[X] == goal[X] && n->loc[Y] == goal[Y]){
               success = true;
               break;
            }
            n->status = CLOSED;
            count++;

            //send out message to each process
            for(i = 0; i < DIRS; i++){
               add = false;
               next[X] = n->loc[X] + DIR[i][X];
               next[Y] = n->loc[Y] + DIR[i][Y];

	       changes++;
               if(next[X] >= 0 && next[X] < nodes[X] && next[Y] >= 0 && next[Y] < nodes[Y]){
                  temp = node[next[X]][next[Y]];

                  if(temp == NULL || temp->status != CLOSED){
                     // Calculate distance from root to this node
                     if(i%2 == ORTH)
                        dist = nodeCost[next[X]][next[Y]];
                     else{   //DIAG
                        // Diagonals take the hypotenuse of the two adjacent values, 
                        //  instead of the stated value
                        diag1 = (i+DIRS-1)%DIRS;
                        diag2 = (i+DIRS+1)%DIRS;
                        dist = ceil(hypotf(nodeCost[n->loc[X] + DIR[diag1][X]][n->loc[Y] + DIR[diag1][Y]],
                                           nodeCost[n->loc[X] + DIR[diag2][X]][n->loc[Y] + DIR[diag2][Y]]));
                     }
                     dist += n->distance;

                     if(temp == NULL){
                        node[next[X]][next[Y]] = malloc(sizeof(aStarNode));
                        temp = node[next[X]][next[Y]];
                        temp->loc[X] = next[X];
                        temp->loc[Y] = next[Y];
                        temp->distance = dist;
                        temp->estimate = findEstimate(next[X], next[Y], goal[X], goal[Y]);
                        temp->priority = temp->distance + temp->estimate;
                        temp->status = OPEN;
                        temp->parent = n;
                        
                        add = true;
                    }
                     else if(dist < temp->distance){ // is OPEN
                        temp->distance = dist;
                        temp->priority = temp->distance + temp->estimate;
                        temp->parent = n;

                        changes++;
                        sendMsg(temp, UPDATE, ROOT, temp->inProc);// update
                     }
                  }
                    
                  if(add){
                     if(!deleted && usedProc+1 == n->inProc){
 		        msg = REPLACE;
                        deleted = true;
                     }
                     else
                         msg = ADD;
                  }
                  else if(!deleted && usedProc+1 == n->inProc){
                     msg = DELETE;
                     deleted = true;
                  }
                  else
                     msg = NOTHING;
               }
               else if(!deleted && usedProc+1 == n->inProc){
                  msg = DELETE;
                  deleted = true;
               }
               else
                  msg = NOTHING;
              
              sendMsg(temp, msg, ROOT, usedProc+1);// nothing
              usedProc = (usedProc+1)%(procs-1); // iterates and loops through all procs besides ROOT
            }

            //recieve top nodes from each process
            n = NULL;
            for(i = 0; i < changes; i++){
               recieveMsg();

               if(buffer[X] != -1){
                  if(n == NULL){
                     n = node[buffer[X]][buffer[Y]];
                     n->priority = buffer[VALUE];
                  }
                  else{
   	             temp = node[buffer[X]][buffer[Y]];
                     temp->priority = buffer[VALUE];
       	             if(temp->priority < n->priority)
                        n = temp;
                  }
	       }
            }
         }
         if(success){
            double finish = MPI_Wtime() - startTime;
            printf("\n");
            printPath(n);
            printf("\n\n");
            printf("Path found over %i nodes in %f seconds\n", count, finish);
            fflush(stdout);
            break;
         }
      }
   }   

   // Free all data
   for(i = 1; i < procs; i++)
      sendMsg(NULL, SHUTDOWN, ROOT, i);

   for(i = 0; i < nodes[X]; i++){
      for(int j = 0; j < nodes[Y]; j++)
         free(node[i][j]);
   }
}
 

void slave(){
   // Initialize binary heap
   head = NULL;
   tail = NULL;

   // Respond to messages
   while(true){
      recieveMsg();
      int tag = status.MPI_TAG;
      if(tag == ADD)
         push();
      else if(tag == REPLACE){
         replace(head);
      }
      else if(tag == UPDATE)
         update(head);
      else if(tag == DELETE)
         pop();
      else if(tag == SHUTDOWN){
         freeMem(head);
         break;
      }
      
      // Send new top node back to root
      if(head != NULL){
         buffer[X] = head->data[X];
         buffer[Y] = head->data[Y];
         buffer[VALUE] = head->data[VALUE];
      }
      else
         buffer[X] = -1; // Root will ignore messages with this value

      MPI_Send(buffer, 3, MPI_INT, ROOT, NOTHING, MPI_COMM_WORLD);
   }
}


int findEstimate(int x1, int y1, int x2, int y2){
   int dx = abs(x1 - x2);
   int dy = abs(y1 - y2);
   return min(dx, dy)*MOVE_COST[DIAG] + abs(dx - dy)*MOVE_COST[ORTH];
}


int min(int a, int b){
   if(a > b)
      return b;
   return a;
}


void sendMsg(aStarNode* a, int tag, int from, int to){
   if(from == ROOT){
      if(tag == DELETE)
         nodeCount--;
      else if(tag == ADD){
         nodeCount++;
         a->inProc = to;
      }
      else if(tag == REPLACE)
         a->inProc = to;
   }
   if(a != NULL){
      buffer[X] = a->loc[X];
      buffer[Y] = a->loc[Y];
      buffer[VALUE] = a->priority;
   }
   MPI_Send(buffer, 3, MPI_INT, to, tag, MPI_COMM_WORLD);   
}


void recieveMsg(){
   MPI_Recv(buffer, 3, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);   
}


void printPath(aStarNode* a){
   if(a->parent != NULL)
      printPath(a->parent);
   printf("(%i, %i) -to- ", a->loc[X], a->loc[Y]);
}


void push(){
   if(head == NULL){
      head = malloc(sizeof(heapNode));
      head->data[X] = buffer[X];
      head->data[Y] = buffer[Y];
      head->data[VALUE] = buffer[VALUE];
      head->parent = NULL;
      head->left = NULL;
      head->right = NULL;
      tail = head;
   }
   else{
      if(head == tail){
         head->left = malloc(sizeof(heapNode));
         tail = head->left;
         tail->data[X] = buffer[X];
         tail->data[Y] = buffer[Y];
         tail->data[VALUE] = buffer[VALUE];
         tail->parent = head;
         tail->left = NULL;
         tail->right = NULL;
      }
      else{
         heapNode* tailParent = tail->parent;
         if(tailParent->right == NULL){
            tailParent->right = malloc(sizeof(heapNode));
            tail = tailParent->right;
            tail->data[X] = buffer[X];
            tail->data[Y] = buffer[Y];
            tail->data[VALUE] = buffer[VALUE];
            tail->parent = tailParent;
            tail->left = NULL;
            tail->right = NULL;
         }
         else
            pushSub(tail);
      }
      shiftUp(tail);
   }
}


void pushSub(heapNode* n){
   heapNode* parent = n->parent;
   if(n == parent->left){
      n = parent->right;
      while(n->left != NULL)
         n = n->left;
      n->left = malloc(sizeof(heapNode));
      tail = n->left;
      tail->data[X] = buffer[X];
      tail->data[Y] = buffer[Y];
      tail->data[VALUE] = buffer[VALUE];
      tail->parent = n;
      tail->left = NULL;
      tail->right = NULL;      
   }
   else if(parent == head){
      n = parent->left;
      while(n->left != NULL)
         n = n->left;
      n->left = malloc(sizeof(heapNode));
      tail = n->left;
      tail->data[X] = buffer[X];
      tail->data[Y] = buffer[Y];
      tail->data[VALUE] = buffer[VALUE];
      tail->parent = n;
      tail->left = NULL;
      tail->right = NULL;
   }
   else
      pushSub(parent);
}


void replace(heapNode* n){
   n->data[X] = buffer[X];
   n->data[Y] = buffer[Y];
   n->data[VALUE] = buffer[VALUE];
   shiftDown(n);
}


int update(heapNode* n){
   if(n != NULL){
      if(n->data[X] == buffer[X] && n->data[Y] == buffer[Y]){
         replace(n);
         shiftUp(n);
         return true;
      }  
      if(update(n->left))
         return true;
      return(update(n->right));
   }
   return false;
}


void pop(){
   if(head != NULL){
      if(head == tail){
         free(head);
         head = NULL;
         tail = NULL;
      }
      else{
         swap(head, tail);
         heapNode* tailParent = tail->parent;
         if(tailParent->right == tail){
            tailParent->right = NULL;
            free(tail);
            tail = tailParent->left;
         }
         else{
            tailParent->left = NULL;
            popSub(tail);
         }
         shiftDown(head);
      }
   }
}


void popSub(heapNode* n){
   heapNode* parent = n->parent;
   if(parent->right == n){
      n = parent->left;
      while(n->right != NULL)
         n = n->right;
      free(tail);
      tail = n;
   }
   else if(parent == head){
      n = parent;
      while(n->right != NULL)
         n = n->right;
      free(tail);
      tail = n;
   }
   else
      popSub(parent);
}


void freeMem(heapNode* n){
   if(n != NULL){
      freeMem(n->left);
      freeMem(n->right);
      free(n);
   }
}


void reheap(heapNode* n){
   shiftUp(n);
   shiftDown(n);
}


void shiftUp(heapNode* n){
   if(n->parent != NULL && n->parent->data[VALUE] > n->data[VALUE]){
      swap(n, n->parent);
      shiftUp(n->parent);
   }
}


void shiftDown(heapNode* n){
   if(n->left != NULL){
      if(n->right != NULL){
         if(n->right->data[VALUE] <= n->left->data[VALUE]){
            if(n->right->data[VALUE] < n->data[VALUE]){
               swap(n->right, n);
               shiftDown(n->right);
            }
            return;
         }
      }
      if(n->left->data[VALUE] < n->data[VALUE]){
         swap(n->left, n);
         shiftDown(n->left);
      }
   }
}


void swap(heapNode* a, heapNode* b){
   int i = a->data[X];
   int j = a->data[Y];
   int k = a->data[VALUE];

   a->data[X] = b->data[X];
   a->data[Y] = b->data[Y];
   a->data[VALUE] = b->data[VALUE];

   b->data[X] = i;
   b->data[Y] = j;
   b->data[VALUE] = k;
}
