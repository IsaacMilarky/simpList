# simpList
Simple to do list written in c++.


This project was originally started long ago when I was a freshman. I now am going back to it and want to make it into *something* presentable.

The crux of my design is using the data structs I have learned about in class to create a fast and efficiant todo list with dynamic features.

The primary data structure used in my design is a priority queue that acts as the dynamic storage for the todo list data. When data is being actively looked at it should be somewhere within a priorityQueTodo object. The priorityQueue is how the actual *list* of a todo list is represented conceptually.

The secondary data structure I have yet to implement is a hash table to store list items in a more permanent fasion in an easily retreiveable manner. This will be a fairly simple design although considerations need to be made for storage overlap. The exact method of serialization will also need to be designed.

Thirdly, the data in the todoList will need to be represented somehow. I plan to make this application solely cli-based and intended for programmers (mainly just practice I don't expect to be too useful). However, given I have time this semester I will make a gui that interacts with the underlying processes. 

I am now adding boost libraries to the project. Boost is unzipped in /libs.
