# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.11

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\Applications\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\Applications\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows

# Include any dependencies generated for this target.
include CMakeFiles/clear.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/clear.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clear.dir/flags.make

CMakeFiles/clear.dir/bitboard.cpp.obj: CMakeFiles/clear.dir/flags.make
CMakeFiles/clear.dir/bitboard.cpp.obj: ../bitboard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/clear.dir/bitboard.cpp.obj"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\clear.dir\bitboard.cpp.obj -c D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\bitboard.cpp

CMakeFiles/clear.dir/bitboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clear.dir/bitboard.cpp.i"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\bitboard.cpp > CMakeFiles\clear.dir\bitboard.cpp.i

CMakeFiles/clear.dir/bitboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clear.dir/bitboard.cpp.s"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\bitboard.cpp -o CMakeFiles\clear.dir\bitboard.cpp.s

CMakeFiles/clear.dir/board.cpp.obj: CMakeFiles/clear.dir/flags.make
CMakeFiles/clear.dir/board.cpp.obj: ../board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/clear.dir/board.cpp.obj"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\clear.dir\board.cpp.obj -c D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\board.cpp

CMakeFiles/clear.dir/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clear.dir/board.cpp.i"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\board.cpp > CMakeFiles\clear.dir\board.cpp.i

CMakeFiles/clear.dir/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clear.dir/board.cpp.s"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\board.cpp -o CMakeFiles\clear.dir\board.cpp.s

CMakeFiles/clear.dir/main.cpp.obj: CMakeFiles/clear.dir/flags.make
CMakeFiles/clear.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/clear.dir/main.cpp.obj"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\clear.dir\main.cpp.obj -c D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\main.cpp

CMakeFiles/clear.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clear.dir/main.cpp.i"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\main.cpp > CMakeFiles\clear.dir\main.cpp.i

CMakeFiles/clear.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clear.dir/main.cpp.s"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\main.cpp -o CMakeFiles\clear.dir\main.cpp.s

CMakeFiles/clear.dir/utils.cpp.obj: CMakeFiles/clear.dir/flags.make
CMakeFiles/clear.dir/utils.cpp.obj: ../utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/clear.dir/utils.cpp.obj"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\clear.dir\utils.cpp.obj -c D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\utils.cpp

CMakeFiles/clear.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clear.dir/utils.cpp.i"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\utils.cpp > CMakeFiles\clear.dir\utils.cpp.i

CMakeFiles/clear.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clear.dir/utils.cpp.s"
	D:\Applications\MinGW-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\utils.cpp -o CMakeFiles\clear.dir\utils.cpp.s

# Object files for target clear
clear_OBJECTS = \
"CMakeFiles/clear.dir/bitboard.cpp.obj" \
"CMakeFiles/clear.dir/board.cpp.obj" \
"CMakeFiles/clear.dir/main.cpp.obj" \
"CMakeFiles/clear.dir/utils.cpp.obj"

# External object files for target clear
clear_EXTERNAL_OBJECTS =

clear.exe: CMakeFiles/clear.dir/bitboard.cpp.obj
clear.exe: CMakeFiles/clear.dir/board.cpp.obj
clear.exe: CMakeFiles/clear.dir/main.cpp.obj
clear.exe: CMakeFiles/clear.dir/utils.cpp.obj
clear.exe: CMakeFiles/clear.dir/build.make
clear.exe: CMakeFiles/clear.dir/linklibs.rsp
clear.exe: CMakeFiles/clear.dir/objects1.rsp
clear.exe: CMakeFiles/clear.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable clear.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\clear.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clear.dir/build: clear.exe

.PHONY : CMakeFiles/clear.dir/build

CMakeFiles/clear.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\clear.dir\cmake_clean.cmake
.PHONY : CMakeFiles/clear.dir/clean

CMakeFiles/clear.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows D:\Code\SourceTree\ChessEngine\Clear\kdevelop\Clear\build-windows\CMakeFiles\clear.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/clear.dir/depend
