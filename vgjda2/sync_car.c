#include <stdio.h>
#include <pthread.h>
#include "sync_car.h"
#include <unistd.h>

void station_init(struct station *station){
    pthread_mutex_init(&station->lock, NULL);
    pthread_cond_init(&station->chegada_carro, NULL);
    pthread_cond_init(&station->passageiro_sentado, NULL);

    station->esperando = 0;
    station->assentos_livre = 0;
    station ->boarding = 0;
    station-> carro_presente = 0;
}

//chamada por cada passageiro ao chegar na estação. 
//só vai retornar quando há carro na estaçao e um assento livre
void station_wait_for_car(struct station *station){


	pthread_mutex_lock(&station->lock);

    station->esperando++;
    while (!(station->carro_presente && station->assentos_livre > 0)){
        pthread_cond_wait(&station->chegada_carro, &station->lock);
    }

    station->assentos_livre --; //reserva o assento
    station->esperando--; //sai da plataforma
    station->boarding++; //esta a caminho do assento

    pthread_mutex_unlock(&station->lock);
}

void* passageiro_thread(void *arg) {
    struct station *s = (struct station*) arg;
    printf("[Passageiro] Chegou na estação e está esperando o trem...\n");
    
    station_wait_for_car(s);
    
    printf("[Passageiro] Conseguiu vaga e reservou o assento!\n");
    return NULL;
}

int main() {
    struct station s;
    station_init(&s);

    pthread_t t_passageiro;

    printf("--- TESTANDO STATION_WAIT_FOR_CAR ---\n");

    // 1. Criar a thread do passageiro
    pthread_create(&t_passageiro, NULL, passageiro_thread, &s);
    sleep(1); // Tempo para garantir que o passageiro entrou no station_wait_for_car

    // 2. Simular a chegada do trem (liberando 1 assento)
    pthread_mutex_lock(&s.lock);
    printf("[Sistema] Trem chegando com 1 assento livre...\n");
    s.carro_presente = 1;
    s.assentos_livre = 1;
    pthread_cond_signal(&s.chegada_carro); // Avisa o passageiro
    pthread_mutex_unlock(&s.lock);

    // 3. Aguardar a thread do passageiro finalizar
    pthread_join(t_passageiro, NULL);

    // 4. Verificação de estado
    printf("\n--- RESULTADO DOS ESTADOS ---\n");
    printf("Esperando: %d (esperado: 0)\n", s.esperando);
    printf("Assentos livres: %d (esperado: 0)\n", s.assentos_livre);
    printf("Boarding: %d (esperado: 1)\n", s.boarding);

    if (s.esperando == 0 && s.assentos_livre == 0 && s.boarding == 1) {
        printf("RESULTADO: station_wait_for_car FUNCIONOU COM SUCESSO!\n");
    } else {
        printf("RESULTADO: FALHA no teste de estado!\n");
    }

    return 0;
}