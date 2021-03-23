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
    BOOST_TEST(controller.showList("emptyTest").find("NewInEmpty") != std::string::npos);
    std::cout << "-----------------------TEST END------------------\n";
}

BOOST_AUTO_TEST_CASE(test_edit_list_item)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();

    boost::gregorian::date dead(2002,2,10);
    controller.editList("emptyTest","NewInEmpty",dead,"4:00AM","AllArgs");

    //Make sure time is now differant in output.
    BOOST_TEST(controller.showList("emptyTest").find("3:00PM") == std::string::npos);
    std::cout << "-----------------------TEST END------------------\n";
}

const static unsigned int LIST_LOAD_SIZE = 50;
const static std::string LIST_FILE_LOAD = "exampleLoadTest.list";
//Wrapper tests.
BOOST_AUTO_TEST_CASE(test_heavy_wrapper_load)
{
    std::cout << "-----------------------STARTING TEST------------------\n";

    std::vector<ListItem> verifyCopies;

    {
        ListItemLoadWrapper wrapper = ListItemLoadWrapper();
    
        for(unsigned int iter = 0; iter < LIST_LOAD_SIZE; ++iter)
        {
            //Create Object.
            ListItem toAdd = ListItem("Example item " + (char)('0' + iter));
            toAdd.setTodoBody("Standard body");

            //Push object to be stored into two differant vectors.
            wrapper.addItem(&toAdd);
            verifyCopies.push_back(toAdd);
        }

        //Pickle the archive
        wrapper.writeToFile(LIST_FILE_LOAD);
    }

    ListItemLoadWrapper loader = ListItemLoadWrapper();
    loader.loadFromFile(LIST_FILE_LOAD);

    //Load and compare loaded vector to pre loaded vector.
    for(unsigned int iter = 0; iter < loader.wrapArray.size(); ++iter)
    {
        std::string loadName = loader.wrapArray.at(iter).getTodoName();
        BOOST_TEST(loadName == verifyCopies.at(iter).getTodoName());
    }

    std::cout << "-----------------------TEST END------------------\n";
}

//Test scheduling method.
BOOST_AUTO_TEST_CASE(test_check_dead_lines)
{
    std::cout << "-----------------------STARTING TEST------------------\n";
    TodoController controller = TodoController();

    //Create list to pump full of deadlines
    controller.addList("deadLines");
    //Example items that SHOULD NOT get output
    controller.addToList("deadLines","NotDue",boost::gregorian::from_string("2024/1/1"),"3:00PM","This is not due");

    controller.addToList("deadLines","NotDueToo",boost::gregorian::from_string("2020/1/1"),"3:00PM","This is not due");

    BOOST_TEST(controller.checkDeadLines().find("NotDue") == std::string::npos);

    //Example items that SHOULD get output.
    boost::posix_time::ptime local = boost::posix_time::second_clock::local_time();
    std::string hourString = local.time_of_day().hours() + ":" + (local.time_of_day().minutes() + 2);
    controller.addToList("deadLines","NotDueToo",local.date(),hourString,"This is not due");

    BOOST_TEST(controller.checkDeadLines().find("NotDue") != std::string::npos);

    //Add some far away dates that should not illicit a response.
    std::cout << "-----------------------TEST END------------------\n";
}