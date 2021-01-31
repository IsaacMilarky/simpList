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
		void setDeadLine(std::tm);
		void setTodoName(std::string);
		void setTodoBody(std::string);
		std::string getTodoBody();
		void print();

	protected:
		std::tm * dateCreated;
		std::tm * deadLine; //ssh its fine
		std::string itemName;
		/*
			Adding a body section to each reminder.
		*/
		std::string itemBody;
		
};
