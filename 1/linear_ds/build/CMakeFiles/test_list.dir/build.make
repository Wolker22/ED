# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Escritorio/ED/1/linear_ds

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Escritorio/ED/1/linear_ds/build

# Include any dependencies generated for this target.
include CMakeFiles/test_list.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_list.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_list.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_list.dir/flags.make

CMakeFiles/test_list.dir/test_list.cpp.o: CMakeFiles/test_list.dir/flags.make
CMakeFiles/test_list.dir/test_list.cpp.o: /home/david/Escritorio/ED/1/linear_ds/test_list.cpp
CMakeFiles/test_list.dir/test_list.cpp.o: CMakeFiles/test_list.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/david/Escritorio/ED/1/linear_ds/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_list.dir/test_list.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_list.dir/test_list.cpp.o -MF CMakeFiles/test_list.dir/test_list.cpp.o.d -o CMakeFiles/test_list.dir/test_list.cpp.o -c /home/david/Escritorio/ED/1/linear_ds/test_list.cpp

CMakeFiles/test_list.dir/test_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_list.dir/test_list.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Escritorio/ED/1/linear_ds/test_list.cpp > CMakeFiles/test_list.dir/test_list.cpp.i

CMakeFiles/test_list.dir/test_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_list.dir/test_list.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Escritorio/ED/1/linear_ds/test_list.cpp -o CMakeFiles/test_list.dir/test_list.cpp.s

# Object files for target test_list
test_list_OBJECTS = \
"CMakeFiles/test_list.dir/test_list.cpp.o"

# External object files for target test_list
test_list_EXTERNAL_OBJECTS =

test_list: CMakeFiles/test_list.dir/test_list.cpp.o
test_list: CMakeFiles/test_list.dir/build.make
test_list: CMakeFiles/test_list.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/david/Escritorio/ED/1/linear_ds/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_list"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_list.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_list.dir/build: test_list
.PHONY : CMakeFiles/test_list.dir/build

CMakeFiles/test_list.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_list.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_list.dir/clean

CMakeFiles/test_list.dir/depend:
	cd /home/david/Escritorio/ED/1/linear_ds/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Escritorio/ED/1/linear_ds /home/david/Escritorio/ED/1/linear_ds /home/david/Escritorio/ED/1/linear_ds/build /home/david/Escritorio/ED/1/linear_ds/build /home/david/Escritorio/ED/1/linear_ds/build/CMakeFiles/test_list.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_list.dir/depend

