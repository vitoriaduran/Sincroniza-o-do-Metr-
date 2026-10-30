#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct station {
    pthread_mutex_t lock;
    pthread_cond_t chegada_carro;
    pthread_cond_t passageiro_sentado;
    int assentos_livre;
    int passageiros_esperando;
    int passageiros_embarcando;
};
