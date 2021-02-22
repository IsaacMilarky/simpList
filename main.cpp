#include "SimpListConfig.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "ListItem.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char * argv[])
{
    //Print Version number
    std::cout << argv[0] << " Version " << SimpList_VERSION_MAJOR << "."
        << SimpList_VERSION_MINOR << std::endl;
    //const double inputValue = std::stod(argv[1]);
    
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

