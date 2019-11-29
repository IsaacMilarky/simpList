#include <iostream>
#include <iomanip>
#include "ListItem.hpp"

ListItem::ListItem(std::string name)
{
	std::time_t now = time(NULL);
	dateCreated = std::localtime(&now);
	deadLine = NULL;
	itemName = name;	
}

ListItem::ListItem(std::string name, std::tm hardLineDeadLine)
{
	/*
		Arguments are not pointers because I don't
		want to deal with the possibility of memory
		handles to ListItem being null.
	*/
	std::time_t now = std::time(NULL);
	dateCreated = std::localtime(&now);
	deadLine = new std::tm;
	if(!deadLine) //Dont touch
		std::cout << "Error: everything is on fire: line 24 toDoList.cpp\n";

	*deadLine = hardLineDeadLine;

	itemName = name;
}

ListItem::ListItem(std::string name, std::time_t hardLineDeadLine)
{
	/*
		Arguments are not pointers because I don't
		want to deal with the possibility of memory
		handles to ListItem being null.
	*/

	std::time_t now = std::time(NULL);
	dateCreated = std::localtime(&now);
	deadLine = new std::tm;
	if(!deadLine)
		std::cout << "Error: seek help on line 43 toDoList.cpp\n";

	//localtime takes pointer so we give it parameter addr.
	deadLine = std::localtime(&hardLineDeadLine);

	itemName = name;
}


ListItem::~ListItem()
{
	if(deadLine)
		delete deadLine;
}

std::tm* ListItem::getCreationDate()
{
	return dateCreated;
}

std::tm* ListItem::getDeadLine()
{
	return deadLine ? deadLine : NULL;
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
	std::cout << "Item Created on: " << std::put_time(dateCreated,"%c %Z") << "\n";
	
	if(deadLine)
		std::cout << "Item should be completed on: " << std::put_time(deadLine,"%c %Z") << "\n";
}

void ListItem::setDeadLine(std::tm future)
{
	deadLine = new std::tm;
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

/*
	Standard:
		Make sure that these operator overloads match up in the 
		order that they push/pull all members from a given
		stream. (ints all together, strings all together, etc).
*/
std::istream& operator>>(std::istream& is, ListItem& en)
{
	//Take in rawInput as string and cast it.
	std::string rawInput;
	is >> rawInput;

	auto input = std::stol(rawInput);
	en.dateCreated = localtime(&input);

	is >> rawInput;
	if(rawInput != "nodeadline")
	{
		input = std::stol(rawInput);
		en.deadLine = localtime(&input);
	}
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const ListItem& en)
{
	os << std::mktime(en.dateCreated) << ", ";
	if(en.deadLine)
		os << std::mktime(en.deadLine) << ", ";
	else
		os << "nodeadline,";
	
	os << en.itemName << ", ";

	return os;
}
