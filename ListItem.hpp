#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <ctime>
#include <fstream>
//Using text serialization for the moment as it can be debugged easier.
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/*	
 *	Created by: Isaac Milarsky
 * 	Created on: 11/5/2019
 *  //TODO: Be able to serialize list data.
 * 	In order to do this I'm adding boost libraries to the project.
 */



//TODO: standardize date format storage fmt.
class ListItem
{
	public:
		//Blank constructor for memory purposes sometimes.
		ListItem();
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
		friend class boost::serialization::access;
		//Taken from: https://www.boost.org/doc/libs/1_75_0/libs/serialization/doc/tutorial.html
		//We are using Archive similar to a stream operator.
		//In case Archive is an input & is used similar to >>
		//Taken from boost example given.
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			//Differant from example. Gives member info to the archive.
			//Important to store data and not pointers.
			ar & itemName;
			ar & itemBody;
			//Now for the hard ones.
			/*if(dateCreated)
				ar & *dateCreated;
			if(deadLine)
				ar & *deadLine;*/
		}		

		std::tm * dateCreated;
		std::tm * deadLine; //ssh its fine
		std::string itemName;
		/*
			Adding a body section to each reminder.
		*/
		std::string itemBody;
		
};
