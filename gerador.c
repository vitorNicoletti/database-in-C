#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef struct Livro Livro;

struct Livro
{
    int id;
    char titulo[50];
    Livro* proximo;
};

void verif_arq(FILE*arq){
    if (arq==NULL)
    {
        puts("erro ao abrir arquivo");
        exit(1);
    }
    
}
void inserir_binario(Livro* lista,FILE*arq)
{
    verif_arq(arq);

    Livro* q = lista;
    while (q!= NULL)
    {
        fwrite(q,sizeof(Livro),1,arq);
        q = q->proximo;
    }
}

void liberar_lista(Livro *lista) 
{
    if (lista != NULL) {
        if (lista->proximo != NULL) {
            liberar_lista(lista->proximo);
            lista->proximo = NULL;
        }
        free(lista);
    }
}
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
void imprimir_lista(Livro* lista)
{
    
    Livro *P = lista;
    
    while (P != NULL)
    {
    printf("%d-%s ", P->id,P->titulo);
    P = P->proximo;
    }
    putchar('\n');
}

int main()
{
    Livro* lista = NULL;
    FILE* arq = fopen("D:/Jogos/code/Programacao Imperativa/trabalho 2/texto-base.txt","r");
    verif_arq(arq);
    int id;
    char titulo[50];
    while (fscanf(arq,"%d\n%s",&id,titulo) != EOF)
    {
        lista = inserir_ordenado(id,titulo,lista);
        
    }
    fclose(arq);
    printf("%d",lista->id);
    puts("\n");
    imprimir_lista(lista);
    arq = fopen("D:/Jogos/code/Programacao Imperativa/trabalho 2/texto-base.bin","wb");
    inserir_binario(lista,arq);
    liberar_lista(lista);

}