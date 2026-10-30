CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -pthread
TARGET  = sync_car
SRC     = sync_car.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all run clean