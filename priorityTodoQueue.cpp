#include <iostream>
#include <string>
#include "priorityTodoQueue.hpp"

priorityQueueTodo::priorityQueueTodo()
{
	head = NULL;
	rear = NULL;
}

/*
 * class destructor:
 * kills all of the memory that was allocated by the queue.
 */
priorityQueueTodo::~priorityQueueTodo()
{
	Node* iter = head;
	while(iter)
	{
		Node* clobberinTime = iter;
		iter = iter->next;
		delete clobberinTime;
	}	
}

bool priorityQueueTodo::addTodoItem(ListItem * listItemPtr,float priority)
{
	Node toAdd;
	toAdd = new Node;
	if(!toAdd)
	{
		std::cout << "Error: Pointer didn't allocate in addtoQueue :(\n";
		return false;
	}

	toAdd->key = listItemPtr;
	toAdd->priority = priority;
	toAdd->next = NULL;

	if(!head || !rear)
	{
		head = toAdd;
		rear = toAdd;
		return true;
	}

	Node* iter;
	for(iter = head; iter->next; iter = iter->next)
	{
		if(iter->next->priority >= toAdd->priority)
			break;
	}

	//Equals iter->next if it exists otherwise its null;
	Node* temp = (iter->next) ? iter->next : NULL;

	if(priority < head->priority)
	{
		temp = head;
		head = toAdd;
		toAdd->next = temp;
		return true;
	}

	iter->next = toAdd;
	toAdd->next = temp;
	return true;
}

//Just prints what's in the class.
void priorityQueueTodo::printTodo()
{

	return;
}
