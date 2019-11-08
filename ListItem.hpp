#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <ctime>

class ListItem
{
	public:
		//Default contructor without deadline
		ListItem(std::string);
		//Secondary constructor with deadline
		ListItem(std::string, std::time_t);
		//Free the pointer to deadline if it exists.
		~ListItem();

		//Getters and Setters
		std::time_t getCreationDate();
		std::time_t getDeadLine();
		std::string getTodoName();
		void print();
		void setDeadLine(std::time_t);
		void setTodoName(std::string);
	protected:
		std::time_t dateCreated;
		std::time_t * deadLine; //ssh its fine
		std::string itemName;
		
};
