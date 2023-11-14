#include "funcoes.h"

void verif_arq(FILE *arq) {
    if (arq == NULL) {
        puts("Erro ao abrir o arquivo");
        exit(1);
    }
}

void imprimir_lista(Livro *lista) {
    Livro *aux = lista;
    while (aux != NULL) {
        printf("ID: %d, Titulo: %s\n", aux->id, aux->titulo);
        aux = aux->proximo;
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

Livro *remover(Livro *lista, int livro_id) {
    Livro *resposta = NULL;
    Livro *p = NULL;
    Livro *aux = lista; 

    while (aux != NULL && resposta == NULL) {
        if (aux->id == livro_id) {
            if (p == NULL) {
                free(lista);
                resposta = aux->proximo;
            } else {
                p->proximo = aux->proximo;
                free(aux);
                resposta = lista;
            }
        }

        p = aux;
        aux = aux->proximo;
    }

    return resposta;
}

Livro *buscar_por_id(Livro *lista, int livro_id) {
    if (lista->id == livro_id)
        return lista;

    if (lista->proximo == NULL)
        return NULL;
    else
        return buscar_por_id(lista->proximo, livro_id);
}

Livro *armazenar_binario(Livro *nova_lista, FILE *arquivo) {
    Livro L;

    while (fread(&L, sizeof(Livro), 1, arquivo)) {
        nova_lista = inserir_ordenado(L.id, L.titulo, nova_lista);
    }

    return nova_lista;
}

void inserir_binario(Livro *lista, FILE *arq) {
    verif_arq(arq);

    Livro *q = lista;
    while (q != NULL) {
        fwrite(q, sizeof(Livro), 1, arq);
        q = q->proximo;
    }
}
