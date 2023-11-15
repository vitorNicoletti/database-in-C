#ifndef funcoes
#define funcoes

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
void imprimir_lista(Livro *lista); /*Imprimir a lista */
void inserir_binario(Livro* lista, FILE* arq); /*Insere as modificaçoes*/
Livro * inserir_ordenado(int novo_valor, char novo_titulo[MAX], Livro *lista_daora); /* Cadastrar um livro de forma ordenada */
Livro * remover(Livro *lista, int livro_id); /* Exclui um livro selecionado */
Livro* buscar_por_id(Livro *lista, int livro_id); /* Procura o livro pelo ID */
Livro *armazenar_binario(Livro *nova_lista, FILE *arquivo); /* Salva as operacoes feitas */
void liberar_lista(Livro *lista); /* Libera a memoria */

#endif