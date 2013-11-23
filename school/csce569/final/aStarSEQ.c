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

const int MAX_PROCS = 1;
const int ROOT = 0;


int procs, rank;
MPI_Status status;

int buffer[3];
int nodeCount;
heapNode* head;
heapNode* tail;
aStarNode* n;


struct aStarNode{
   int loc[2];
   int priority;
   int estimate;
   int distance;
   int status;
   aStarNode* parent;
   heapNode* node;
};

struct heapNode{
   heapNode* parent;
   heapNode* left;
   heapNode* right;
   aStarNode* item;
};


void master();

int min(int, int);
int findEstimate(int, int, int, int);
void printPath(aStarNode*);

void sendMsg(aStarNode*, int, int, int);
void recieveMsg();

void push(aStarNode*);
void pushSub(aStarNode*, heapNode*);
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

   if(rank == 0){
      if(procs > MAX_PROCS){
         printf("Only %i processes allowed, remaining will not be used\n", MAX_PROCS);
         procs = MAX_PROCS;
      } 
      master();
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
         n = node[start[X]][start[Y]];
         n->loc[X] = start[X];
         n->loc[Y] = start[Y];
         n->estimate = findEstimate(start[X], start[Y], goal[X], goal[Y]);         
         n->distance = 0;
         n->priority = n->distance + n->estimate;
         n->parent = NULL;
         n->node = malloc(sizeof(heapNode));
	 n->node->parent = NULL;
         n->node->left = NULL;
         n->node->right = NULL;
         n->node->item = n;

         // Push node to process 1
         nodeCount = 0;
         push(n);

         // Other
         int success = false;  	// boolean: if succeeded in finding goal node
         int add;		// boolean: if node was added for this direction
         int next[2];           // next node coordinates
         int diag1, diag2;      // values of diagonals
         int dist;              // distance to next node
         aStarNode* temp;       // temp node representing next node
         int count = 0;		// count of nodes iterated through, used for early outs
         int deleted;		// boolean: if node has been deleted or not

         while(head != NULL){                       
            n = head->item;
            deleted = false;
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
                        temp->node = malloc(sizeof(heapNode));
                        temp->node->parent = NULL;
                        temp->node->left = NULL;
                        temp->node->right = NULL;
                        temp->node->item = temp;
                       
                        add = true;
                    }
                     else if(dist < temp->distance){ // is OPEN
                        temp->distance = dist;
                        temp->priority = temp->distance + temp->estimate;
                        temp->parent = n;

                        reheap(temp->node);
                     }
                  }
                    
                  if(add){
                     if(!deleted){
 		        head->item = temp;
                        temp->node = head;
                        reheap(head);
                        deleted = true;
                     }
                     else
                         push(temp);
                  }
                  else if(!deleted){
                     pop();
                     deleted = true;
                  }
               }
               else if(!deleted){
                  pop();
                  deleted = true;
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
   freeMem(head);

   for(i = 0; i < nodes[X]; i++){
      for(int j = 0; j < nodes[Y]; j++)
         free(node[i][j]);
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


void printPath(aStarNode* a){
   if(a->parent != NULL)
      printPath(a->parent);
   printf("(%i, %i) -to- ", a->loc[X], a->loc[Y]);
}


void push(aStarNode* a){
   if(head == NULL){
      head = a->node;
      head->item = a;
      tail = head;
   }
   else{
      if(head == tail){
         head->left = a->node;
         head->left->item = a;
         tail = head->left;
         tail->parent = head;
      }
      else{
         heapNode* tailParent = tail->parent;
         if(tailParent->right == NULL){
            tailParent->right = a->node;            
            tailParent->right->item = a;
            tail = tailParent->right;
            tail->parent = tailParent;
         }
         else
            pushSub(a, tail);
      }
      shiftUp(tail);
   }
}


void pushSub(aStarNode* a, heapNode* no){
   heapNode* parent = no->parent;
   if(no == parent->left){
      no = parent->right;
      while(no->left != NULL)
         no = no->left;
      
      no->left = a->node;
      no->left->item = a;
      tail = no->left;
      tail->parent = no;
   }
   else if(parent == head){
      no = parent->left;
      while(no->left != NULL)
         no = no->left;
      
      no->left = a->node;
      no->left->item = a;
      tail = no->left;
      tail->parent = no;
   }
   else
      pushSub(a, parent);
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


void popSub(heapNode* no){
   heapNode* parent = no->parent;
   if(parent->right == no){
      no = parent->left;
      while(no->right != NULL)
         no = no->right;
      free(tail);
      tail = no;
   }
   else if(parent == head){
      no = parent;
      while(no->right != NULL)
         no = no->right;
      free(tail);
      tail = no;
   }
   else
      popSub(parent);
}


void freeMem(heapNode* no){
   if(no != NULL){
      freeMem(no->left);
      freeMem(no->right);
      free(no);
   }
}


void reheap(heapNode* no){
   shiftUp(no);
   shiftDown(no);
}


void shiftUp(heapNode* no){
   if(no->parent != NULL && no->parent->item->priority > no->item->priority){
      swap(no, no->parent);
      shiftUp(no->parent);
   }
}


void shiftDown(heapNode* no){
   if(no->left != NULL){
      if(no->right != NULL){
         if(no->right->item->priority <= no->left->item->priority){
            if(no->right->item->priority < no->item->priority){
               swap(no->right, no);
               shiftDown(no->right);
            }
            return;
         }
      }
      if(no->left->item->priority < no->item->priority){
         swap(no->left, no);
         shiftDown(no->left);
      }
   }
}


void swap(heapNode* a, heapNode* b){
   aStarNode* temp = a->item;
   a->item = b->item;
   a->item->node = a;
   b->item = temp;
   b->item->node = b;
}
