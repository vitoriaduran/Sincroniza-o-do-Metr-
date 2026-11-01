CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -pthread
TARGET  = sync_car
IMPL    = sync_car.c
HDRS    = sync_car.h

# Teste(s): qualquer outro .c da pasta (ex.: test_sync_car.c do professor, que tem a main)
TEST_SRC = $(filter-out $(IMPL), $(wildcard *.c))

ifeq ($(TEST_SRC),)
# Sem arquivo de teste: compila so o modulo (sync_car.o), sem erro
all: sync_car.o
	@echo "Aviso: nenhum .c de teste (com main) na pasta; compilado apenas sync_car.o."
	@echo "Para gerar o executavel sync_car, copie o test_sync_car.c do professor para esta pasta e rode make."
run: all
else
# Com arquivo de teste: gera o executavel sync_car
all: $(TARGET)
run: $(TARGET)
	./$(TARGET)
endif

sync_car.o: $(IMPL) $(HDRS)
	$(CC) $(CFLAGS) -c $(IMPL) -o sync_car.o

$(TARGET): sync_car.o $(TEST_SRC) $(HDRS)
	$(CC) $(CFLAGS) -o $(TARGET) sync_car.o $(TEST_SRC)

clean:
	rm -f $(TARGET) *.o

.PHONY: all run clean