#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <ctime>

/*
 *	Created by: Isaac Milarsky
 * 	Created on: 11/5/2019
 * 	Last Modified: 11/11/2019
 * 
 */



//TODO: standardize date format storage fmt.
class ListItem
{
	public:
		//Default contructor without deadline
		ListItem(std::string);
		//Secondary constructor with deadline
		ListItem(std::string, std::tm);
		//Tertiary constructor for diff. time measure
		ListItem(std::string, std::time_t);
		//Free the pointer to deadline if it exists.
		~ListItem();

		//Getters and Setters
		std::tm * getCreationDate();
		std::tm * getDeadLine();
		std::string getTodoName();
		void print();
		void setDeadLine(std::tm);
		void setTodoName(std::string);

		//Operators for file insertion/extraction
		friend std::istream& operator>>(std::istream& is, ListItem& en);
		friend std::ostream& operator<<(std::ostream& os, const ListItem& en);

	protected:
		std::tm * dateCreated;
		std::tm * deadLine; //ssh its fine
		std::string itemName;
		
};
