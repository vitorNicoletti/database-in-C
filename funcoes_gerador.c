#include "funcoes_gerador.h"

void verif_arq(FILE *arq) {
    if (arq == NULL) {
        puts("Erro ao abrir o arquivo");
        exit(1);
    }
}

void inserir_binario(Livro *lista, FILE *arq) {
    verif_arq(arq);

    Livro *q = lista;
    while (q != NULL) {
        fwrite(q, sizeof(Livro), 1, arq);
        q = q->proximo;
    }
}

void imprimir_lista(Livro *lista) {
    Livro *aux = lista;
    while (aux != NULL) {
        printf("ID: %d, Titulo: %s\n", aux->id, aux->titulo);
        aux = aux->proximo;
    }
}

void liberar_lista(Livro *lista) 
{
    if (lista != NULL) {
        if (lista->proximo != NULL) {
            liberar_lista(lista->proximo);
            lista->proximo = NULL;
        }
        free(lista);
    }
}

Livro * inserir_ordenado(int novo_valor, char novo_titulo[MAX],Livro *lista_daora) {
  Livro *novo_livro = (Livro *)malloc(sizeof(Livro));
  novo_livro->id = novo_valor;
  strcpy(novo_livro->titulo, novo_titulo);

  Livro *p = NULL;
  Livro *q = lista_daora;
  bool localizado = true;
  while (q && localizado) {
    if (novo_valor <= q->id) {
      localizado = false;
    } else {
      p = q;
      q = q->proximo;
    }
  }
  if (p == NULL) {
    novo_livro->proximo = lista_daora;
    // lista=novo_livro;

    lista_daora = novo_livro;
  } else {
    p->proximo = novo_livro;
    novo_livro->proximo = q;
  }
  return lista_daora;
}