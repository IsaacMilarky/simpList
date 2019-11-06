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

std::string ListItem::getTodoName()
{
	return itemName;
}

void ListItem::print()
{
	//TODO: just make it print out members that exist.
}

