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
        void addToList(std::string);
        void editList(std::string);

        //Get list by name
        priorityQueueTodo * getList(std::string);

        //Handle getting date from prompt
        boost::posix_time::ptime promptDate();
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
        boost::posix_time::time_duration promptTime();
        //Prints items in lists
        void showList(std::string);
    
    private:
        //Lists are stored on heap, make sure to destruct that memory.
        std::vector<priorityQueueTodo *> lists;

};