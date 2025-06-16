# Compiler configuration
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I./include
LDFLAGS = -L./build

# Directory structure
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Targets
LIBRARY = $(BUILD_DIR)/libcryptonite.a
SHA256_TEST = $(BUILD_DIR)/test_sha256
HMAC_TEST = $(BUILD_DIR)/test_hmac

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Test files
TEST_SHA256_SRC = $(TEST_DIR)/test_sha256.c
TEST_HMAC_SRC = $(TEST_DIR)/test_hmac.c

# Default target
all: $(LIBRARY) $(SHA256_TEST) $(HMAC_TEST)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Library target
$(LIBRARY): $(OBJ_FILES) | $(BUILD_DIR)
	ar rcs $@ $^

# Test targets
$(SHA256_TEST): $(TEST_SHA256_SRC) $(LIBRARY) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lcryptonite

$(HMAC_TEST): $(TEST_HMAC_SRC) $(LIBRARY) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lcryptonite

# Compilation rule for source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Test commands
test: $(SHA256_TEST) $(HMAC_TEST)
	@echo "\nRunning SHA-256 tests:"
	@./$(SHA256_TEST)
	@echo "\nRunning HMAC tests:"
	@./$(HMAC_TEST)

# Cleanup
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean test