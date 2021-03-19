#define BOOST_TEST_MODULE SimpListTests
#include <boost/test/included/unit_test.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/filesystem.hpp>
#include "TodoController.hpp"
#include <fstream>
#include <iostream>
#include <string>

//Where to save listItems
const std::string LISTITEM_STORE = "listitems.list";

//Utility function because std::algorithm shit the bed earlier.
bool contains(std::vector<std::string>* collection, std::string searchTerm)
{
    bool contains = false;
    for(unsigned int iter = 0; iter < collection->size(); ++iter)
    {
        if(collection->at(iter) == searchTerm)
            contains = !contains;
    }
    return contains;
}


BOOST_AUTO_TEST_CASE(test_list_create)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    ListItem g("Hello World");
    g.setTodoBody("good morning");

    ListItemLoadWrapper wrap = ListItemLoadWrapper();
    wrap.addItem(&g);
    std::string listName = "readWriteExample";
    std::string fileName = listName + ".list";
    wrap.writeToFile(fileName);

    TodoController controller = TodoController();
    std::vector<std::string> controlLists = controller.getLists();

    BOOST_TEST(contains(&controlLists,listName));
    std::cout << "-----------------------TEST END------------------\n";
}

BOOST_AUTO_TEST_CASE(test_load_from_file)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();
    BOOST_TEST(controller.showLists() != "");
    std::cout << "-----------------------TEST END------------------\n";
}

BOOST_AUTO_TEST_CASE(test_add_list)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();
    controller.addList("Example");

    std::vector<std::string> controlLists = controller.getLists();

    BOOST_TEST(contains(&controlLists,"Example"));
    std::cout << "-----------------------TEST END------------------\n";
}

BOOST_AUTO_TEST_CASE(test_delete_list)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();
    std::string listName = "readWriteExample";
    controller.deleteList(listName);

    std::vector<std::string> controlLists = controller.getLists();

    BOOST_TEST(!contains(&controlLists,"readWriteExample"));
    std::cout << "-----------------------TEST END------------------\n";
}


//Empty list tests.
BOOST_AUTO_TEST_CASE(test_show_empty_list)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();
    controller.addList("Empty");
    std::string listShow = controller.showList("Empty");

    //std::cout << listShow << std::endl;
    BOOST_TEST(listShow.find(std::string("Empty")) != std::string::npos);

    std::cout << "-----------------------TEST END------------------\n";
}


BOOST_AUTO_TEST_CASE(test_delete_empty_list)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();
    std::string listName = "Empty";
    controller.deleteList(listName);


    std::vector<std::string> controlLists = controller.getLists();
    BOOST_TEST(!contains(&controlLists,"Empty"));
    std::cout << "-----------------------TEST END------------------\n";
}

// Make sure .list file is deleted from disk after list is deleted. 
BOOST_AUTO_TEST_CASE(test_list_deleted_from_disk)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    std::string listName = "Empty";

    boost::filesystem::path p(".");
    boost::filesystem::directory_iterator end_itr;

    //Look through directory to see if listName exists.
    for(boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        std::string current_file = itr->path().string();
        //Check for file. Make sure is not directory or non-.list
        if(boost::filesystem::is_regular_file(itr->path())
            && current_file.find(listName) != std::string::npos)
        {
            //Failed to delete listName.
            BOOST_TEST(false);        
        }
    }
    std::cout << "-----------------------TEST END-----------------------\n";
}


BOOST_AUTO_TEST_CASE(test_add_to_empty_list)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();
    controller.addList("emptyTest");
    boost::gregorian::date dead(2002,1,10);
    controller.addToList("emptyTest","NewInEmpty",dead,"3:00PM","AllArgsUsed");

    //std::cout << "Failure\n";
    //controller.showLists();
    controller.showList("emptyTest");
    std::cout << "-----------------------TEST END------------------\n";
}

BOOST_AUTO_TEST_CASE(test_edit_list_item)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();

    boost::gregorian::date dead(2002,2,10);
    controller.editList("emptyTest","NewInEmpty",dead,"4:00AM","AllArgs");

    controller.showList("emptyTest");
    std::cout << "-----------------------TEST END------------------\n";
}
