#include <iostream>
#include <string>
#include "ListItem.hpp"

//Standard linked list with minor diffs. (priority)
typedef struct nodeStruct
{
	ListItem * key;
	nodeStruct * next;	
	float priority;
} Node;

/* priorityQueueTodo:
 * class to perform queue functions
 */
class priorityQueueTodo
{
	//Uses default constructor.
	public:
		priorityQueueTodo();
		~priorityQueueTodo();
		//arg needs to be dynamic
		bool addTodoItem(ListItem*,float);
		void printTodo();
		void prioritizeByDeadLine();
		void prioritizeByDateCreated();

	private:
		void sort();

		int size;
		Node *head,*rear;
		
};


void switchNodes(Node*,Node*);
