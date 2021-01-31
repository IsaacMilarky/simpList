#Makefile for simpList application.
BUILD_FILES ?= ListItem.o main.o priorityTodoQueue.o simpList


simpList : main.o ListItem.o priorityTodoQueue.o
#compile into a file called simpList
	g++ main.o ListItem.o priorityTodoQueue.o -o simpList

#-----------------------------------------------------------------

main.o : main.cpp priorityTodoQueue.hpp ListItem.hpp
	g++ -c main.cpp

ListItem.o : ListItem.cpp ListItem.hpp
	g++ -c ListItem.cpp

priorityTodoQueue.o : priorityTodoQueue.cpp priorityTodoQueue.hpp ListItem.hpp
	g++ -c priorityTodoQueue.cpp


.PHONY: clean

clean:
	$(RM) -r $(BUILD_FILES)
