#ifndef funcoes_gerador
#define funcoes_gerador

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

void verif_arq(FILE *arq); /* Verificaçao do arquivo */
void inserir_binario(Livro *lista, FILE *arq); /*Insere a nova lista*/
void imprimir_lista(Livro *lista); /*Imprimir a lista */
void liberar_lista(Livro *lista); /* Libera a memoria */
Livro *inserir_ordenado(int novo_valor, char novo_titulo[MAX], Livro *lista_daora); /* Organiza a lista de forma ordenada*/

#endif