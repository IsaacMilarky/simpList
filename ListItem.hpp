#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <ctime>
#include <fstream>
//Using text serialization for the moment as it can be debugged easier.
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
//Upgrade to a more complicated Date time format
#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

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
		//Another constructor for best time measure
		ListItem(std::string,boost::gregorian::date);
		//Yet another overload
		ListItem(std::string,boost::posix_time::ptime);

		//Getters and Setters
		boost::posix_time::ptime getCreationDate();
		boost::posix_time::ptime getDeadLine();
		std::string getTodoName();
		void setDeadLine(std::tm);
		void setDeadLine(boost::gregorian::date);
		void setDeadLine(boost::posix_time::ptime);
		void setTodoName(std::string);
		void setTodoBody(std::string);
		std::string getTodoBody();

		void print();
		

	protected:
		friend class boost::serialization::access;
		//Taken from: https://www.boost.org/doc/libs/1_75_0/libs/serialization/doc/tutorial.html
		template<class archive_type, class temporal_type>
      	void save_to(archive_type& ar, const temporal_type& tt)
      	{
        	ar << tt;
      	}
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
			//std::cout << "Body:" << itemBody << std::endl;
			//Now for the hard ones.
			ar & dateCreated;

			//if(!deadLine.is_not_a_date_time())
			//	ar & deadLine;
			//std::cout << deadLine << std::endl;
			ar & deadLine;
		}		

		//We want to store times as a simple numeral if possible.
		boost::posix_time::ptime dateCreated;
		boost::posix_time::ptime deadLine; //ssh its fine
		std::string itemName;
		/*
			Adding a body section to each reminder.
		*/
		std::string itemBody;
		
};
