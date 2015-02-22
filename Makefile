CC := clang++-3.5
CFLAGS := -Wall -Wextra -std=c++11
OPT := # Empty

SRC_DIR := src/
INCLUDES := -I include/

SRCS := $(wildcard $(SRC_DIR)*.cpp)

BIN := rms

.PHONY: clean

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(OPT) $(SRCS) -o $(BIN)

clean:
	rm $(BIN)
