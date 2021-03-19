#include <iostream>
#include <string>
#include "ListItem.hpp"

/*	
 *	Created by: Isaac Milarsky
 * 	Created on: 11/5/2019
 * 	Last Modified: 11/11/2019
 * 
 */


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
		priorityQueueTodo(std::string);
		~priorityQueueTodo();
		//arg needs to be dynamic
		bool addTodoItem(ListItem*,float);
		std::string printTodo();
		void prioritizeByDeadLine();
		void prioritizeByDateCreated();

		std::string getName();

		/*
		Get/pop head
		*/

		//Returns heap memory
		Node* getHead();
		//Returns reference to popped listItem.
		ListItem* popHead();
		//Returns heap memory.
		Node* getRear();
		//We don't pop back the rear of the pq as it doesn't make sense logically.

		//Get reference to some listItem
		ListItem* getItem(std::string);
		//Delete listItem from list in smooth way.
		void deleteItem(std::string);

	private:
		void sort();
		std::string listName;
		int size;
		Node *head,*rear;
		
};


void switchNodes(Node*,Node*);
