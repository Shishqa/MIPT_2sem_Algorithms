# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/103/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/103/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/A_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/A_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A_.dir/flags.make

CMakeFiles/A_.dir/main.cpp.o: CMakeFiles/A_.dir/flags.make
CMakeFiles/A_.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A_.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/A_.dir/main.cpp.o -c /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/main.cpp

CMakeFiles/A_.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A_.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/main.cpp > CMakeFiles/A_.dir/main.cpp.i

CMakeFiles/A_.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A_.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/main.cpp -o CMakeFiles/A_.dir/main.cpp.s

# Object files for target A_
A__OBJECTS = \
"CMakeFiles/A_.dir/main.cpp.o"

# External object files for target A_
A__EXTERNAL_OBJECTS =

A_: CMakeFiles/A_.dir/main.cpp.o
A_: CMakeFiles/A_.dir/build.make
A_: CMakeFiles/A_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable A_"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/A_.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A_.dir/build: A_

.PHONY : CMakeFiles/A_.dir/build

CMakeFiles/A_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/A_.dir/cmake_clean.cmake
.PHONY : CMakeFiles/A_.dir/clean

CMakeFiles/A_.dir/depend:
	cd /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/cmake-build-debug /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/cmake-build-debug /home/shishqa/Repositories/MIPT/2_semester/Algorithms/03_SearchTrees/A_следующий/cmake-build-debug/CMakeFiles/A_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A_.dir/depend

