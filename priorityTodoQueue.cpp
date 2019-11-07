#include <iostream>
#include <string>
#include <functional>
#include <list>
#include "priorityTodoQueue.hpp"

priorityQueueTodo::priorityQueueTodo()
{
	head = NULL;
	rear = NULL;
	size = 0;
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
	Node * toAdd;
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

	size++;

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
	Node * iter;

	for(iter = head; iter; iter = iter->next)
	{
		std::cout << "--------------------------------------------------------\n";
		iter->key->print();
		std::cout << "--------------------------------------------------------\n";
	}

	return;
}

void priorityQueueTodo::prioritizeByDeadLine()
{
	Node * iter;
	int priorityOffset = 0;
	std::time_t oldestUnixTime = NULL;

	for(iter = head; iter; iter = iter->next)
	{
		if(!iter->key->getDeadLine() == NULL)
			iter->priority = 0;
		else if(oldestUnixTime == NULL || iter->key->getDeadLine() < oldestUnixTime)
		{
			oldestUnixTime = iter->key->getDeadLine();
			iter->priority = ++priorityOffset;	 
		}
		else
		{
			iter->priority = priorityOffset;
		}
	}

	sort();
}

void priorityQueueTodo::prioritizeByDateCreated()
{
	Node * iter;
	int priorityOffset = 0;
	for(iter = head; iter; iter = iter->next)
	{
		if(!iter->key->getDeadLine() == NULL)
			iter->priority = 0;
		else
		{
			iter->priority = ++priorityOffset;
		}
		
	}
}

//Private
//TODO: this is bubble sort but should be something better.
void priorityQueueTodo::sort()
{
	//Decending order.
	bool sorted = false;

	while(!sorted)
	{
		for(Node * iter = head; iter; iter = iter->next)
		{
			sorted = true;
			if(iter->priority < iter->next->priority)
			{
				switchNodes(iter,iter->next);
				sorted = false;
			}
		}

	}
}

//You have entered the comedy area.
//Switches the refs of these
void switchNodes(Node* a,Node* b)
{
	Node* temp = new Node;
	if(!temp) return;
	temp->key = a->key;
	temp->priority = a->priority;

	a->key = b->key;
	a->priority = b->priority;

	b->key = temp->key;
	b->priority = temp->priority;

	delete temp;
}