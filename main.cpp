#include "priorityTodoQueue.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    ///Testing serialization of ListItem
    std::ofstream ofs("filename");

    const ListItem g("HelloWorld");

    //Save to archive
    {
        boost::archive::text_oarchive oa(ofs);
        oa << g;
    }

    ListItem newItem;
    {
        //create and open for input
        std::ifstream ifs("filename");
        boost::archive::text_iarchive ia(ifs);
        //Read class state from archive.
        ia >> newItem;
    }

    newItem.print();
}

