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
	//Default name.
	listName = std::to_string(std::time(0));
}

priorityQueueTodo::priorityQueueTodo(std::string title)
{
	head = NULL;
	rear = NULL;
	size = 0;
	listName = title;
}

/*
 * class destructor:
 * kills all of the memory that was allocated by the queue.
 */
priorityQueueTodo::~priorityQueueTodo()
{
	Node* iter = head;
	//Wont fire if queue is empty
	while(iter)
	{
		Node* clobberinTime = iter;
		iter = iter->next;
		delete clobberinTime->key;
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

	//We are now storing on the heap because memory errors.
	//toAdd->key = listItemPtr;
	ListItem * copyData = new ListItem();
	*copyData = *listItemPtr;
	toAdd->key = copyData;

	//toAdd->key->print();
	toAdd->priority = priority;
	toAdd->next = NULL;

	if(!head || !rear)
	{
		head = toAdd;
		rear = toAdd;
		return true;
	}

	//Use a pointer to iterate through p-queue and stop when relevant
	//sorting index is reached.
	Node* iter;
	for(iter = head; iter->next; iter = iter->next)
	{
		if(iter->next->priority >= toAdd->priority)
			break;
	}

	//Equals iter->next if it exists otherwise its null;
	Node* temp = (iter->next) ? iter->next : NULL;

	++size;

	//Replace new first index as the head.
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
		std::cout << iter->priority << "\n";
		std::cout << "--------------------------------------------------------\n";
	}

	return;
}

void priorityQueueTodo::prioritizeByDeadLine()
{
	Node * iter;
	int priorityOffset = 0;
	std::time_t oldestUnixTime = -1;


	for(iter = head; iter; iter = iter->next)
	{
		std::tm toTimestruct = boost::posix_time::to_tm(iter->key->getDeadLine());
		if((iter->key->getDeadLine()).is_not_a_date_time())
			iter->priority = 0;
		//std::mktime converts time to seconds since 1/1/1970
		else if(oldestUnixTime == -1 || std::mktime(&toTimestruct) < oldestUnixTime)
		{
			oldestUnixTime = std::mktime(&toTimestruct);
			std::cout << oldestUnixTime << "/ C iteration\n";
			iter->priority = ++priorityOffset;	 
		}
		else
		{
			iter->priority = priorityOffset;
		}
		
	}

	sort();
}

//Needs large scale testing to make sure is actually good.
void priorityQueueTodo::prioritizeByDateCreated()
{
	Node * iter;
	int priorityOffset = 0;
	std::time_t oldestUnixTime = -1;

	for(iter = head; iter; iter = iter->next)
	{
		std::tm toTimestruct = boost::posix_time::to_tm(iter->key->getCreationDate());
		if(oldestUnixTime == -1 || std::mktime(&toTimestruct) <= oldestUnixTime)
		{
			oldestUnixTime = std::mktime(&toTimestruct);
			iter->priority = ++priorityOffset;
		}
		else
		{
			iter->priority = priorityOffset;
		}
		
		
	}
	sort();
}

//Head/rear get/set

std::string priorityQueueTodo::getName()
{
	return listName;
}

Node* priorityQueueTodo::getHead()
{
	return head;
}

ListItem* priorityQueueTodo::popHead()
{
	//Get memory of listItem before deleting head.
	ListItem * toReturn;
	if(head)
	{
		toReturn = head->key;
		//std::cout << head->key->getTodoBody() << std::endl;
		//toReturn->print();
	}
	else
		toReturn = NULL;
	//Delete head.
	Node * clobberinTime = head;
	if(head)
		head = head->next;

	delete clobberinTime;
	return toReturn;
}

Node* priorityQueueTodo::getRear()
{
	return rear;
}


//Private
//TODO: this is bubble sort but should be something better.
// Currently does not work.
void priorityQueueTodo::sort()
{
	//Decending order.
	bool sorted = false;

	while(!sorted)
	{
		int count = 0;

		for(Node * iter = head; iter->next; iter = iter->next)
		{

			if(iter->priority < iter->next->priority)
			{
				switchNodes(iter,iter->next);
				count++;
			}
		}

		sorted = count == 0;

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