
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lelf

SOURCES = hnm.c
TARGET = hnm

all: $(TARGET)

$(TARGET): $(SOURCES)
    $(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
    rm -f $(TARGET)
