TARGET := chess
SRC_DIR := src
INC_DIR := include
CC := cc
CFLAGS := -std=c23 -O3 -Wall -Wextra -I$(INC_DIR)
SRCS := $(wildcard $(SRC_DIR)/*.c)

all: chess

chess: 
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: chess
	./$(TARGET)
	
clean:
	rm -f $(TARGET)

.PHONY: all clean run
