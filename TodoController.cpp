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

        saveToDrive.writeToFile(lists.at(iter)->getName());
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

//This is too bloated and needs to be subdivided.
void TodoController::addToList(std::string list)
{
    priorityQueueTodo * listRef = this->getList(list);

    if(listRef != nullptr)
    {
        //Prompts for adding new list item.
        std::string itemName;
        std::string itemBody;
        boost::posix_time::ptime deadLine;

        std::string prompt;

        //Get data from user
        std::cout << "Please input item name: ";
        getline(std::cin,itemName);
        std::cout << std::endl;

        //Ask if they want to add a deadline.
        std::cout << "Would you like to add a deadline? (y/n): ";
        getline(std::cin, prompt);
        std::cout << std::endl;

        if(prompt.compare("y") == 0 || prompt.compare("Y") == 0)
        {
            deadLine = this->promptDate();
        }
        //If not Y deadLine => not_a_date_time

        //ask if they want an item body.
        std::cout << "Would you like to add a body? (y/n): ";
        getline(std::cin,prompt);
        if(prompt.compare("y") == 0 || prompt.compare("Y") == 0)
        {
            std::cout << "Enter body: ";
            getline(std::cin,itemBody);
            std::cout << std::endl;
        }
        else
        {
            itemBody = "";
        }

        //Add item.
        ListItem toAdd;
        
        if(deadLine.is_not_a_date_time())
        {
            toAdd = ListItem(itemName);
        }
        else
            toAdd = ListItem(itemName,deadLine);

        if(itemBody.compare("") != 0)
            toAdd.setTodoBody(itemBody);

        listRef->addTodoItem(&toAdd,1.0);
    }
    else
        std::cout << "List Entered was not found." << std::endl;
}

priorityQueueTodo * TodoController::getList(std::string listName)
{
    //Find list with name list
    for(unsigned int iter = 0; iter < lists.size(); ++iter)
    {
        //Test each list
        if(lists.at(iter)->getName().compare(listName) == 0)
        {
            return lists.at(iter);
        }
    }

    return nullptr;
}

void TodoController::showList(std::string listName)
{
    this->getList(listName)->printTodo();
}

boost::posix_time::ptime TodoController::promptDate()
{
    //Prompt for year. defaults to current year.
    int year;
    year = this->promptYear();
    
    //Prompt for month, defaults to current month.
    int month;
    month = this->promptMonth();
            
    //Prompt for day, defaults to current day.
    int day;
    day = this->promptDay(month);
    
    //Prompt for hour:minute in return constructor.
    return boost::posix_time::ptime(boost::gregorian::date(year,month,day), this->promptTime());
}


int TodoController::promptYear()
{
    std::string prompt;
    std::cout << "Year: ";
    getline(std::cin,prompt);
    if(prompt.empty())
    {
        return boost::posix_time::second_clock::local_time().date().year();
    }
    else
    {
        std::string::size_type sz; //alias of size_t.
        return std::stoi(prompt,&sz); //String to int for prompt.
    }
}

int TodoController::promptMonth()
{
    std::string prompt;
    std::cout << "Month(1-12): ";
    getline(std::cin,prompt);
    std::cout << std::endl;

    if(prompt.empty())
    {
        return boost::posix_time::second_clock::local_time().date().month();
    }
    else
    {
        //Make sure is valid month.
        std::string::size_type sz;
        int month;
        month = std::stoi(prompt,&sz);
        if(month < 1 || month > 12)
            month = boost::posix_time::second_clock::local_time().date().month();
        
        return month;
    }
}

//month is 1-12
int TodoController::promptDay(int month)
{
    //Get how many days are in month.
    boost::gregorian::date d(2002,month,10);
    int howManyDaysInMonth = d.end_of_month().day();
    std::string prompt;

    std::cout << "Day(1-" << howManyDaysInMonth << "): ";
    getline(std::cin,prompt);
    std::cout << std::endl;

    if(prompt.empty())
    {
        return boost::posix_time::second_clock::local_time().date().day();
    }
    else
    {
        int day;
        std::string::size_type sz;
        day = std::stoi(prompt,&sz);
        if(day < 1 || day > howManyDaysInMonth)
        {
            std::cout << "Invalid day!" << std::endl;
            day = boost::posix_time::second_clock::local_time().date().day();
        }
        return day;
    }
}

//This is where a problem is.
boost::posix_time::time_duration TodoController::promptTime()
{
    //Get offset from start of day in hours and minute.
    //Defaults to midnight, e.g. (0,0)
    std::string prompt;
    short int hours, minutes;
    std::cout << "Please input time of day: ";
    getline(std::cin,prompt);
    if(prompt.empty())
    {
        hours = 0;
        minutes = 0;
    }
    else
    {
        std::string::size_type sz;
        //Get hour from input.
        std::string::size_type seperator = prompt.find(":");
        //If ':' exists in response string.
        if(seperator != std::string::npos)
        {
            std::string hourString = prompt.substr(0,seperator);
            hours = std::stoi(hourString,&sz);
        }
       else
       {
           hours = 0;
        }
        

        //Get minute from input
        std::string::size_type beforePM = prompt.find("M");
        --beforePM; //Get either A or P from string.
        if(seperator != std::string::npos && beforePM != std::string::npos)
        {
            std::string minuteString = prompt.substr(seperator + 1,beforePM - 1);
            minutes = std::stoi(minuteString,nullptr,10);
        }
        else
        {
            minutes = 0;
        }

        //If PM exists in the response string
        if(prompt.find("PM") != std::string::npos)
            hours+= 12;
    }

    return boost::posix_time::hours(hours) + boost::posix_time::minutes(minutes);
}