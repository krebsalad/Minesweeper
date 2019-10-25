# arguments
PKG_DIR = ./
INC_DIR = $(PKG_DIR)./include
SRC_DIR = $(PKG_DIR)./src
OBJ_DIR = $(PKG_DIR)./build

# build flags
CC = g++
CXXFLAGS = -g -std=c++11
LIBRARIES = $()

# objects and sources
INCLUDES = $(wildcard $(INC_DIR)/*.h)
DEPENDENCIES = $(addprefix $(INC_DIR)/,$(notdir $(INCLUDES:.cpp=.h))) 
SOURCES = $(wildcard $(SRC_DIR)/*.cpp main.cpp) 
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o))) 

EXEC_NAME = test1

# Create executable
$(EXEC_NAME): $(OBJECTS) 
	$(CC) -o $(EXEC_NAME) $(OBJECTS)

# build
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

# build main
$(OBJ_DIR)/main.o: main.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

# clean files created by make
clean:
	rm $(OBJECTS)
	rm $(EXEC_NAME)