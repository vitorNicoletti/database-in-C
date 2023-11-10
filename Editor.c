#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct Livro Livro;

struct Livro {
  int id;
  char titulo[MAX];
  Livro *proximo;
};
void verif_arq(FILE *arq) {
  if (arq == NULL) {
    puts("erro ao abrir arquivo");
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

Livro *inserir_ordenado(int novo_valor, char novo_titulo[50],
                        Livro *lista_daora) {
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
Livro *remover(int livro_id, Livro **lista, int *tam) {
  Livro *aux, *remover = NULL;

  if (*lista) {
    if ((*lista)->id == livro_id) {
      remover = *lista;
      *lista = remover->proximo;
      (*tam)--;
    } else {
      Livro *aux = *lista;
      while (aux->proximo && aux->proximo->id != livro_id) {
        aux = aux->proximo;
      }
      if (aux->proximo) {
        remover = aux->proximo;
        aux->proximo = remover->proximo;
        (*tam)--;
      }
    }
  }
  return remover;
}

void buscar(Livro *lista, int livro_id) {
  Livro *aux = lista;
  while (aux != NULL) {
    if (aux->id == livro_id) {
      printf("Livro encontrado: ID: %d, Titulo: %s\n", aux->id, aux->titulo);
      return;
    }
    aux = aux->proximo;
  }
  printf("Livro nao encontrado\n");
}

Livro *armazenar_binario(Livro *nova_lista, FILE *arquivo) {

  Livro L;
  
  while (fread(&L, sizeof(Livro), 1, arquivo)) {
    puts("a");
    nova_lista = inserir_ordenado(L.id, L.titulo, nova_lista);
  };
  return nova_lista;
}

int main() {
  FILE *arq = fopen("texto-base.bin", "rb");
  verif_arq(arq);
  Livro *lista = NULL;
  lista = armazenar_binario(lista, arq);
  imprimir_lista(lista);
  puts("aaaa");

  int opcao;
  int livro_id;
  Livro *removido;
  int tam = 0;

  verif_arq(arq);

  do {
    printf("\nSelecione uma opcao:\n");
    printf("1. Exibir todos os livros\n");
    printf("2. Cadastrar um livro\n");
    printf("3. Excluir um livro\n");
    printf("4. Exibir um livro\n");
    printf("0. Sair\n");
    printf("Digite o numero da opcao desejada: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Esses sao os Livros\n");
      imprimir_lista(lista);
      break;
    case 2:
      printf("Insira a ID e o titulo:\n");
      int novo_valor;
      char novo_titulo[MAX];
      scanf("%d", &novo_valor);
      scanf("%s", novo_titulo);
      inserir_ordenado(novo_valor, novo_titulo, lista);
      tam++;
      break;
    case 3:
      printf("Informe a ID do livro que deseja excluir\n");
      scanf("%d", &livro_id);
      removido = remover(livro_id, &lista, &tam);
      if (removido) {
        printf("Livro removido: %d\n", removido->id);
        free(removido);
      } else {
        printf("Livro nao encontrado\n");
      }
      break;
    case 4:
      printf("Digite o ID do livro que esta procurando:\n");
      scanf("%d", &livro_id);
      buscar(lista, livro_id);
      break;
    case 0:
      printf("Encerrando...\n");
      break;
    default:
      printf("Opcao invalida. Tente novamente.\n");
    }
  } while (opcao != 0);

  return 0;
}
