#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "ListItemLoadWrapper.hpp"

bool hasEnding(std::string const&,std::string const&);

class TodoController
{
    public:

        TodoController();
        ~TodoController();

        std::vector<std::string> getLists();

        //Adds to selected list, arg is list name.
        //Default args to toggle prompts.
        void addToList(std::string,std::string = "",boost::gregorian::date = boost::gregorian::date(),std::string = "",std::string = "");
        //edit will remove requested list item string and call AddToList.
        //No default is present for ListItem's name on this method.
        void editList(std::string,std::string,boost::gregorian::date = boost::gregorian::date(),std::string = "",std::string = "");

        //Get list by name
        priorityQueueTodo * getList(std::string);

        void deleteList(std::string);

        void deleteListItem(std::string,std::string);

        //Prints items in lists
        void showList(std::string);

        void checkDeadLines();
    
    private:
        //Private methods
        //Handle getting date from prompt
        //Defualt argument to subvert text prompt.
        boost::posix_time::ptime promptDate(boost::gregorian::date = boost::gregorian::date(),std::string = "");
        //Prompt user for year to store in an int.
        //Returns current system year if no input.
        int promptYear();
        //Prompt user for month to store in an int
        //returns current system month if no input.
        int promptMonth();
        //prompt user for year to store in int
        //Returns current system month if no input
        int promptDay(int);
        //Prompt user for time of day.
        boost::posix_time::time_duration promptTime(std::string = "");
        
        //Lists are stored on heap, make sure to destruct that memory.
        std::vector<priorityQueueTodo *> lists;


};