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
CMAKE_SOURCE_DIR = /home/armando/Documentos/S.O/WebServerSchemas/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/armando/Documentos/S.O/WebServerSchemas/Server/Bin

# Include any dependencies generated for this target.
include CMakeFiles/Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/main.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Server/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Server.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/main.c.o   -c /home/armando/Documentos/S.O/WebServerSchemas/Server/main.c

CMakeFiles/Server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/armando/Documentos/S.O/WebServerSchemas/Server/main.c > CMakeFiles/Server.dir/main.c.i

CMakeFiles/Server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/armando/Documentos/S.O/WebServerSchemas/Server/main.c -o CMakeFiles/Server.dir/main.c.s

CMakeFiles/Server.dir/main.c.o.requires:

.PHONY : CMakeFiles/Server.dir/main.c.o.requires

CMakeFiles/Server.dir/main.c.o.provides: CMakeFiles/Server.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/main.c.o.provides

CMakeFiles/Server.dir/main.c.o.provides.build: CMakeFiles/Server.dir/main.c.o


CMakeFiles/Server.dir/source/server.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/source/server.c.o: ../source/server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Server/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Server.dir/source/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/source/server.c.o   -c /home/armando/Documentos/S.O/WebServerSchemas/Server/source/server.c

CMakeFiles/Server.dir/source/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/source/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/armando/Documentos/S.O/WebServerSchemas/Server/source/server.c > CMakeFiles/Server.dir/source/server.c.i

CMakeFiles/Server.dir/source/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/source/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/armando/Documentos/S.O/WebServerSchemas/Server/source/server.c -o CMakeFiles/Server.dir/source/server.c.s

CMakeFiles/Server.dir/source/server.c.o.requires:

.PHONY : CMakeFiles/Server.dir/source/server.c.o.requires

CMakeFiles/Server.dir/source/server.c.o.provides: CMakeFiles/Server.dir/source/server.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/source/server.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/source/server.c.o.provides

CMakeFiles/Server.dir/source/server.c.o.provides.build: CMakeFiles/Server.dir/source/server.c.o


CMakeFiles/Server.dir/source/List.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/source/List.c.o: ../source/List.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Server/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Server.dir/source/List.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/source/List.c.o   -c /home/armando/Documentos/S.O/WebServerSchemas/Server/source/List.c

CMakeFiles/Server.dir/source/List.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/source/List.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/armando/Documentos/S.O/WebServerSchemas/Server/source/List.c > CMakeFiles/Server.dir/source/List.c.i

CMakeFiles/Server.dir/source/List.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/source/List.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/armando/Documentos/S.O/WebServerSchemas/Server/source/List.c -o CMakeFiles/Server.dir/source/List.c.s

CMakeFiles/Server.dir/source/List.c.o.requires:

.PHONY : CMakeFiles/Server.dir/source/List.c.o.requires

CMakeFiles/Server.dir/source/List.c.o.provides: CMakeFiles/Server.dir/source/List.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/source/List.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/source/List.c.o.provides

CMakeFiles/Server.dir/source/List.c.o.provides.build: CMakeFiles/Server.dir/source/List.c.o


CMakeFiles/Server.dir/source/client.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/source/client.c.o: ../source/client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Server/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Server.dir/source/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/source/client.c.o   -c /home/armando/Documentos/S.O/WebServerSchemas/Server/source/client.c

CMakeFiles/Server.dir/source/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/source/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/armando/Documentos/S.O/WebServerSchemas/Server/source/client.c > CMakeFiles/Server.dir/source/client.c.i

CMakeFiles/Server.dir/source/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/source/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/armando/Documentos/S.O/WebServerSchemas/Server/source/client.c -o CMakeFiles/Server.dir/source/client.c.s

CMakeFiles/Server.dir/source/client.c.o.requires:

.PHONY : CMakeFiles/Server.dir/source/client.c.o.requires

CMakeFiles/Server.dir/source/client.c.o.provides: CMakeFiles/Server.dir/source/client.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/source/client.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/source/client.c.o.provides

CMakeFiles/Server.dir/source/client.c.o.provides.build: CMakeFiles/Server.dir/source/client.c.o


# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/main.c.o" \
"CMakeFiles/Server.dir/source/server.c.o" \
"CMakeFiles/Server.dir/source/List.c.o" \
"CMakeFiles/Server.dir/source/client.c.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/main.c.o
Server: CMakeFiles/Server.dir/source/server.c.o
Server: CMakeFiles/Server.dir/source/List.c.o
Server: CMakeFiles/Server.dir/source/client.c.o
Server: CMakeFiles/Server.dir/build.make
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/armando/Documentos/S.O/WebServerSchemas/Server/Bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server

.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/main.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/source/server.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/source/List.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/source/client.c.o.requires

.PHONY : CMakeFiles/Server.dir/requires

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /home/armando/Documentos/S.O/WebServerSchemas/Server/Bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/armando/Documentos/S.O/WebServerSchemas/Server /home/armando/Documentos/S.O/WebServerSchemas/Server /home/armando/Documentos/S.O/WebServerSchemas/Server/Bin /home/armando/Documentos/S.O/WebServerSchemas/Server/Bin /home/armando/Documentos/S.O/WebServerSchemas/Server/Bin/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend

