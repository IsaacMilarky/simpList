#include <iostream>
#include <iomanip>
#include "ListItem.hpp"

ListItem::ListItem()
{
	//std::time_t now = time(NULL);
	//Get current system time using boost
	dateCreated = boost::posix_time::second_clock::local_time();
	//Init to null value equal to not_a_date_time
	//Value is checked using |bool is_not_a_date() const|
	deadLine = boost::posix_time::ptime();
	itemName = "N/A";
	itemBody = "";
}

ListItem::ListItem(std::string name)
{
	//now = current system time.
	//Get current system time using boost
	dateCreated = boost::posix_time::second_clock::local_time();

	//Init to null value equal to not_a_date_time
	//Value is checked using |bool is_not_a_date() const|
	deadLine = boost::posix_time::ptime();
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
	//Get current system time using boost
	dateCreated = boost::posix_time::second_clock::local_time();

	deadLine = boost::posix_time::ptime_from_tm(hardLineDeadLine);

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

	//Get current system time using boost
	dateCreated = boost::posix_time::second_clock::local_time();

	//localtime takes pointer so we give it parameter addr.
	deadLine = boost::posix_time::ptime_from_tm(*std::localtime(&hardLineDeadLine));

	itemName = name;
	itemBody = "";
}

ListItem::ListItem(std::string name,boost::gregorian::date hardLineDeadLine)
{
	//Get current system time using boost
	dateCreated = boost::posix_time::second_clock::local_time();

	deadLine = boost::posix_time::ptime(hardLineDeadLine);

	itemName = name;
	itemBody = "";
}

ListItem::ListItem(std::string name, boost::posix_time::ptime futureDeadline)
{
	//Get current system time using boost
	dateCreated = boost::posix_time::second_clock::local_time();

	deadLine = futureDeadline;

	itemName = name;
	itemBody = "";
}

boost::posix_time::ptime ListItem::getCreationDate()
{
	return dateCreated;
}

boost::posix_time::ptime ListItem::getDeadLine()
{
	return deadLine;
}

std::string ListItem::getTodoName()
{
	return itemName;
}


void ListItem::setDeadLine(std::tm future)
{
	deadLine = boost::posix_time::ptime_from_tm(future);
	return;
}

void ListItem::setDeadLine(boost::gregorian::date future)
{
	deadLine = boost::posix_time::ptime(future);
}

void ListItem::setDeadLine(boost::posix_time::ptime future)
{
	deadLine = future;
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
	std::cout << "Body: " << itemBody << "\n";
	std::cout << "Item Created on: " << dateCreated << "\n";
	
	if(!deadLine.is_not_a_date_time())
		std::cout << "Item should be completed on: " << deadLine << "\n";
}

