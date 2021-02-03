#Makefile for simpList application.
BUILD_FILES ?= ListItem.o main.o priorityTodoQueue.o simpList
CC = g++
BASE_FLAGS = -Wall

#Base directory and boost directory for headers.
LDFLAGS = -I libs/boost_1_71_0

#Base directory and boost directory for lib files.
LLIBFLAGS = -L/libs/lib

#Link options
LINKSUFFIX = \-Llibs/lib/ -lboost_regex -lboost_serialization
LINKFLAGS = -lboost_regex -lboost_serialization

FLAGS = $(BASE_FLAGS)  $(LLIBFLAGS) $(LINKFLAGS) 

simpList : main.o ListItem.o priorityTodoQueue.o
#compile into a file called simpList
	$(CC) $(BASE_FLAGS) $(LDFLAGS) main.o ListItem.o priorityTodoQueue.o -o simpList $(LINKSUFFIX)

#-----------------------------------------------------------------

main.o : main.cpp priorityTodoQueue.hpp ListItem.hpp
	$(CC) $(BASE_FLAGS) $(LLIBFLAGS) -c main.cpp

ListItem.o : ListItem.cpp ListItem.hpp
	$(CC) $(BASE_FLAGS) $(LLIBFLAGS) -c ListItem.cpp

priorityTodoQueue.o : priorityTodoQueue.cpp priorityTodoQueue.hpp ListItem.hpp
	$(CC) $(BASE_FLAGS) $(LLIBFLAGS) -c priorityTodoQueue.cpp


.PHONY: clean

clean:
	$(RM) -r $(BUILD_FILES)