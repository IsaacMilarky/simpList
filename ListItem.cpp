#include <iostream>
#include "ListItem.hpp"

ListItem::ListItem(std::string name)
{
	dateCreated = time(NULL);
	deadLine = NULL;
	itemName = name;	
}

ListItem::ListItem(std::string name, std::time_t hardLineDeadLine)
{
	dateCreated = time(NULL);
	deadLine = new std::time_t;
	if(!deadLine) //Dont touch
		std::cout << "Error: everything is on fire: line 16 toDoList.cpp\n";

	*deadLine = hardLineDeadLine;

	itemName = name;
}

ListItem::~ListItem()
{
	if(deadLine)
		delete deadLine;
}

std::time_t ListItem::getCreationDate()
{
	return dateCreated;
}

std::time_t ListItem::getDeadLine()
{
	if(deadLine)
		return *deadLine;
	return NULL;
}

std::string ListItem::getTodoName()
{
	return itemName;
}

void ListItem::print()
{
	//TODO: just make it print out members that exist.
	/*
		std::time_t dateCreated;
		std::time_t * deadLine; //ssh its fine
		std::string itemName;
	*/

	std::cout << "toDo: " << itemName << "\n";
	std::cout << "Item Created on: " << std::ctime(&dateCreated) << "\n";
	if(deadLine)
		std::cout << "Item should be completed on: " << std::ctime(deadLine) << "\n";
}

void ListItem::setDeadLine(std::time_t future)
{
	deadLine = new std::time_t;
	if(!deadLine)
		return;
	*deadLine = future;
	return;
}

void ListItem::setTodoName(std::string name)
{
	itemName = name;
	return;
}

