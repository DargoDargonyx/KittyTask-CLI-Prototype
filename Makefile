SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

CXX = g++
CXXFLAGS = -std=c++20 -I ./$(INC_DIR)

SRC = $(wildcard $(SRC_DIR)/*.cpp) \
	$(wildcard $(SRC_DIR)/groups/*.cpp) \
	$(wildcard $(SRC_DIR)/tasks/*.cpp) \
	$(wildcard $(SRC_DIR)/util/*.cpp) 

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
TARGET = kitty_task

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(BIN_DIR)/*.o $(BIN_DIR)/groups/*.o \
		$(BIN_DIR)/tasks/*.o $(BIN_DIR)/util/*.o

.PHONY: all clean
