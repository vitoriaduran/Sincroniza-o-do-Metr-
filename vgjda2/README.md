# Implementação 4 — Sincronização do Metrô (METROREC)
 
Disciplina: Infraestrutura de Software — CESAR School  
Aluna: Vitória Gabrielle Janeiro Duran (login: `vgjda2`)
 
## Sistema operacional
 
Implementado e testado em **Linux (Ubuntu via WSL no Windows)**, compilador **gcc 15.2.0**, com pthreads (POSIX).
Deve funcionar em qualquer Linux/Unix/macOS com `gcc` e `make`.
 
## Arquivos
 
| Arquivo | Descrição |
|---|---|
| `sync_car.h` | Define a `struct station` (1 mutex, 2 variáveis de condição e os contadores `esperando`, `assentos_livre`, `boarding`, `carro_presente`) e os protótipos das 4 funções. |
| `sync_car.c` | Implementação de `station_init`, `station_load_car`, `station_wait_for_car` e `station_on_board`. Não possui `main`. |
| `test_sync_car.c` | Teste automatizado fornecido pelo professor (contém o `main`). Não foi alterado. |
| `Makefile` | Compila `sync_car.c` + `test_sync_car.c` e gera o executável `sync_car`; possui as regras `all`, `run` e `clean`. |
| `evidencias.log` | Log do terminal (comando `script`) com compilações, erros e testes ao longo do desenvolvimento. |
| `vgjda2.pdf` | Relatório. |
 
## Como compilar, executar e testar
 
```bash
cd vgjda2
make clean      # remove executáveis e objetos
make            # gera o executável ./sync_car
./sync_car      # roda o teste do professor; deve terminar com "Looks good!"
```
 
`make run` compila (se necessário) e executa em um só passo.
 
O único aviso do compilador (`unused parameter 'foo'` em `alarm_handler`) vem do `test_sync_car.c` do professor, não da implementação.
 
## Resumo da solução
 
Um único `pthread_mutex_t` protege todo o estado da estação. Duas variáveis de condição separam quem espera:
`chegada_carro` (passageiros esperando carro com assento livre) e `passageiro_sentado` (carro esperando o embarque terminar).
Todas as esperas usam `while` + `pthread_cond_wait`, portanto não há busy-wait. Usa apenas
`pthread_mutex_init/lock/unlock` e `pthread_cond_init/signal/wait/broadcast`; sem semáforos.
 