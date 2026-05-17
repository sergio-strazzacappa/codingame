SRC_DIR		:= ./tools
BUILD_DIR	:= ./build
BIN_DIR		:= ./bin

CC			:= gcc
CFLAGS		:= -Wall -Wextra

FINAL_EXEC	:= $(BIN_DIR)/codingame
TARGET_EXEC	:= $(BIN_DIR)/bundler
OBJECTS		:= $(BUILD_DIR)/bundler.o

.PHONY: clean all

all: codingame.c

#all: $(FINAL_EXEC)

# Compile codingame.o into codingame, the final bin to run the bot
$(FINAL_EXEC): $(BUILD_DIR)/codingame.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Generate the objet .o of codingame
$(BUILD_DIR)/codingame.o: codingame.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the bundler to generate codingame.c
codingame.c: $(TARGET_EXEC)
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make FILE=main.c"; \
		exit 1; \
	fi
	$(TARGET_EXEC) $(FILE) > $@

# Compile the bundler, link the .o objects
$(TARGET_EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Generate the object .o of the bundler
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the directories to store the files
$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) codingame.c #$(BIN_DIR) codingame.c
