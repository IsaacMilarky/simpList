#Makefile for simpList application.
BUILD_FILES ?= ListItem.o main.o priorityTodoQueue.o simpList
CC = g++
BASE_FLAGS = -Wall 

#Base directory and boost directory for headers.
LDFLAGS = -Ilibs/boost_1_71_0

#Base directory and boost directory for lib files.
LLIBFLAGS = -Llibs/lib

#Link options
LINKSUFFIX = \libs/lib/libboost_serialization.a
LINKFLAGS = -lboost_serialization

FLAGS = $(BASE_FLAGS)  $(LLIBFLAGS) $(LINKFLAGS) 

simpList : main.o ListItem.o priorityTodoQueue.o
#compile into a file called simpList
	$(CC) $(BASE_FLAGS) $(LDFLAGS) $(LLIBFLAGS) main.o ListItem.o priorityTodoQueue.o -o simpList $(LINKSUFFIX) $(LINKFLAGS)

#-----------------------------------------------------------------

ListItem.o : ListItem.cpp ListItem.hpp
	$(CC) $(BASE_FLAGS) $(LDFLAGS) -c ListItem.cpp

main.o : main.cpp priorityTodoQueue.hpp ListItem.hpp
	$(CC) $(BASE_FLAGS) $(LDFLAGS) -c main.cpp 


priorityTodoQueue.o : priorityTodoQueue.cpp priorityTodoQueue.hpp ListItem.hpp
	$(CC) $(BASE_FLAGS) $(LDFLAGS) -c priorityTodoQueue.cpp


.PHONY: clean

clean:
	$(RM) -r $(BUILD_FILES)