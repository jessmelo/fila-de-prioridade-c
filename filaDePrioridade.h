#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

// esse ep é baseado na implementação de listas duplamente ligadas ordenadas e com nó cabeça
// e também utilizaremos um arranjo auxiliar

// obs.: a lista utilizada será ordenada de forma decrescente 

typedef int bool;

typedef struct aux {
  int id;
  float prioridade;
  struct aux* ant;
  struct aux* prox;
} ELEMENTO, * PONT;

typedef struct {
  int maxElementos;
  PONT fila;
  PONT* arranjo;
} FILADEPRIORIDADE, * PFILA;

PFILA criarFila(int max);

int tamanho(PFILA f);

bool inserirElemento(PFILA f, int id, float prioridade);

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade);

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade);

PONT removerElemento(PFILA f);

bool consultarPrioridade(PFILA f, int id, float* resposta);