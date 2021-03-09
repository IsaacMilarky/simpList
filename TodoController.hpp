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

        //Prints items in lists
        void showList(std::string);
    
    private:
        //Lists are stored on heap, make sure to destruct that memory.
        std::vector<priorityQueueTodo *> lists;

};