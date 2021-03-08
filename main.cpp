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
    //Print Version number
    std::cout << argv[0] << " Version " << SimpList_VERSION_MAJOR << "."
        << SimpList_VERSION_MINOR << std::endl;
    //const double inputValue = std::stod(argv[1]);
    
    ListItem g("HelloWorld");
    g.setTodoBody("Good morning world and all who inhabit it!");
    
    //Wrapper _should_ handle overhead presented by multi-serialization.
    ListItemLoadWrapper wrapper = ListItemLoadWrapper();
    wrapper.addItem(g);
    wrapper.writeToFile(LISTITEM_STORE);
    wrapper = ListItemLoadWrapper();
    wrapper.loadFromFile(LISTITEM_STORE);

    //wrapper.wrapArray.at(0).print();

    TodoController controller = TodoController();
    controller.getLists();

    
}

