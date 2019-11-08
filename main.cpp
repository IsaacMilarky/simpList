#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "priorityTodoQueue.hpp"

int main()
{
	auto pqtd = priorityQueueTodo();

	for(int iter = 0; iter < 20; iter++)
	{
		ListItem * ptr = new ListItem("Item " + std::to_string(iter));
		std::time_t now = std::time(0);

		ptr->setDeadLine(now + 1000000);
		pqtd.addTodoItem(ptr,10.0/((float)iter));
	}

	pqtd.printTodo();

	return 0;
}
