#pragma once
#include <vector>
#include <time.h>
#include <string>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <math.h>

/*
 *	Created by: Isaac Milarsky
 * 	Created on: 11/5/2019
 * 	Last Modified: 11/28/2019
 * 
 */

//Had to make own version of std::stol
long stringToLongInt(std::string str)
{
	long convertThis = 0;
	for(unsigned iter = 0; iter < str.length(); ++iter)
	{
		//I'm doing it the c way.
		long digit = (int)str.at(iter) - '0';
		convertThis += digit * std::pow(10,iter);
		std::cout << convertThis << '\n';
	}
	return convertThis;
}


//TODO: try to get rid of some of these libraries.
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
