#include "TodoController.hpp"
#include <cmath>

static std::string listStringLocation = std::string(getenv("HOME")) + std::string("/.simplist");

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
    //Prompts are true by default.
    this->prompts = true;
    //Load all .list Items from file.
    std::vector<std::string> listFiles;

    //Lists are user specific 
    boost::filesystem::path p(listStringLocation);
    if(!boost::filesystem::exists(p))
        boost::filesystem::create_directory(p);

    //std::cout << listStringLocation << std::endl;

    boost::filesystem::directory_iterator end_itr;

    //cycle through directory.
    for(boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        std::string current_file = itr->path().string();
        //If it's not a directory, list it. remove this check to also list dirs
        if(boost::filesystem::is_regular_file(itr->path()) && hasEnding(current_file,".list"))
        {
            std::size_t iPos = current_file.find_last_of("/");
            std::size_t fPos = current_file.find(".list");

            //std::cout << current_file.substr(iPos + 1,fPos - 1) << std::endl;
            listFiles.push_back(current_file.substr(iPos + 1));
        }
    }


    for(int iter = 0; iter < listFiles.size(); iter++)
    {
        //Load from file, This is tricky as hell beware.
        ListItemLoadWrapper loadFromDrive = ListItemLoadWrapper();
        //std:: cout << "Loading.. ";
        //std::cout << listStringLocation + "/" + listFiles.at(iter) << std::endl;
        loadFromDrive.loadFromFile(listStringLocation + "/" + listFiles.at(iter));

        //Load Each item into a PQ. strip the file extension.
        std::size_t iPos = listFiles.at(iter).find(".");
        //std::cout << listFiles.at(iter).substr(0,iPos) << std::endl;
        priorityQueueTodo * newList = new priorityQueueTodo(listFiles.at(iter).substr(0,iPos));

        //Add each loaded listitem into the pq by address.
        for(int item = 0; item < loadFromDrive.wrapArray.size(); item++)
        {
            newList->addTodoItem(&loadFromDrive.wrapArray.at(item),1.0);
        }

        //newList->prioritizeByDateCreated();
        //Add to class
        lists.push_back(newList);
    }
        

}

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

        //std::cout << listStringLocation + "/" + lists.at(iter)->getName() + ".list" << std::endl;
        saveToDrive.writeToFile(listStringLocation + "/" + lists.at(iter)->getName() + ".list");
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
    }

    return toReturn;
}

std::string TodoController::showLists()
{
    std::string toPrint = "";
    for(unsigned int iter = 0; iter < lists.size(); ++iter)
    {
        //List Title.
        toPrint += "List: " + lists.at(iter)->getName() + "\n";
        std::cout << "List: " << lists.at(iter)->getName() << "\n";
        //print
        toPrint += lists.at(iter)->printTodo();
    }

    return toPrint;
}

void TodoController::addList(std::string listName)
{
    priorityQueueTodo * newList = new priorityQueueTodo(listName);
    lists.push_back(newList);
}

//This is too bloated and needs to be subdivided.
void TodoController::addToList(std::string list, std::string name,boost::gregorian::date date,std::string hourMin, std::string bodyText)
{
    priorityQueueTodo * listRef = this->getList(list);

    if(listRef != nullptr)
    {
        //Prompts for adding new list item.
        std::string itemName;
        std::string itemBody;
        boost::posix_time::ptime deadLine;

        std::string prompt;

        //prompt for name if none given and prompts are on.
        if(name.empty() && this->prompts)
        {
            //Get data from user
            std::cout << "Please input item name: ";
            getline(std::cin,itemName);
        }
        else if(name.empty())
        {
            itemName = "No name given!";
        }
        else
        {
            itemName = name;
        }

        if(date.is_not_a_date() && this->prompts)
        {
            //Ask if they want to add a deadline.
            std::cout << "Would you like to add a deadline? (y/n): ";
            getline(std::cin, prompt);

            if(prompt.compare("y") == 0 || prompt.compare("Y") == 0)
            {
                deadLine = this->promptDate();
            }   
            //If not Y deadLine => not_a_date_time
        }
        else if (!date.is_not_a_date())
        {
            deadLine = this->promptDate(date,hourMin);
        }
        //In implicit case deadline => not_a_date_time,
        
        if(bodyText == "" && this->prompts)
        {
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
        }
        else if (bodyText == "")
        {
            //Case where prompts are off and no prompt is given in argument.
            itemBody = "";
        }
        else
            itemBody = bodyText;

        

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

        toAdd.print();
        listRef->addTodoItem(&toAdd,1.0);
        listRef->prioritizeByDateCreated();
    }
    else
        std::cout << "List Entered was not found." << std::endl;
}

void TodoController::editList(std::string list, std::string name,boost::gregorian::date date,std::string hourMin, std::string bodyText)
{
    priorityQueueTodo * listRef = this->getList(list);
    ListItem * itemRef = listRef->getItem(name);
    if(listRef != nullptr || itemRef != nullptr)
    {
        std::string itemBody;

        boost::posix_time::ptime deadLine;
        std::string prompt;

        //Get data from user
        std::cout << "Please input item name (blank for no change): ";
        getline(std::cin,prompt);

        //If response is recorded, change name of reference. 
        if(!prompt.empty())
        {
            itemRef->setTodoName(prompt);
        }

        if(date.is_not_a_date())
        {
            //Ask if they want to add a deadline.
            std::cout << "Would you like to change a deadline? (y/n): ";
            getline(std::cin, prompt);

            if(prompt.compare("y") == 0 || prompt.compare("Y") == 0)
            {
                deadLine = this->promptDate();
            }   
            //If not Y deadLine => not_a_date_time
        }
        else
        {
            deadLine = this->promptDate(date,hourMin);
        }

        //Update heap reference.
        itemRef->setDeadLine(deadLine);

        if(bodyText == "")
        {
            //ask if they want an item body.
            std::cout << "Would you like to change the body? (y/n): ";
            getline(std::cin,prompt);
            if(prompt.compare("y") == 0 || prompt.compare("Y") == 0)
            {
                std::cout << "Enter body: ";
                getline(std::cin,itemBody);
                std::cout << std::endl;
            }
            else
            {
                //Quick default fix.
                itemBody = itemRef->getTodoBody();
            }
        }
        else
            itemBody = bodyText;
        
        //Update ref.
        itemRef->setTodoBody(itemBody);
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

//O(n)
void TodoController::deleteList(std::string listName)
{

    boost::filesystem::path p(listStringLocation);

    boost::filesystem::directory_iterator end_itr;

    //cycle through directory.
    for(boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        std::string current_file = itr->path().string();
        //If it's not a directory, list it. remove this check to also list dirs
        //Also checks if filename contains the listName _somewhere_ in it.
        if(boost::filesystem::is_regular_file(itr->path()) 
            && hasEnding(current_file,".list") 
            && current_file.find(listName) != std::string::npos)
        {
            boost::filesystem::remove(itr->path());
        }
    }

    //Find list with name list
    for(unsigned int iter = 0; iter < lists.size(); ++iter)
    {
        //Test each list
        if(lists.at(iter)->getName().compare(listName) == 0)
        {
            priorityQueueTodo * toDelete = lists.at(iter);
            //Remove from vector by index.
            //Erase lists[iter]
            lists.erase(lists.begin() + iter);
            delete toDelete;
            //Deletion found. exit.
            return;
        }
    }

    std::cout << "No list found to remove" << std::endl;
}

void TodoController::deleteListItem(std::string list, std::string itemName)
{
    priorityQueueTodo * listRef = this->getList(list);
    listRef->deleteItem(itemName);
}

std::string TodoController::showList(std::string listName)
{
    //this->getList(listName)->printTodo();
    //Check for empty
    std::string toPrint = "";
    priorityQueueTodo * someList = this->getList(listName);
    std::cout << "Showing list " << someList->getName() << ":\n";
    toPrint += someList->getName() + '\n';

    if(someList != nullptr)
        toPrint += someList->printTodo();
    else
    {
        std::cout << "List Not Found!" << std::endl;
        toPrint += "List Not Found!\n";
    }

    return toPrint;
}

//O(n^2) fix in the future.
std::string TodoController::checkDeadLines()
{
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    //Vector to hold data to print.
    std::vector<ListItem *> toPrint;
    //Vector to hold data thats around a day away
    std::vector<ListItem *> lateToPrint;
    //String to hold data to print
    std::string printString = "";
    //Check deadlines in all lists.
    //Notify if deadline is less than five minutes away.
    for(unsigned int iter = 0; iter < lists.size(); ++iter)
    {
        //use node to iterate through list.
        Node * headRef = lists.at(iter)->getHead();

        for(Node * iter = headRef; iter; iter = iter->next)
        {
            //This scope is the reference for every ListItem
            ListItem * itemRef = iter->key;
            boost::posix_time::ptime stopDate = itemRef->getDeadLine();
            //If deadLine not null
            if(!stopDate.is_not_a_date_time())
            {
                //Time elapsed
                boost::posix_time::time_duration diff = stopDate - now;
                if(std::abs(diff.total_seconds()) <= 120)
                {
                    toPrint.push_back(itemRef);
                }
                else if(std::abs(diff.total_seconds()) <= 86400)
                {
                    //Else if less than a day away
                    lateToPrint.push_back(itemRef);
                }
            }
        }
    }

    if(!toPrint.empty())
        std::cout << toPrint.size() << " events are due in the near future!\n" << std::endl;
    else
        std::cout << "No events are due in the near future!\n" << std::endl;
    
    for(unsigned int iter = 0; iter < toPrint.size(); iter++)
    {
        printString += toPrint.at(iter)->print();
        std::cout << "---------------------------------------" << std::endl;
    }

    if(!lateToPrint.empty())
        std::cout << lateToPrint.size() << " events due less than a day from now!\n" << std::endl;
    
    for(unsigned int iter = 0; iter < lateToPrint.size(); iter++)
    {
        printString += lateToPrint.at(iter)->print();
        std::cout << "---------------------------------------" << std::endl;
    }

    return printString;
}

void TodoController::togglePrompts()
{
    this->prompts = !this->prompts;
}

///PRIVATE
boost::posix_time::ptime TodoController::promptDate(boost::gregorian::date date, std::string hourMin)
{
    //if i need to prompt.
    if(date.is_not_a_date())
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
        if(hourMin.compare("") == 0)
            return boost::posix_time::ptime(boost::gregorian::date(year,month,day), this->promptTime());
        else
            return boost::posix_time::ptime(boost::gregorian::date(year,month,day), this->promptTime(hourMin));   
    }
    else
    {
        //Prompt for hour:minute in return constructor.
        if(hourMin.compare("") == 0)
            return boost::posix_time::ptime(date, this->promptTime());
        else
            return boost::posix_time::ptime(date, this->promptTime(hourMin));
    }
    
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
boost::posix_time::time_duration TodoController::promptTime(std::string hourMin)
{
    //Get offset from start of day in hours and minute.
    //Defaults to midnight, e.g. (0,0)
    std::string prompt;
    short int hours, minutes;

    if(hourMin.empty())
    {
        std::cout << "Please input time of day: ";
        getline(std::cin,prompt);
    }
    else
    {
        prompt = hourMin;
    }
    
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