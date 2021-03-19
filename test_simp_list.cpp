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

    bool contains = false;
    for(unsigned int iter = 0; iter < controlLists.size(); ++iter)
    {
        if(controlLists.at(iter) == listName)
            contains = !contains;
    }

    BOOST_TEST(contains);
}
