#pragma once
#include <iostream>
#include <string>
#include <fstream>
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
		void printTodo();
		void prioritizeByDeadLine();
		void prioritizeByDateCreated();

		bool writeToFile();
		bool loadFromFile(std::string);

	private:
		void sort();

		int size;
		Node *head,*rear;
		
};


void switchNodes(Node*,Node*);
