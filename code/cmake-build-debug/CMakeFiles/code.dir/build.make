# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/weijie/CLionProjects/untitled2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/weijie/CLionProjects/untitled2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/code.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/code.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/code.dir/flags.make

CMakeFiles/code.dir/main.cpp.o: CMakeFiles/code.dir/flags.make
CMakeFiles/code.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weijie/CLionProjects/untitled2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/code.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code.dir/main.cpp.o -c /Users/weijie/CLionProjects/untitled2/main.cpp

CMakeFiles/code.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weijie/CLionProjects/untitled2/main.cpp > CMakeFiles/code.dir/main.cpp.i

CMakeFiles/code.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weijie/CLionProjects/untitled2/main.cpp -o CMakeFiles/code.dir/main.cpp.s

CMakeFiles/code.dir/book.cpp.o: CMakeFiles/code.dir/flags.make
CMakeFiles/code.dir/book.cpp.o: ../book.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weijie/CLionProjects/untitled2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/code.dir/book.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code.dir/book.cpp.o -c /Users/weijie/CLionProjects/untitled2/book.cpp

CMakeFiles/code.dir/book.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code.dir/book.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weijie/CLionProjects/untitled2/book.cpp > CMakeFiles/code.dir/book.cpp.i

CMakeFiles/code.dir/book.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code.dir/book.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weijie/CLionProjects/untitled2/book.cpp -o CMakeFiles/code.dir/book.cpp.s

CMakeFiles/code.dir/log.cpp.o: CMakeFiles/code.dir/flags.make
CMakeFiles/code.dir/log.cpp.o: ../log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weijie/CLionProjects/untitled2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/code.dir/log.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code.dir/log.cpp.o -c /Users/weijie/CLionProjects/untitled2/log.cpp

CMakeFiles/code.dir/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code.dir/log.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weijie/CLionProjects/untitled2/log.cpp > CMakeFiles/code.dir/log.cpp.i

CMakeFiles/code.dir/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code.dir/log.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weijie/CLionProjects/untitled2/log.cpp -o CMakeFiles/code.dir/log.cpp.s

CMakeFiles/code.dir/token_scanner.cpp.o: CMakeFiles/code.dir/flags.make
CMakeFiles/code.dir/token_scanner.cpp.o: ../token_scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weijie/CLionProjects/untitled2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/code.dir/token_scanner.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code.dir/token_scanner.cpp.o -c /Users/weijie/CLionProjects/untitled2/token_scanner.cpp

CMakeFiles/code.dir/token_scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code.dir/token_scanner.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weijie/CLionProjects/untitled2/token_scanner.cpp > CMakeFiles/code.dir/token_scanner.cpp.i

CMakeFiles/code.dir/token_scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code.dir/token_scanner.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weijie/CLionProjects/untitled2/token_scanner.cpp -o CMakeFiles/code.dir/token_scanner.cpp.s

CMakeFiles/code.dir/accounts.cpp.o: CMakeFiles/code.dir/flags.make
CMakeFiles/code.dir/accounts.cpp.o: ../accounts.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weijie/CLionProjects/untitled2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/code.dir/accounts.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code.dir/accounts.cpp.o -c /Users/weijie/CLionProjects/untitled2/accounts.cpp

CMakeFiles/code.dir/accounts.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code.dir/accounts.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weijie/CLionProjects/untitled2/accounts.cpp > CMakeFiles/code.dir/accounts.cpp.i

CMakeFiles/code.dir/accounts.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code.dir/accounts.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weijie/CLionProjects/untitled2/accounts.cpp -o CMakeFiles/code.dir/accounts.cpp.s

# Object files for target code
code_OBJECTS = \
"CMakeFiles/code.dir/main.cpp.o" \
"CMakeFiles/code.dir/book.cpp.o" \
"CMakeFiles/code.dir/log.cpp.o" \
"CMakeFiles/code.dir/token_scanner.cpp.o" \
"CMakeFiles/code.dir/accounts.cpp.o"

# External object files for target code
code_EXTERNAL_OBJECTS =

code: CMakeFiles/code.dir/main.cpp.o
code: CMakeFiles/code.dir/book.cpp.o
code: CMakeFiles/code.dir/log.cpp.o
code: CMakeFiles/code.dir/token_scanner.cpp.o
code: CMakeFiles/code.dir/accounts.cpp.o
code: CMakeFiles/code.dir/build.make
code: CMakeFiles/code.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/weijie/CLionProjects/untitled2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable code"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/code.dir/build: code
.PHONY : CMakeFiles/code.dir/build

CMakeFiles/code.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/code.dir/cmake_clean.cmake
.PHONY : CMakeFiles/code.dir/clean

CMakeFiles/code.dir/depend:
	cd /Users/weijie/CLionProjects/untitled2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/weijie/CLionProjects/untitled2 /Users/weijie/CLionProjects/untitled2 /Users/weijie/CLionProjects/untitled2/cmake-build-debug /Users/weijie/CLionProjects/untitled2/cmake-build-debug /Users/weijie/CLionProjects/untitled2/cmake-build-debug/CMakeFiles/code.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/code.dir/depend

