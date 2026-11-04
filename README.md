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
| `Makefile` | Compila o módulo e, quando há um arquivo de teste com `main` na pasta, gera o executável `sync_car`. Regras: `all`, `run` e `clean`. |
| `evidencias.log` | Log do terminal (comando `script`) com compilações, erros e testes ao longo do desenvolvimento. |
| `README.md` | Este arquivo. |
 
O arquivo de teste `test_sync_car.c` (que contém a `main`) é fornecido pelo professor e **não** está incluído neste pacote.
 
## Como compilar, executar e testar
 
Descompacte o pacote e entre na pasta:
 
```bash
tar -xf vgjda2.tar
cd vgjda2
```
 
**1. Compilar apenas o módulo** (sem arquivo de teste na pasta):
 
```bash
make            # compila sync_car.c e gera sync_car.o
```
 
**2. Compilar o executável e rodar o teste automatizado:**
 
```bash
cp /caminho/do/test_sync_car.c .   # copie o teste do professor para esta pasta
make clean
make            # gera o executável ./sync_car (sync_car.c + test_sync_car.c)
./sync_car      # deve terminar com "Looks good!"
```
 
`make run` compila (se necessário) e executa em um só passo.
 
**3. Limpar os arquivos compilados:**
 
```bash
make clean      # remove sync_car e os arquivos .o
```
 
O Makefile compila `sync_car.c` junto com qualquer outro `.c` presente na pasta (o arquivo de teste, qualquer que seja o nome).
O único aviso do compilador (`unused parameter 'foo'` em `alarm_handler`) vem do `test_sync_car.c` do professor, não da implementação.
 
## Resumo da solução
 
Um único `pthread_mutex_t` protege todo o estado da estação. Duas variáveis de condição separam quem espera:
`chegada_carro` (passageiros esperando carro com assento livre) e `passageiro_sentado` (carro esperando o embarque terminar).
Todas as esperas usam `while` + `pthread_cond_wait`, portanto não há busy-wait. Usa apenas
`pthread_mutex_init/lock/unlock` e `pthread_cond_init/signal/wait/broadcast`; sem semáforos.
 

📄 **Relatório do Projeto (PDF):** [Acessar vgjda2.pdf](./vgjda2.pdf)
