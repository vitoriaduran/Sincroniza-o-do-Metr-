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

//chama pela thread do carro quando ele chega com count assentos libre 
//so retorna quando: ninguem mais espera na plataforma ou nao tem mais assentos livres
// e todos os passageiros que ja reservaram assentos ja chamara ststation_on_board
void station_load_car(struct station *station, int count){

    pthread_mutex_lock(&station->lock);

    station->carro_presente =1;
    if (count >  0){
        station -> assentos_livre = count;
    }
    else{
        station -> assentos_livre =  0;
    }

    //acorda todos os passageiros(cada um olha para verificar se tem assentos para eles)
    pthread_cond_broadcast(&station -> chegada_carro );

    //espera enquanto ainda for possivel embarcar alguem ou ainda tiver passageiro a caminho do assento
    while ((station->esperando > 0 && station -> assentos_livre > 0) || station -> boarding > 0 ){
        pthread_cond_wait (&station -> passageiro_sentado, & station -> lock);
    }
    //carro vai embora: estaçao fica sem carro e sem assento
    station -> carro_presente = 0;
    station->assentos_livre = 0;

    pthread_mutex_unlock(&station->lock);


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

void station_on_board(struct station *station) {
    (void)station;
}

// MAIN DE TESTE DA STATION_LOAD_CAR
int main() {
    struct station s;
    station_init(&s);

    printf("--- TESTE 1: station_load_car sem passageiros ---\n");
    station_load_car(&s, 5);
    printf("Carro presente após saída: %d (esperado: 0)\n", s.carro_presente);
    printf("Assentos livres após saída: %d (esperado: 0)\n", s.assentos_livre);

    if (s.carro_presente == 0 && s.assentos_livre == 0) {
        printf("RESULTADO TESTE 1: SUCESSO! O carro retornou imediatamente.\n\n");
    } else {
        printf("RESULTADO TESTE 1: FALHA!\n\n");
    }

    return 0;
}