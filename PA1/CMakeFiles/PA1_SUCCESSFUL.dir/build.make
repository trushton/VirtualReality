# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usr/local/home/demo/Desktop/Thomas/VirtualReality

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/local/home/demo/Desktop/Thomas/VirtualReality

# Utility rule file for PA1_SUCCESSFUL.

# Include the progress variables for this target.
include PA1/CMakeFiles/PA1_SUCCESSFUL.dir/progress.make

PA1/CMakeFiles/PA1_SUCCESSFUL: PA1/PA1
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E echo 
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E echo =====================
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E echo \ \ Compile\ complete!
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E echo =====================
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E echo /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E copy_directory /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/shaders/ /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/shaders
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E copy_directory /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/media/ /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/media
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E copy_directory /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/config/ /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/config
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E copy /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/config/cavrconfig.lua /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && /usr/bin/cmake -E copy /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/config/cavrplugins.lua /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1

PA1_SUCCESSFUL: PA1/CMakeFiles/PA1_SUCCESSFUL
PA1_SUCCESSFUL: PA1/CMakeFiles/PA1_SUCCESSFUL.dir/build.make
.PHONY : PA1_SUCCESSFUL

# Rule to build all files generated by this target.
PA1/CMakeFiles/PA1_SUCCESSFUL.dir/build: PA1_SUCCESSFUL
.PHONY : PA1/CMakeFiles/PA1_SUCCESSFUL.dir/build

PA1/CMakeFiles/PA1_SUCCESSFUL.dir/clean:
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 && $(CMAKE_COMMAND) -P CMakeFiles/PA1_SUCCESSFUL.dir/cmake_clean.cmake
.PHONY : PA1/CMakeFiles/PA1_SUCCESSFUL.dir/clean

PA1/CMakeFiles/PA1_SUCCESSFUL.dir/depend:
	cd /usr/local/home/demo/Desktop/Thomas/VirtualReality && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/local/home/demo/Desktop/Thomas/VirtualReality /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 /usr/local/home/demo/Desktop/Thomas/VirtualReality /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1 /usr/local/home/demo/Desktop/Thomas/VirtualReality/PA1/CMakeFiles/PA1_SUCCESSFUL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : PA1/CMakeFiles/PA1_SUCCESSFUL.dir/depend

