# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/armando/Documentos/S.O/WebServerSchemas/Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/armando/Documentos/S.O/WebServerSchemas/Client/Bin

# Include any dependencies generated for this target.
include CMakeFiles/Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client.dir/flags.make

CMakeFiles/Client.dir/main.c.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Client/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Client.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Client.dir/main.c.o   -c /home/armando/Documentos/S.O/WebServerSchemas/Client/main.c

CMakeFiles/Client.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Client.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/armando/Documentos/S.O/WebServerSchemas/Client/main.c > CMakeFiles/Client.dir/main.c.i

CMakeFiles/Client.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Client.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/armando/Documentos/S.O/WebServerSchemas/Client/main.c -o CMakeFiles/Client.dir/main.c.s

CMakeFiles/Client.dir/main.c.o.requires:

.PHONY : CMakeFiles/Client.dir/main.c.o.requires

CMakeFiles/Client.dir/main.c.o.provides: CMakeFiles/Client.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Client.dir/build.make CMakeFiles/Client.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Client.dir/main.c.o.provides

CMakeFiles/Client.dir/main.c.o.provides.build: CMakeFiles/Client.dir/main.c.o


CMakeFiles/Client.dir/source/client.c.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/source/client.c.o: ../source/client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Client/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Client.dir/source/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Client.dir/source/client.c.o   -c /home/armando/Documentos/S.O/WebServerSchemas/Client/source/client.c

CMakeFiles/Client.dir/source/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Client.dir/source/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/armando/Documentos/S.O/WebServerSchemas/Client/source/client.c > CMakeFiles/Client.dir/source/client.c.i

CMakeFiles/Client.dir/source/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Client.dir/source/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/armando/Documentos/S.O/WebServerSchemas/Client/source/client.c -o CMakeFiles/Client.dir/source/client.c.s

CMakeFiles/Client.dir/source/client.c.o.requires:

.PHONY : CMakeFiles/Client.dir/source/client.c.o.requires

CMakeFiles/Client.dir/source/client.c.o.provides: CMakeFiles/Client.dir/source/client.c.o.requires
	$(MAKE) -f CMakeFiles/Client.dir/build.make CMakeFiles/Client.dir/source/client.c.o.provides.build
.PHONY : CMakeFiles/Client.dir/source/client.c.o.provides

CMakeFiles/Client.dir/source/client.c.o.provides.build: CMakeFiles/Client.dir/source/client.c.o


CMakeFiles/Client.dir/source/List.c.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/source/List.c.o: ../source/List.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Client/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Client.dir/source/List.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Client.dir/source/List.c.o   -c /home/armando/Documentos/S.O/WebServerSchemas/Client/source/List.c

CMakeFiles/Client.dir/source/List.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Client.dir/source/List.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/armando/Documentos/S.O/WebServerSchemas/Client/source/List.c > CMakeFiles/Client.dir/source/List.c.i

CMakeFiles/Client.dir/source/List.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Client.dir/source/List.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/armando/Documentos/S.O/WebServerSchemas/Client/source/List.c -o CMakeFiles/Client.dir/source/List.c.s

CMakeFiles/Client.dir/source/List.c.o.requires:

.PHONY : CMakeFiles/Client.dir/source/List.c.o.requires

CMakeFiles/Client.dir/source/List.c.o.provides: CMakeFiles/Client.dir/source/List.c.o.requires
	$(MAKE) -f CMakeFiles/Client.dir/build.make CMakeFiles/Client.dir/source/List.c.o.provides.build
.PHONY : CMakeFiles/Client.dir/source/List.c.o.provides

CMakeFiles/Client.dir/source/List.c.o.provides.build: CMakeFiles/Client.dir/source/List.c.o


# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/main.c.o" \
"CMakeFiles/Client.dir/source/client.c.o" \
"CMakeFiles/Client.dir/source/List.c.o"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client: CMakeFiles/Client.dir/main.c.o
Client: CMakeFiles/Client.dir/source/client.c.o
Client: CMakeFiles/Client.dir/source/List.c.o
Client: CMakeFiles/Client.dir/build.make
Client: CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Client/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client.dir/build: Client

.PHONY : CMakeFiles/Client.dir/build

CMakeFiles/Client.dir/requires: CMakeFiles/Client.dir/main.c.o.requires
CMakeFiles/Client.dir/requires: CMakeFiles/Client.dir/source/client.c.o.requires
CMakeFiles/Client.dir/requires: CMakeFiles/Client.dir/source/List.c.o.requires

.PHONY : CMakeFiles/Client.dir/requires

CMakeFiles/Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client.dir/clean

CMakeFiles/Client.dir/depend:
	cd /home/armando/Documentos/S.O/WebServerSchemas/Client/Bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/armando/Documentos/S.O/WebServerSchemas/Client /home/armando/Documentos/S.O/WebServerSchemas/Client /home/armando/Documentos/S.O/WebServerSchemas/Client/Bin /home/armando/Documentos/S.O/WebServerSchemas/Client/Bin /home/armando/Documentos/S.O/WebServerSchemas/Client/Bin/CMakeFiles/Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Client.dir/depend

