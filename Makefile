#Makefile for simpList application.
BUILD_FILES ?= ListItem.o main.o priorityTodoQueue.o simpList
CC = g++
BASE_FLAGS = -m64 -Wall

#Base directory and boost directory for headers.
LDFLAGS = -I./libs/boost_1_71_0

#Base directory and boost directory for lib files.
#LLIBFLAGS = -L/usr/local/Cellar/boost/1.75.0_1 -L/root/boost_1_71_0/stage/lib

#Link options
#LINKFLAGS = -l boost_thread-mt -lboost_system

FLAGS = $(BASE_FLAGS) $(LDFLAGS) #$(LINKFLAGS) $(LLIBFLAGS) 

simpList : main.o ListItem.o priorityTodoQueue.o
#compile into a file called simpList
	$(CC) $(FLAGS) main.o ListItem.o priorityTodoQueue.o -o simpList

#-----------------------------------------------------------------

main.o : main.cpp priorityTodoQueue.hpp ListItem.hpp
	$(CC) $(FLAGS) -c main.cpp

ListItem.o : ListItem.cpp ListItem.hpp
	$(CC) $(FLAGS) -c ListItem.cpp

priorityTodoQueue.o : priorityTodoQueue.cpp priorityTodoQueue.hpp ListItem.hpp
	$(CC) $(FLAGS) -c priorityTodoQueue.cpp


.PHONY: clean

clean:
	$(RM) -r $(BUILD_FILES)
