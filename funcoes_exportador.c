#include "funcoes_exportador.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50


Livro* inserir_ordenado(int novo_valor, char novo_titulo[50],Livro* lista_daora)
{
    Livro* novo_livro = (Livro*) malloc(sizeof(Livro));
    novo_livro->id = novo_valor;
    strcpy(novo_livro->titulo, novo_titulo);
    
    Livro* p=NULL;
    Livro* q = lista_daora;
    bool localizado = true;
    while (q && localizado)
    {
        if (novo_valor <= q->id)
        {
            localizado=false;
        }
        else
        {
            p=q;
            q=q->proximo;
        }
    }
    if (p==NULL)
    {
        novo_livro->proximo = lista_daora;
        //lista=novo_livro;
        
        lista_daora = novo_livro;
    }
    else
    {
        p->proximo = novo_livro;
        novo_livro->proximo = q;  
    }
    return lista_daora;
}
Livro *armazenar_binario(Livro *nova_lista, FILE *arquivo) {

  Livro L;

  while (fread(&L, sizeof(Livro), 1, arquivo)) {
    nova_lista = inserir_ordenado(L.id, L.titulo, nova_lista);
  };
  return nova_lista;
}

void binario_para_texto(Livro *lista, char* arquivo_saida) {
    FILE *arquivo_texto = fopen(arquivo_saida, "wt");

    Livro *p = lista;
    while (p != NULL) {
        fprintf(arquivo_texto, "%d\n%s\n", p->id, p->titulo);
        p = p->proximo;
    }

    fclose(arquivo_texto);
}

void liberar_lista(Livro *lista) {
    if (lista != NULL) {
        if (lista->proximo != NULL) {
            liberar_lista(lista->proximo);
            lista->proximo = NULL;
        }
        free(lista);
    }
}
