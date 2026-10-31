#include <stdio.h>
#include <pthread.h>
#include "sync_car.h"

void station_init(struct station *station){
    pthread_mutex_init(&station->lock, NULL);
    pthread_cond_init(&station->chegada_carro, NULL);
    pthread_cond_init(&station->passageiro_sentado, NULL);

    station->esperando = 0;
    station->assentos_livre = 0;
    station ->boarding = 0;
    station-> carro_presente = 0;
}

int main() {

    //parte para testar apenas a funcao station init
    struct station s;
    station_init(&s);

    printf("--- TESTANDO STATION_INIT ---\n");
    printf("Esperando: %d (esperado: 0)\n", s.esperando);
    printf("Assentos livres: %d (esperado: 0)\n", s.assentos_livre);
    printf("Boarding: %d (esperado: 0)\n", s.boarding);
    printf("Carro presente: %d (esperado: 0)\n", s.carro_presente);

    if (s.esperando == 0 && s.assentos_livre == 0 && s.boarding == 0 && s.carro_presente == 0) {
        printf("RESULTADO: station_init FUNCIONOU!\n");
    } else {
        printf("RESULTADO: FALHA na inicialização!\n");
    }

    return 0;
}

