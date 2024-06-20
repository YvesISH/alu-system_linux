# Makefile to compile and link the hnm program
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lelf

SOURCES = hnm.c
TARGET = hnm

all: $(TARGET)

# Compile the hnm target
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Clean up the compiled output
clean:
	rm -f $(TARGET)
