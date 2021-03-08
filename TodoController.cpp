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
            std::size_t fPos = current_file.find(".list");

            std::cout << current_file.substr(iPos + 1,fPos - 1) << std::endl;
            listFiles.push_back(current_file.substr(iPos + 1));
        }
    }


    //Load if any files are found.
    if(listFiles.size() > 0)
    {
        for(unsigned int iter = 0; iter < listFiles.size(); ++iter)
        {
            listWrapper = ListItemLoadWrapper();
            std::cout << listFiles.at(iter) << std::endl;
            listWrapper.loadFromFile(listFiles.at(iter));

            std::size_t fPos = listFiles.at(iter).find(".list");
            //Create starter objects.
            priorityQueueTodo * toAdd = new priorityQueueTodo(listFiles.at(iter).substr(0,fPos));

            //Add list Items to starter objects.
            for(auto item = listWrapper.wrapArray.begin(); item != listWrapper.wrapArray.end(); ++item)
            {
                toAdd->addTodoItem(&(*item),1.0);
            }
            //Store address of list in lists fector
            lists.push_back(toAdd);
        }
    }

}


TodoController::~TodoController()
{
    //Iterate and save each list.
    for(unsigned int iter = 0; iter < lists.size(); ++iter)
    {
        listWrapper = ListItemLoadWrapper();
        //Pop head, null at end of queue.
        ListItem * head = lists.at(iter)->popHead();
        while(head)
        {
            //Add list to wrapper.
            listWrapper.addItem(*(head));
            head = lists.at(iter)->popHead();
        }

        listWrapper.writeToFile(lists.at(iter)->getName() + ".list");
        
        //Free the memory
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

