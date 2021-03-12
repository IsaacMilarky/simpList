#include "SimpListConfig.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/filesystem.hpp>
#include "TodoController.hpp"
#include <fstream>
#include <iostream>
#include <string>

//Where to save listItems
const std::string LISTITEM_STORE = "listitems.list";

/*
    Should have not stupid syntax.
    Something like ./Simplist -a listItem -d DD-MM-YYYY

*/


int main(int argc, char * argv[])
{
    //Print Version number
    std::cout << argv[0] << " Version " << SimpList_VERSION_MAJOR << "."
        << SimpList_VERSION_MINOR << std::endl;
    //const double inputValue = std::stod(argv[1]);
    
    ListItem g("Hello World");
    g.setTodoBody("good morning");

    ListItemLoadWrapper wrap = ListItemLoadWrapper();
    wrap.addItem(&g);
    wrap.writeToFile(LISTITEM_STORE);

    TodoController controller = TodoController();
    controller.addToList("listitems.list");
    controller.getLists();

    
}

