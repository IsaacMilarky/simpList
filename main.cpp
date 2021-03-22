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
        SimpList add [listName] [Item Name]
    Operations:
        create - create list
        add - add to List
        
        
    */


   ///TODO: Add support for argument optionals. Ex: -m would turn off prompting and just use defaults for adding and editing.
    std::string operation = std::string(argv[1]);

    if(operation == "create")
    {
        //exception handling for too many args
        if(argc != 3)
            throw "Too many arguments for cohearant list creation!"; 
        mainController.addList(std::string(argv[2]));
    }
    else if(operation == "add")
    {
        /*
            For adding to lists:
                Format is SimpList add [listname] [itemname] [itemBody] [date] [time]
            
        */
        //Get the arguments as strings
        std::string listName, itemName, itemBody;
        //Get date argument as string.
        boost::gregorian::date itemDeadline;
        std::string timeValue;
        //List title
        if(argv[2])
            listName = std::string(argv[2]);
        else
            throw "No list specified!";
        
        //List item name
        if(argv[3])
            itemName = std::string(argv[3]);
        else
            throw "No item specified to add to list!";

        //List body text
        if(argv[4])
            itemBody = std::string(argv[4]);
        else
            itemBody = "";
        
        //Deadline date
        //From delimited date string where with order year-month-day eg: 2002-1-25
        if(argv[5])
            itemDeadline = boost::gregorian::date(boost::gregorian::from_string(std::string(argv[5])));
        else
            itemDeadline = boost::gregorian::date();
        
        //Deadline time
        //Format: 3:00PM
        if(argv[6])
            timeValue = std::string(argv[6]);
        else
            timeValue = "";
        
        mainController.addToList(listName,itemName,itemDeadline,timeValue,itemBody);

    }
    else if(operation == "delete")
    {
        if(argc != 3)
            throw "Too many arguments for cohereant list creation!";
        mainController.deleteList(std::string(argv[2]));
    }
    else if(operation == "update")
    {
        if(argc != 3)
            throw "Too many arguments for update call!";
        
        mainController.checkDeadLines();
    }
    else if(operation == "show")
    {
        if(argc != 3)
            throw "No list specified!";
        
        mainController.showList(std::string(argv[2]));
    }
    else
        throw "Invalid arguments given!";

    return 0;
}

