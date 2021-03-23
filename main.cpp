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


int main(int argc, char * argv[])
{
    //I'm going to handle arguments asm style with pointer addition.
    //Addition only really happens when optionals are used like -m
    char ** argumentPointer = argv;
    //Print Version number
    std::cout << argumentPointer[0] << " Version " << SimpList_VERSION_MAJOR << "."
        << SimpList_VERSION_MINOR << std::endl;
    
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

    std::string testOptional = std::string(argumentPointer[1]);
    if(testOptional.find("-") != std::string::npos)
    {
        //verbosity option.
        if(testOptional.find("v") != std::string::npos)
            std::cout << "Optional invoked." << std::endl;
        argumentPointer++;

        //Test options to see if minimal option is selected.
        if(testOptional.find("m") != std::string::npos)
            mainController.togglePrompts();
    }

    std::string operation = std::string(argumentPointer[1]);

    if(operation == "create")
    {
        //exception handling for too many args
        if(argumentPointer[3] != NULL)
            throw "Too many arguments for cohearant list creation!"; 
        mainController.addList(std::string(argumentPointer[2]));
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
        //std::cout << "ARG 2 : "<< argumentPointer[2] << std::endl;
        if(argumentPointer[2])
            listName = std::string(argumentPointer[2]);
        else
            throw "No list specified!";
        
        //List item name
        //std::cout << "ARG 3 : "<< argumentPointer[3] << std::endl;
        if(argumentPointer[3])
            itemName = std::string(argumentPointer[3]);
        else
            throw "No item specified to add to list!";

        //List body text
        //std::cout << "ARG  4: "<< argumentPointer[4] << std::endl;
        if(argumentPointer[4])
            itemBody = std::string(argumentPointer[4]);
        else
            itemBody = "";

        //std::cout << "ARG  5: "<< argumentPointer[5] << std::endl;
        if(argumentPointer[5] && argumentPointer[4])
            itemDeadline = boost::gregorian::from_string(std::string(argumentPointer[5]));
        else  
            itemDeadline = boost::gregorian::date();
        
        //Deadline time
        //Format: 3:00PM
        //std::cout << "ARG  6: "<< argumentPointer[6] << std::endl;
        if(argumentPointer[6])
            timeValue = std::string(argumentPointer[6]);
        else
            timeValue = "";
        
        mainController.addToList(listName,itemName,itemDeadline,timeValue,itemBody);

    }
    else if(operation == "delete")
    {
        if(argumentPointer[3] != NULL)
            throw "Too many arguments for cohereant list creation!";
        mainController.deleteList(std::string(argumentPointer[2]));
    }
    else if(operation == "update")
    {
        if(argumentPointer[3] != NULL)
            throw "Too many arguments for update call!";
        
        mainController.checkDeadLines();
    }
    else if(operation == "show")
    {
        if(argumentPointer[2] == NULL)
            throw "No list specified!";
        
        mainController.showList(std::string(argumentPointer[2]));
    }
    else
        throw "Invalid arguments given!";

    return 0;
}

