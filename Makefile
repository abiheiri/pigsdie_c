CC ?= cc
CFLAGS = -O2 -Wall -Wextra
TARGET = pigsdie
SRC = pigsdie.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
