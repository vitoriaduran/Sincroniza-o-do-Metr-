CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -pthread
IMPL    = sync_car.c
HDRS    = sync_car.h

# Procura qualquer outro arquivo .c na pasta para usar como arquivo de teste (ex: test_sync_car.c)
TEST_SRC = $(filter-out $(IMPL), $(wildcard *.c))

all: sync_car.o

# Gera apenas o modulo objeto exigido
sync_car.o: $(IMPL) $(HDRS)
	$(CC) $(CFLAGS) -c $(IMPL) -o sync_car.o

# Se o professor rodar 'make run' ou 'make sync_car'
run: sync_car.o
@if [ -z "$(TEST_SRC)" ]; then \
	echo "Nenhum arquivo de teste (.c com main) foi encontrado na pasta."; \
	echo "Compilado apenas o objeto sync_car.o com sucesso."; \
else \
	$(CC) $(CFLAGS) -o test_runner sync_car.o $(TEST_SRC); \
	./test_runner; \
fi

clean:
	rm -f *.o test_runner sync_car test_sync_car teste_limite

.PHONY: all run clean