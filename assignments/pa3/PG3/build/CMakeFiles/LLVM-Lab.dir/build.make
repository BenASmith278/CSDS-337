# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/ben/Documents/csds337/assignments/pa3/PG3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ben/Documents/csds337/build

# Include any dependencies generated for this target.
include CMakeFiles/LLVM-Lab.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LLVM-Lab.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LLVM-Lab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LLVM-Lab.dir/flags.make

CMakeFiles/LLVM-Lab.dir/src/main.cpp.o: CMakeFiles/LLVM-Lab.dir/flags.make
CMakeFiles/LLVM-Lab.dir/src/main.cpp.o: /home/ben/Documents/csds337/assignments/pa3/PG3/src/main.cpp
CMakeFiles/LLVM-Lab.dir/src/main.cpp.o: CMakeFiles/LLVM-Lab.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ben/Documents/csds337/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LLVM-Lab.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LLVM-Lab.dir/src/main.cpp.o -MF CMakeFiles/LLVM-Lab.dir/src/main.cpp.o.d -o CMakeFiles/LLVM-Lab.dir/src/main.cpp.o -c /home/ben/Documents/csds337/assignments/pa3/PG3/src/main.cpp

CMakeFiles/LLVM-Lab.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/LLVM-Lab.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ben/Documents/csds337/assignments/pa3/PG3/src/main.cpp > CMakeFiles/LLVM-Lab.dir/src/main.cpp.i

CMakeFiles/LLVM-Lab.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/LLVM-Lab.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ben/Documents/csds337/assignments/pa3/PG3/src/main.cpp -o CMakeFiles/LLVM-Lab.dir/src/main.cpp.s

# Object files for target LLVM-Lab
LLVM__Lab_OBJECTS = \
"CMakeFiles/LLVM-Lab.dir/src/main.cpp.o"

# External object files for target LLVM-Lab
LLVM__Lab_EXTERNAL_OBJECTS =

/home/ben/Documents/csds337/assignments/pa3/PG3/bin/LLVM-Lab: CMakeFiles/LLVM-Lab.dir/src/main.cpp.o
/home/ben/Documents/csds337/assignments/pa3/PG3/bin/LLVM-Lab: CMakeFiles/LLVM-Lab.dir/build.make
/home/ben/Documents/csds337/assignments/pa3/PG3/bin/LLVM-Lab: CMakeFiles/LLVM-Lab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ben/Documents/csds337/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/ben/Documents/csds337/assignments/pa3/PG3/bin/LLVM-Lab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LLVM-Lab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LLVM-Lab.dir/build: /home/ben/Documents/csds337/assignments/pa3/PG3/bin/LLVM-Lab
.PHONY : CMakeFiles/LLVM-Lab.dir/build

CMakeFiles/LLVM-Lab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LLVM-Lab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LLVM-Lab.dir/clean

CMakeFiles/LLVM-Lab.dir/depend:
	cd /home/ben/Documents/csds337/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ben/Documents/csds337/assignments/pa3/PG3 /home/ben/Documents/csds337/assignments/pa3/PG3 /home/ben/Documents/csds337/build /home/ben/Documents/csds337/build /home/ben/Documents/csds337/build/CMakeFiles/LLVM-Lab.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/LLVM-Lab.dir/depend

