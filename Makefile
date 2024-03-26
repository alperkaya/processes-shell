# Makefile for wish.c, utils.c, my_test.c, and Unity

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
TEST_DIR = unit_test
UNITY_DIR = unit_test/Unity/src

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c) $(UNITY_DIR)/unity.c

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRCS))

# Executable name
EXEC = wish
TEST_EXEC = my_test

# Targets
all: $(EXEC) $(TEST_EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_EXEC): $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC_DIR) -I$(UNITY_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR) -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR) -I$(UNITY_DIR) -o $@

clean:
	rm -f $(EXEC) $(TEST_EXEC) $(OBJS) $(TEST_OBJS)
