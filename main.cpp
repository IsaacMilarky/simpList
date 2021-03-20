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

    For reminders:
        some command like ./Simplist -U should be called by the system to check deadlines.

*/


int main(int argc, char * argv[])
{
    //Print Version number
    std::cout << argv[0] << " Version " << SimpList_VERSION_MAJOR << "."
        << SimpList_VERSION_MINOR << std::endl;
    //const double inputValue = std::stod(argv[1]);
    
    TodoController mainController = TodoController();

    /*
    Main entrance to the cli.
    First argument of interface is the operation to perform.
    Format:
        SimpList create [listName]
    Operations:
        create - creat list
        
        
    */

    return 0;
}

