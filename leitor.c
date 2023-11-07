#include <stdio.h>
#define MAX 10
/*
int main()
{
    char palavra[MAX];
    FILE* arq = fopen("D:/Jogos/code/Programacao Imperativa/trabalho 2/output/teste.bin","rb");
    fread(palavra,1,MAX,arq);
    fclose(arq);
    for(int i =0; i<MAX;i++)
    {
        printf("%c",palavra[i]);
        putchar('\n');
    }
    
}
*/
typedef struct Livro Livro;
struct Livro
{
    int id;
    char titulo[50];
    Livro* proximo;
};

int main()
{
    Livro L;
    FILE* arq = fopen("D:/Jogos/code/Programacao Imperativa/trabalho 2/texto-base.bin","rb");
    fread(&L,sizeof(Livro),1,arq);
    fclose(arq);
    printf("%d-%s\n",L.id,L.titulo);
}
