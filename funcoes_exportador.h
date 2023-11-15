#ifndef funcoes_exportador
#define funcoes_exportador

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

Livro* inserir_ordenado(int novo_valor, char novo_titulo[50],Livro* lista_daora); /* Cadastrar um livro de forma ordenada */
Livro *armazenar_binario(Livro *nova_lista, FILE *arquivo); /* Salva as operacoes feitas */
void binario_para_texto(Livro *lista, char* arquivo_saida); /* converte de binario pra texto */
void liberar_lista(Livro *lista); /* Libera a memoria */


#endif