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

	private:
		Node *head,*rear;
};
