# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /tmp/tmp.qi0qsv5C10

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.qi0qsv5C10/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SemestralkaTicTacToe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SemestralkaTicTacToe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SemestralkaTicTacToe.dir/flags.make

CMakeFiles/SemestralkaTicTacToe.dir/main.c.o: CMakeFiles/SemestralkaTicTacToe.dir/flags.make
CMakeFiles/SemestralkaTicTacToe.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.qi0qsv5C10/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SemestralkaTicTacToe.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SemestralkaTicTacToe.dir/main.c.o -c /tmp/tmp.qi0qsv5C10/main.c

CMakeFiles/SemestralkaTicTacToe.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SemestralkaTicTacToe.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.qi0qsv5C10/main.c > CMakeFiles/SemestralkaTicTacToe.dir/main.c.i

CMakeFiles/SemestralkaTicTacToe.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SemestralkaTicTacToe.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.qi0qsv5C10/main.c -o CMakeFiles/SemestralkaTicTacToe.dir/main.c.s

# Object files for target SemestralkaTicTacToe
SemestralkaTicTacToe_OBJECTS = \
"CMakeFiles/SemestralkaTicTacToe.dir/main.c.o"

# External object files for target SemestralkaTicTacToe
SemestralkaTicTacToe_EXTERNAL_OBJECTS =

SemestralkaTicTacToe: CMakeFiles/SemestralkaTicTacToe.dir/main.c.o
SemestralkaTicTacToe: CMakeFiles/SemestralkaTicTacToe.dir/build.make
SemestralkaTicTacToe: CMakeFiles/SemestralkaTicTacToe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.qi0qsv5C10/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SemestralkaTicTacToe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SemestralkaTicTacToe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SemestralkaTicTacToe.dir/build: SemestralkaTicTacToe

.PHONY : CMakeFiles/SemestralkaTicTacToe.dir/build

CMakeFiles/SemestralkaTicTacToe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SemestralkaTicTacToe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SemestralkaTicTacToe.dir/clean

CMakeFiles/SemestralkaTicTacToe.dir/depend:
	cd /tmp/tmp.qi0qsv5C10/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.qi0qsv5C10 /tmp/tmp.qi0qsv5C10 /tmp/tmp.qi0qsv5C10/cmake-build-debug /tmp/tmp.qi0qsv5C10/cmake-build-debug /tmp/tmp.qi0qsv5C10/cmake-build-debug/CMakeFiles/SemestralkaTicTacToe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SemestralkaTicTacToe.dir/depend

