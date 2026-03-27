SRC_DIR = src
INC_DIR = include
BIN_DIR = build

CC = gcc
CFLAGS = -Wall -Wextra -g -I ./$(INC_DIR)

SRC = $(wildcard $(SRC_DIR)/*.c) \
	$(wildcard $(SRC_DIR)/core/*.c) \
	$(wildcard $(SRC_DIR)/external/*.c) \
	$(wildcard $(SRC_DIR)/util/*.c) 

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
TARGET = ktask

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(BIN_DIR)/*.o \
		$(BIN_DIR)/core/*.o \
		$(BIN_DIR)/external/*.o \
		$(BIN_DIR)/util/*.o

.PHONY: all clean
