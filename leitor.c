#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX 10
/*
int main()
{
    char palavra[MAX];
    FILE* arq = fopen("D:/Jogos/code/Programacao Imperativa/trabalho
2/output/teste.bin","rb"); fread(palavra,1,MAX,arq); fclose(arq); for(int i =0;
i<MAX;i++)
    {
        printf("%c",palavra[i]);
        putchar('\n');
    }

}
*/
typedef struct Livro Livro;
struct Livro {
  int id;
  char titulo[50];
  Livro *proximo;
};
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
void imprimir_lista(Livro *lista) {

  Livro *P = lista;

  while (P != NULL) {
    printf("%d-%s ", P->id, P->titulo);
    P = P->proximo;
  }
  putchar('\n');
}
int main() {
  Livro L;
  Livro *nova_lista = NULL;
  FILE *arq = fopen("texto-base.bin", "rb");

  while (fread(&L, sizeof(Livro), 1, arq)) {
    inserir_ordenado(L.id, L.titulo, nova_lista);
    printf("%d-%s\n", L.id, L.titulo);
  };
  fclose(arq);
  imprimir_lista(nova_lista);
}
