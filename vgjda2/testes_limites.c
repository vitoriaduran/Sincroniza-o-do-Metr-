/* Casos limite e invalido (nao faz parte do teste do professor) */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "sync_car.h"
 
static struct station st;
static volatile int liberou = 0;
 
static void *passageiro(void *a) {
    (void)a;
    station_wait_for_car(&st);
    liberou = 1;
    station_on_board(&st);
    return NULL;
}
 
static void *carro1(void *a) {
    (void)a;
    station_load_car(&st, 1);       /* limite: 1 unico assento */
    return NULL;
}
 
int main(void) {
    station_init(&st);
 
    /* limite: sem passageiros, count = 0 e count > 0 retornam na hora */
    alarm(2);
    station_load_car(&st, 0);
    station_load_car(&st, 10);
    printf("[limite] sem passageiros: retornou imediatamente\n");
 
    /* invalido: count negativo com um passageiro esperando */
    pthread_t p;
    pthread_create(&p, NULL, passageiro, NULL);
    sleep(1);                       /* garante que o passageiro ja esta esperando */
    station_load_car(&st, -5);
    printf("[invalido] count = -5: retornou imediatamente\n");
    printf("[invalido] passageiro liberado? %s (esperado: nao)\n", liberou ? "SIM (erro)" : "nao");
 
    /* limite: carro com 1 assento libera o passageiro que continuava esperando */
    pthread_t c;
    pthread_create(&c, NULL, carro1, NULL);
    pthread_join(c, NULL);
    pthread_join(p, NULL);
    printf("[limite] carro com 1 assento: passageiro liberado? %s (esperado: SIM)\n", liberou ? "SIM" : "nao (erro)");
    alarm(0);
    return 0;
}