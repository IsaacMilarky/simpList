#include "ListItemLoadWrapper.hpp"

ListItemLoadWrapper::ListItemLoadWrapper()
{
    
}

ListItemLoadWrapper::~ListItemLoadWrapper()
{

}

void ListItemLoadWrapper::addItem(ListItem * toAdd)
{
    wrapArray.push_back(*toAdd);
}

void ListItemLoadWrapper::loadFromFile(std::string filename)
{
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);

    ia >> *this;
    ifs.close();
}

void ListItemLoadWrapper::writeToFile(std::string filename)
{
    std::ofstream ofs(filename);

    //Save to archive
    {
        boost::archive::text_oarchive oa(ofs);
        //Dereference self and write.
        oa << *this;
    }
    ofs.close();
}
