# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /var/lib/snapd/snap/cmake/192/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/cmake/192/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/isaac/Documents/codeStuff/simpList

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/isaac/Documents/codeStuff/simpList

# Include any dependencies generated for this target.
include CMakeFiles/app.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app.dir/flags.make

CMakeFiles/app.dir/main.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/main.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/Documents/codeStuff/simpList/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/app.dir/main.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app.dir/main.o -c /home/isaac/Documents/codeStuff/simpList/main.cpp

CMakeFiles/app.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/isaac/Documents/codeStuff/simpList/main.cpp > CMakeFiles/app.dir/main.i

CMakeFiles/app.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/isaac/Documents/codeStuff/simpList/main.cpp -o CMakeFiles/app.dir/main.s

CMakeFiles/app.dir/ListItem.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/ListItem.o: ListItem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/Documents/codeStuff/simpList/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/app.dir/ListItem.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app.dir/ListItem.o -c /home/isaac/Documents/codeStuff/simpList/ListItem.cpp

CMakeFiles/app.dir/ListItem.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/ListItem.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/isaac/Documents/codeStuff/simpList/ListItem.cpp > CMakeFiles/app.dir/ListItem.i

CMakeFiles/app.dir/ListItem.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/ListItem.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/isaac/Documents/codeStuff/simpList/ListItem.cpp -o CMakeFiles/app.dir/ListItem.s

CMakeFiles/app.dir/priorityTodoQueue.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/priorityTodoQueue.o: priorityTodoQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/isaac/Documents/codeStuff/simpList/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/app.dir/priorityTodoQueue.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app.dir/priorityTodoQueue.o -c /home/isaac/Documents/codeStuff/simpList/priorityTodoQueue.cpp

CMakeFiles/app.dir/priorityTodoQueue.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/priorityTodoQueue.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/isaac/Documents/codeStuff/simpList/priorityTodoQueue.cpp > CMakeFiles/app.dir/priorityTodoQueue.i

CMakeFiles/app.dir/priorityTodoQueue.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/priorityTodoQueue.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/isaac/Documents/codeStuff/simpList/priorityTodoQueue.cpp -o CMakeFiles/app.dir/priorityTodoQueue.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/main.o" \
"CMakeFiles/app.dir/ListItem.o" \
"CMakeFiles/app.dir/priorityTodoQueue.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

app: CMakeFiles/app.dir/main.o
app: CMakeFiles/app.dir/ListItem.o
app: CMakeFiles/app.dir/priorityTodoQueue.o
app: CMakeFiles/app.dir/build.make
app: CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/isaac/Documents/codeStuff/simpList/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app.dir/build: app

.PHONY : CMakeFiles/app.dir/build

CMakeFiles/app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app.dir/clean

CMakeFiles/app.dir/depend:
	cd /home/isaac/Documents/codeStuff/simpList && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/isaac/Documents/codeStuff/simpList /home/isaac/Documents/codeStuff/simpList /home/isaac/Documents/codeStuff/simpList /home/isaac/Documents/codeStuff/simpList /home/isaac/Documents/codeStuff/simpList/CMakeFiles/app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/app.dir/depend
