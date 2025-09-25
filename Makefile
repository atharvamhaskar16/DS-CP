# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Project name
TARGET = ev_system.exe

# Source files
SRCS = main.c ev.c queue.c pq.c hash.c set.c bst.c stack.c slots.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	del /Q *.o *.exe 2>nul || true
