#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef struct Livro Livro;
struct Livro
{
    int id;
    char titulo[50];
    Livro* proximo;
};
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
void binario_para_texto(Livro *lista) {
    FILE *arquivo_texto = fopen("D:/Jogos/code/Programacao Imperativa/trabalho 2/texto-final.txt", "wt");

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

int main() {
    Livro *lista = NULL;
    FILE *arq = fopen("D:/Jogos/code/Programacao Imperativa/trabalho 2/texto-editado.bin", "rb");

    lista = armazenar_binario(lista, arq);

    fclose(arq);

    binario_para_texto(lista);
    liberar_lista(lista);

    return 0;
}
