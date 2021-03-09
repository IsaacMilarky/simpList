#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "priorityTodoQueue.hpp"
#include <boost/serialization/vector.hpp>
/*
Author: Isaac Milarsky
Created on: 3/6/2021
*/

//Essentially an extension of std::vector<ListItem> with good practice
class ListItemLoadWrapper
{
    public:
        ListItemLoadWrapper();
        ~ListItemLoadWrapper();

        //Add items by pass
        void addItem(ListItem*);
        void loadFromFile(std::string);
        void writeToFile(std::string);

        std::vector<ListItem> wrapArray;
    private:
        friend class boost::serialization::access;
        //Taken from: https://www.boost.org/doc/libs/1_75_0/libs/serialization/doc/tutorial.html
		
        //Using archive similar to a stream.
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & wrapArray;
        }
        
};