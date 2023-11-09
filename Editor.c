#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50


typedef struct Livro Livro;

struct Livro
{
    int id;
    char titulo[MAX];
    Livro* proximo;
};

void imprimir_lista(Livro* lista){
    Livro* aux = lista;
    while(aux != NULL){
        printf("ID: %d, Titulo: %s\n", aux->id, aux->titulo);
        aux = aux->proximo;
    }
}

void inserir_ordenado(int novo_valor, char novo_titulo[50], Livro** lista_daora) {
    Livro* novo_livro = (Livro*)malloc(sizeof(Livro));
    novo_livro->id = novo_valor;
    strcpy(novo_livro->titulo, novo_titulo);
    novo_livro->proximo = NULL;

    if (*lista_daora == NULL || (*lista_daora)->id >= novo_livro->id) {
        novo_livro->proximo = *lista_daora;
        *lista_daora = novo_livro;
    } else {
        Livro* aux = *lista_daora;
        while (aux->proximo != NULL && aux->proximo->id < novo_livro->id) {
            aux = aux->proximo;
        }
        novo_livro->proximo = aux->proximo;
        aux->proximo = novo_livro;
    }
}
Livro* remover(int livro_id, Livro** lista, int* tam) {
    Livro *aux, *remover = NULL;

    if (*lista) {
        if ((*lista)->id == livro_id) {
            remover = *lista;
            *lista = remover->proximo;
            (*tam)--;
        } else {
            Livro* aux = *lista;
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

void buscar(Livro* lista, int livro_id) {
    Livro* aux = lista;
    while (aux != NULL) {
        if (aux->id == livro_id) {
            printf("Livro encontrado: ID: %d, Titulo: %s\n", aux->id, aux->titulo);
            return;
        }
        aux = aux->proximo;
    }
    printf("Livro nao encontrado\n");
}

int main() {
    int opcao;
    int livro_id;
    Livro* removido;
    int tam = 0;
    Livro* lista = NULL;

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
                inserir_ordenado(novo_valor, novo_titulo, &lista);
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
