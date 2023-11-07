

/*

int main()
{
    char palavra[MAX];
    for(int i =0; i<MAX;i++)
    {
        palavra[i] = i+'a';
    }
    FILE* arq = fopen("teste.bin","wb");
    fwrite(palavra,1,MAX,arq);
    fclose(arq);
}

    typedef struct
    {
        char titulo[50];
        char autor[50]
    }Livro;
    
int main(){
    Livro L;
    strcpy(L.titulo,"ensaio");
    strcpy(L.autor,"LuanGC");
    FILE* arq = fopen("struct.bin","wb");
    fwrite(&L,sizeof(Livro),1,arq);
    fclose(arq);
    
}
*/
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
Livro* lista = NULL;
void inserir_ordenado(int novo_valor, char novo_titulo[50])
{
    Livro* novo_livro = (Livro*) malloc(sizeof(Livro));
    novo_livro->id = novo_valor;
    strcpy(novo_livro->titulo, novo_titulo);
    
    Livro* p=NULL;
    Livro* q = lista;
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
        novo_livro->proximo = lista;
        lista=novo_livro;
    }
    else
    {
        p->proximo = novo_livro;
        novo_livro->proximo = q;
    }
}
void imprimir_lista()
{
Livro* p = lista;
while (p)
{
printf("%d-%s ", p->id,p->titulo);
p = p->proximo;
}
putchar('\n');
}
int main()
{
inserir_ordenado(1,"Eduardo");
inserir_ordenado(2,"Roberto");
inserir_ordenado(5,"Carlos");
inserir_ordenado(3,"Maduardo");
imprimir_lista();
}