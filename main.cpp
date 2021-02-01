#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "priorityTodoQueue.hpp"

/*
	Note:
	Ok, so basically i'm gonna make this cli and
	then just add more and more features from there.
	Hopefully, this project won't be cli forever.
*/

const static std::time_t NOW = std::time(0);

int main(int argc, char* argsv[])
{
	auto pqtd = priorityQueueTodo();

	for(int iter = 1; iter < 20; iter++)
	{
		ListItem * ptr = new ListItem("Item " + std::to_string(iter));
		std::time_t now = std::time(0);

		std::tm * endDate = std::localtime(&now);
		endDate->tm_mon = endDate->tm_mon + iter;

		ptr->setDeadLine(*endDate);
		pqtd.addTodoItem(ptr,10.0/((float)iter));
	}

	pqtd.prioritizeByDeadLine();
	pqtd.printTodo();

	ListItem* yo = pqtd.popHead();
	std::cout << "\n\nyo:\n";
	yo->print();

	return 0;
}
