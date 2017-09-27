#OBJS spcecifies which files to compile as part of the project
OBJS = *.cpp
#CC specifies which compiler used
CC = g++

#COMPILER_FLAGS
# -w suppresses all warnings
# -std=c++11 chose the standard c++11
COMPILER_FLAGS = -w -std=c++11

#LINKER_FLAGS
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our executable
OBJ_NAME = main
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
