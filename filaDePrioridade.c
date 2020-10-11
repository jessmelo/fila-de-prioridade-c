#include "filaDePrioridade.h"

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) res->arranjo[i] = NULL;
  PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
  res->fila = cabeca;
  cabeca->ant = cabeca;
  cabeca->prox = cabeca;
  cabeca->id = -1;
  cabeca->prioridade = 1000000;
  return res;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
  PONT atual = f->fila;
  printf("%p[%i;%f;%p]%p \n", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
  atual = atual->prox;
  while (atual != f->fila){
    printf("%p[%i;%f;%p]%p \n", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
  }
  printf("\nElementos validos: ");
  atual = atual->prox;
  while (atual != f->fila){
    printf("[%i;%f;%p] ", atual->id, atual->prioridade, atual);
    atual = atual->prox;
  }

  printf("\nValores do arrajo:\n\[ ");
  int x;
  for (x=0;x<f->maxElementos;x++) printf("%p ",f->arranjo[x]);
  printf("]\n\n");
}

int tamanho(PFILA f){
  int tam = 0;
  PONT atual = f->fila;
  atual = atual->prox;
  while (atual != f->fila){
    atual = atual->prox;
    tam++;
  }
  return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  bool resposta = false;

  // inserir na ordem descrecente de prioridade 
  if (id < 0 || id >= f->maxElementos) return resposta;

  if(tamanho(f) == 0){
      PONT novo = (PONT) malloc(sizeof(ELEMENTO));
      novo->id = id;
      novo->prioridade = prioridade;
      novo->ant = f->fila;
      novo->prox = f->fila;
      f->fila->prox = novo;
      f->fila->ant = novo;
      f->arranjo[id] = novo;
      resposta = true;
      return resposta;
  }

  // verificando se já existe esse id na fila
  PONT atual = f->fila;
  atual = atual->prox;
  while (atual != f->fila){
    if(atual->id == id) return resposta;

    if(atual->prioridade <= prioridade){
        PONT novo = (PONT) malloc(sizeof(ELEMENTO));
        novo->id = id;
        novo->prioridade = prioridade;
        novo->ant = atual->ant;
        novo->prox = atual;
        atual->ant->prox = novo;
        atual->ant = novo;
        f->arranjo[id] = novo;
        resposta = true;
        return resposta;
    }
    atual = atual->prox;
  }

  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->id = id;
  novo->prioridade = prioridade;
  novo->ant = f->fila->ant;
  novo->prox = f->fila;
  f->fila->ant->prox = novo;
  f->arranjo[id] = novo;
  resposta = true;
  
  return resposta;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;

  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL) return resposta;

  if(f->arranjo[id]->prioridade >= novaPrioridade){
    resposta = false;
    return resposta;
  } else{
    f->arranjo[id]->prioridade = novaPrioridade;
    resposta = true;
  }

  // ordenando a fila em ordem descrecente de prioridade:

  PONT aux;
  PONT prox;

  while(f->arranjo[id]->prioridade > f->arranjo[id]->ant->prioridade){
      aux = f->arranjo[id]->ant;
      aux->ant->prox = f->arranjo[id];
      prox = f->arranjo[id]->prox;
      f->arranjo[id]->prox = aux;
      f->arranjo[id]->ant = aux->ant;
      aux->ant = f->arranjo[id];
      aux->prox = prox;
  }

  return resposta;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;

  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL) return resposta;

  if(f->arranjo[id]->prioridade <= novaPrioridade){
    resposta = false;
    return resposta;
  } else{
    f->arranjo[id]->prioridade = novaPrioridade;
    resposta = true;
  }

  // ordenando a fila em ordem descrecente de prioridade:

  PONT aux;
  PONT prox;
  PONT ant;
  while(f->arranjo[id]->prioridade < f->arranjo[id]->prox->prioridade && f->arranjo[id]->prox != f->fila){
      aux = f->arranjo[id]->prox;
      ant = f->arranjo[id]->ant;
      ant->prox = f->arranjo[id]->prox;
      prox = f->arranjo[id]->prox->prox;
      prox->ant = f->arranjo[id];
      aux->ant = ant;
      aux->prox = f->arranjo[id];
      f->arranjo[id]->ant = aux;
      f->arranjo[id]->prox = prox;
  }

  return resposta;
}

PONT removerElemento(PFILA f){
  PONT resposta = NULL;

  if(tamanho(f) == 0) return resposta;

  // colocando NULL na posição do elemento no arranjo
  int id = f->fila->prox->id;
  f->arranjo[id] = NULL;

  resposta = f->fila->prox;
  f->fila->prox = f->fila->prox->prox;
  f->fila->prox->ant = f->fila;

  return resposta;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool resp = false;

  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL) return resp;

  *resposta = f->arranjo[id]->prioridade;
  resp = true;

  return resp;
}

