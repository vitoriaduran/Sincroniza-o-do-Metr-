#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    pthread_mutex_t lock;
    pthread_cond_t chegada_carro;
    pthread_cond_t passageiro_sentado;
    int esperando; 
    int assentos_livre;
    int boarding;
    int carro_presente; //1 se station_load_car está em execuçao, 0 se nao estiver
};

void station_init(struct station *station);
void station_load_car(struct station *station, int count);
void station_wait_for_car(struct station *station);
void station_on_board(struct station *station);

#endif