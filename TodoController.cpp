#include "TodoController.hpp"

bool hasEnding(std::string const &fullString, std::string const &ending)
{
    if(fullString.length() >= ending.length())
    {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
        return false;
    }
}

TodoController::TodoController()
{
    //Load all .list Items from file.
    std::vector<std::string> listFiles;

    boost::filesystem::path p(".");

    boost::filesystem::directory_iterator end_itr;

    //cycle through directory.
    for(boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        std::string current_file = itr->path().string();
        //If it's not a directory, list it. remove this check to also list dirs
        if(boost::filesystem::is_regular_file(itr->path()) && hasEnding(current_file,".list"))
        {
            std::size_t iPos = current_file.find("/");
            //std::size_t fPos = current_file.find(".list");

            //std::cout << current_file.substr(iPos + 1,fPos - 1) << std::endl;
            listFiles.push_back(current_file.substr(iPos + 1));
        }
    }


    for(int iter = 0; iter < listFiles.size(); iter++)
    {
        //Load from file, This is tricky as hell beware.
        ListItemLoadWrapper loadFromDrive = ListItemLoadWrapper();
        //std::cout << listFiles.at(iter) << std::endl;
        loadFromDrive.loadFromFile(listFiles.at(iter));

        //Load Each item into a PQ.
        priorityQueueTodo * newList = new priorityQueueTodo(listFiles.at(iter));

        //Add each loaded listitem into the pq by address.
        for(int item = 0; item < loadFromDrive.wrapArray.size(); item++)
        {
            newList->addTodoItem(&loadFromDrive.wrapArray.at(item),1.0);
        }

        //Add to class
        lists.push_back(newList);
    }
        

}

///TODO:Saving list body corrupts data, find out why.
//Seems to have to do with listWrapper being reset. Use it differantly.
TodoController::~TodoController()
{
    //Iterate and save each list.
    for(unsigned int iter = 0; iter < lists.size(); ++iter)
    {
        ListItemLoadWrapper saveToDrive = ListItemLoadWrapper();

        ListItem * head = lists.at(iter)->popHead();

        while(head)
        {
            saveToDrive.addItem(head);
            head = lists.at(iter)->popHead();
        }

        saveToDrive.writeToFile("test");
        //delete data
        delete lists.at(iter);
    }

}


std::vector<std::string> TodoController::getLists()
{
    std::vector<std::string> toReturn;

    for(unsigned int iter = 0; iter < lists.size(); ++iter)
    {
        toReturn.push_back(lists.at(iter)->getName());

        //List Title.
        std::cout << "List: " << lists.at(iter)->getName() << std::endl;
        //print
        lists.at(iter)->printTodo();
    }

    return toReturn;
}

