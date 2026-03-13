SRC_DIR		:= ./tools
BUILD_DIR	:= ./build
BIN_DIR		:= ./bin

CC			:= gcc
CFLAGS		:= -Wall -Wextra

TARGET_EXEC	:= $(BIN_DIR)/bundler
OBJECTS		:= $(BUILD_DIR)/bundler.o

.PHONY: clean all

all: $(TARGET_EXEC) codingame.c

$(TARGET_EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

codingame.c: $(TARGET_EXEC) $(FILE)
	$(TARGET_EXEC) $(FILE) > $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) codingame.c
