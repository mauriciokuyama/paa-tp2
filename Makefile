CC := gcc
BIN_NAME := main
BUILD_DIR := build
SRC_DIR := src
ifeq ($(OS), Windows_NT)
	OBJ_DIR := $(BUILD_DIR)\.build
	BIN_PATH := $(BUILD_DIR)\$(BIN_NAME)
else
	OBJ_DIR := $(BUILD_DIR)/.build
	BIN_PATH := $(BUILD_DIR)/$(BIN_NAME)
endif
WFLAGS := -Wall \
		  -Wextra \
		  -pedantic
CFLAGS := $(WFLAGS) \
		  -std=c99 \
		  -g3
LDFLAGS :=
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

.PHONY: all
all: $(BIN_PATH)

$(BIN_PATH): $(BUILD_DIR) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: run
run: $(BIN_PATH)
	@./$<

.PHONY: inputgen
inputgen:
ifeq ($(OS), Windows_NT)
	mingw32-gcc generator/main.c generator/mapa.c -o main
	./main
else
	gcc generator/main.c generator/mapa.c -o main
	./main
endif
	
$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
ifeq ($(OS),Windows_NT)
	mkdir $@
else
	mkdir -p $@
endif

$(OBJ_DIR):
ifeq ($(OS),Windows_NT)
	mkdir $@
else
	mkdir -p $@
endif

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	rmdir /s /q $(BUILD_DIR)
else
	rm -rf $(BUILD_DIR)
endif