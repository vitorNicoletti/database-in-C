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

Livro * inserir_ordenado(int novo_valor, char novo_titulo[50],Livro *lista_daora) {
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
/*Livro *remover(int livro_id, Livro **lista, int *tam) {
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
*/

Livro * remover(Livro *lista, int livro_id) 
{
    Livro *resposta = NULL;
    Livro *p = NULL;
    Livro *aux = lista; 
    while (aux!=NULL && resposta == NULL)
    {
        if(aux->id == livro_id)
        {
            if (p==NULL)
            {
                free(lista);
                resposta = aux->proximo;
            }
            else
            {
                p->proximo = aux->proximo;
                free(aux);
                resposta = lista;
            }
        
        }
            p=aux;
            aux = aux->proximo;
    }
    return resposta;
}

Livro* buscar_por_id(Livro *lista, int livro_id) 
{
    if(lista->id == livro_id)
        return lista;
    
    if (lista->proximo == NULL)
        return NULL;
    else
        return buscar_por_id(lista->proximo,livro_id);
}


Livro *armazenar_binario(Livro *nova_lista, FILE *arquivo) {

  Livro L;

  while (fread(&L, sizeof(Livro), 1, arquivo)) {
    nova_lista = inserir_ordenado(L.id, L.titulo, nova_lista);
  };
  return nova_lista;
}


int main() 
{
    FILE *arq = fopen("D:/Jogos/code/Programacao Imperativa/trabalho 2/texto-base.bin", "rb");
    verif_arq(arq);
    Livro *lista = NULL;
    lista = armazenar_binario(lista, arq);


    int opcao;
    int livro_id;

    int tam = 0;

    do 
    {
        char opcoes[153] = 
        "\nSelecione uma opcao:\n"
        "1. Exibir todos os livros\n"
        "2. Cadastrar um livro\n"
        "3. Excluir um livro\n"
        "4. Exibir um livro\n"
        "0. Sair\n"
        "Digite o numero da opcao desejada: ";
        
        puts(opcoes);
        scanf("%d", &opcao);

        switch (opcao) 
        {
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
                
                if (buscar_por_id(lista,livro_id) == NULL)
                {
                    puts("livro nao encontrado!");
                }
                else
                {
                    lista = remover(lista,livro_id);
                    printf("Livro removido: %d\n", livro_id);
                }
                
            break;
            case 4:
                puts("Digite o ID do livro que esta procurando:\n");
                scanf("%d", &livro_id);
                Livro* L = buscar_por_id(lista, livro_id);
                if (L == NULL)
                    printf("Livro de ID:%d nao encontrado!\n",livro_id);
                else
                    printf("Livro Encontrado!\nID:%d\nTITULO:%s\n",L->id,L->titulo);
            break;
            case 0:
                printf("Encerrando...\n");
            break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
    while (opcao != 0);

  return 0;
}
