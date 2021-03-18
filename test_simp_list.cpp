#define BOOST_TEST_MODULE SimpList Tests
#include <boost/test/included/unit_test.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/filesystem.hpp>
#include "TodoController.hpp"
#include <fstream>
#include <iostream>
#include <string>
/*
Author: Isaac Milarsky
Created on: 3/18/2021
*/


//Where to save listItems
const std::string LISTITEM_STORE = "listitems.list";

struct testFixture
{
    testFixture()
    {
        testController = TodoController();
    }

    ~testFixture()
    {

    }

    TodoController testController;
};


BOOST_AUTO_TEST_CASE(test_file_load)
{
    //Prepare common controller.
    //testFixture fixture;

    ListItem testItem("example");
    testItem.setTodoBody("exampleText");

    //Write
    {
        ListItemLoadWrapper wrap = ListItemLoadWrapper();
        wrap.addItem(&testItem);
        wrap.writeToFile(LISTITEM_STORE);
    }
    
    //read
    ListItemLoadWrapper read = ListItemLoadWrapper();
    read.loadFromFile(LISTITEM_STORE);

    BOOST_TEST(false == read.wrapArray.empty());
}

BOOST_AUTO_TEST_CASE(test_create_list)
{
    //Prepare common controller.
    testFixture fixture;

    fixture.testController.addList("testList");
    
    
    //Try to get the list out after adding it.
    priorityQueueTodo * testList = fixture.testController.getList("testList");
    std::cout << testList->getName() << "HELLO\n";
    BOOST_TEST(testList->getName() + "" == "testList");
    //std::cout << testList->getName();
}