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
            listFiles.push_back(current_file.substr(iPos + 1,fPos - 1));
        }
    }


    //Load if any files are found.
    if(listFiles.size() > 0)
    {
        for(auto file = listFiles.begin(); file != listFiles.end(); ++file)
        {
            listWrapper = ListItemLoadWrapper();
            std::cout << *file << std::endl;
            listWrapper.loadFromFile(*file);

            //Create starter objects.
            priorityQueueTodo * toAdd = new priorityQueueTodo(*file);

            //Add list Items to starter objects.
            for(auto item = listWrapper.wrapArray.begin(); item != listWrapper.wrapArray.end(); ++item)
            {
                toAdd->addTodoItem(item,1.0);
            }
            //Store address of list in lists fector
            lists.push_back(toAdd);
        }
    }

}


TodoController::~TodoController()
{
    //Iterate and save each list.
    for(auto list = lists.begin(); list != lists.end(); ++list)
    {
        listWrapper = ListItemLoadWrapper();
        //Pop head, null at end of queue.
        ListItem * head = *list->popHead();
        while(head)
        {
            //Add list to wrapper.
            listWrapper.addItem(*(head));
            head = *list->popHead();
        }

        listWrapper.writeToFile(*list->getName() + ".list");
        
        //Free the memory
        delete *list;
    }

}


std::vector<std::string> TodoController::getLists()
{
    std::vector<std::string> toReturn;

    for(auto list = lists.begin(); list != lists.end(); ++list)
    {
        toReturn.push_back(*list->getName());

        //List Title.
        std::cout << "List: " << *list->getName() << std::endl;
        //print
        *list->printTodo();
    }

    return toReturn;
}


void TodoController::addToList(std::string listName);
{
    
}