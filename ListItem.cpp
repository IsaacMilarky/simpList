#include <iostream>
#include <iomanip>
#include "ListItem.hpp"

ListItem::ListItem()
{
	std::time_t now = time(NULL);
	dateCreated = std::localtime(&now);
	deadLine = NULL;
	itemName = "N/A";
	itemBody = "";
}

ListItem::ListItem(std::string name)
{
	//now = current system time.
	std::time_t now = time(NULL);
	dateCreated = std::localtime(&now);
	deadLine = NULL;
	itemName = name;
	itemBody = "";	
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
	else
		*deadLine = hardLineDeadLine;

	itemName = name;
	itemBody = "";
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
	itemBody = "";
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

void ListItem::setTodoBody(std::string body)
{
	itemBody = body;
}

std::string ListItem::getTodoBody()
{
	return itemBody;
}

void ListItem::print()
{
	//TODO: just make it print out members that exist.
	/*
		std::time_t dateCreated;
		std::time_t * deadLine; //ssh its fine
		std::string itemName;
	*/

	std::cout << "Title: " << itemName << "\n";
	//Ternery outputs string if it isn't empty, otherwise gives N/A
	std::string bodyToPrint = itemBody.compare("") != 0 ? "N/A" : itemBody;
	std::cout << "Body: " << bodyToPrint << "\n";
	std::cout << "Item Created on: " << std::put_time(dateCreated,"%c %Z") << "\n";
	
	if(deadLine)
		std::cout << "Item should be completed on: " << std::put_time(deadLine,"%c %Z") << "\n";
}

//Taken from boost example given.
template<class Archive>
void ListItem::serialize(Archive & ar, const unsigned int version)
{
	//Differant from example. Gives member info to the archive.
	//Important to store data and not pointers.
	ar & itemName;
	ar & itemBody;
	//Now for the hard ones.
	ar & (dateCreated ? *dateCreated : std::tm());
	ar & (deadLine ? *deadLine : std::tm());
}