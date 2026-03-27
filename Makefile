SRC_DIR := src
INC_DIR := include
BIN_DIR := build

CC := gcc
CFLAGS := -Wall -Wextra -g -I ./$(INC_DIR)
SQL_FLAGS := -O2 -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION

SRC := $(wildcard $(SRC_DIR)/*.c) \
	$(wildcard $(SRC_DIR)/core/*.c) \
	$(wildcard $(SRC_DIR)/external/*.c) \
	$(wildcard $(SRC_DIR)/util/*.c) 

OBJ := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC))

TARGET := ktask


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SQL_FLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(BIN_DIR)

.PHONY: all clean
