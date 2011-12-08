// Jonathan Chandler
// main.C

#include "Node.h"
#include "PriorityQueue.h"


int main(){
	PriorityQueue *pq = new PriorityQueue();
	cout << endl << endl << endl;
	cout << "Testing isEmpty with empty queue" << endl;
	if(pq->isEmpty())
		cout << "Success - true" << endl;
	else 
		cout << "Fail - false" << endl;

	cout << "Pushing a 5 to the queue" << endl;
	pq->Push(5);
	
	cout << "Testing isEmpty with non-empty queue" << endl;
        if(pq->isEmpty())
                cout << "Fail - true" << endl;
        else
                cout << "Success - false" << endl;
	
	cout << "Testing Peek" << endl;
	if(pq->Peek() == 5)
		cout << "Success - top is 5" << endl;
	else
		cout << "Fail - top is not 5" << endl;

	cout << "Testing Pop" << endl;
	if(pq->Pop() == 5)
		cout << "Success - pop returned 5" << endl;
	else
		cout << "Fail - pop did not return 5" << endl;

	cout << "Testing isEmpty()" << endl;
	if(pq->isEmpty())
                cout << "Success - true" << endl;
        else
                cout << "Fail - false" << endl;	

	cout << "Pushing 45, 500, 20, 0, 45, -3, 60, 12, 10, 20" << endl;	
	pq->Push(45);
	pq->Push(500);
        pq->Push(20);
        pq->Push(0);
        pq->Push(45);
        pq->Push(-3);
        pq->Push(60);
        pq->Push(12);
        pq->Push(10);
        pq->Push(20);

	cout << "Correct preorder:  ";
	pq->PreOrder();

	cout << pq->Pop() << endl;

	cout << "Correct preorder:  ";
	pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

        cout << pq->Pop() << endl;

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << "Pushing 45, 500, 20, 0, 45, -3, 60, 12, 10, 20" << endl;
        pq->Push(45);
        pq->Push(500);
        pq->Push(20);
        pq->Push(0);
        pq->Push(45);
        pq->Push(-3);
        pq->Push(60);
        pq->Push(12);
        pq->Push(10);
        pq->Push(20);

	cout << "Attempting to delete 66 -- should fail" << endl;
	pq->Delete(66);

	cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << "Deleting 45 - should delete the tail" << endl;
        pq->Delete(45);

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << "Deleting 10" << endl;
        pq->Delete(10);

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << "Deleting 500 - should delete the tail" << endl;
        pq->Delete(500);

        cout << "Correct preorder:  ";
        pq->PreOrder();	

	cout << "Deleting 0" << endl;
        pq->Delete(0);

        cout << "Correct preorder:  ";
        pq->PreOrder();

	cout << "Attempting to empty the list" << endl;
	pq->Empty();
		
	if(pq->isEmpty())
		cout << "List is empty" << endl;
	else
		cout << "Failure! - List is NOT empty" << endl;
	
	delete pq;

	return 0;
}
