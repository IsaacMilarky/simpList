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
    BOOST_TEST_MESSAGE("running test create list");
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
}

BOOST_AUTO_TEST_CASE(test_load_from_file)
{
    TodoController controller = TodoController();
    controller.showLists();
}

BOOST_AUTO_TEST_CASE(test_add_list)
{
    TodoController controller = TodoController();
    controller.addList("Example");

    std::vector<std::string> controlLists = controller.getLists();

    BOOST_TEST(contains(&controlLists,"Example"));
}

BOOST_AUTO_TEST_CASE(test_delete_list)
{
    TodoController controller = TodoController();
    std::string listName = "readWriteExample";
    controller.deleteList(listName);

    std::vector<std::string> controlLists = controller.getLists();

    BOOST_TEST(!contains(&controlLists,"readWriteExample"));
}


//Empty list tests.
BOOST_AUTO_TEST_CASE(test_show_empty_list)
{
    TodoController controller = TodoController();
    controller.addList("Empty");
    controller.showList("Empty");
}

BOOST_AUTO_TEST_CASE(test_delete_empty_list)
{
    TodoController controller = TodoController();
    std::string listName = "Empty";
    controller.deleteList(listName);


    std::vector<std::string> controlLists = controller.getLists();
    BOOST_TEST(!contains(&controlLists,"Empty"));
}


BOOST_AUTO_TEST_CASE(test_add_to_empty_list)
{
    TodoController controller = TodoController();
    controller.addList("emptyTest");
    boost::gregorian::date dead(2002,1,10);
    controller.addToList("emptyTest","NewInEmpty",dead,"3:00PM","AllArgsUsed");

    std::cout << "Failure\n";
    controller.showLists();
    controller.showList("emptyTest");
}
