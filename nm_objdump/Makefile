# Makefile to compile and link the hnm_bfd program
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lbfd -liberty

SOURCES = hnm_bfd.c
TARGET = hnm

all: $(TARGET)

# Compile the hnm target
$(TARGET): $(SOURCES)
    $(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

# Clean up the compiled output
clean:
    rm -f $(TARGET)
