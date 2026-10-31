CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -pthread
TARGET  = sync_car
IMPL    = sync_car.c
TESTSRC = $(filter-out $(IMPL),$(wildcard *.c))
HDRS    = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(IMPL) $(TESTSRC) $(HDRS)
	$(CC) $(CFLAGS) -o $(TARGET) $(IMPL) $(TESTSRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all run clean