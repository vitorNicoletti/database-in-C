#include "funcoes_gerador.h"


int main(int argc, char* argv[]) /*Recebe o nome dos arquivos de entrada e saida como parametro*/
{
    if (argc != 3){  /*Verifica se os parametros foram informados*/
        printf("Necessario inserir o nome do programa, arquiovo de entrada e o arquivo de saida"); 
        return 1;
    }

    const char* arquivo_entrada = argv[1];
    const char* arquivo_saida = argv[2];

    Livro* lista = NULL;
    FILE* arq = fopen(arquivo_entrada,"r"); /* Abre o arquivo */
    verif_arq(arq); /* Verifica se o arquivo foi encontrado */
    int id;
    char titulo[50];
    while (fscanf(arq,"%d\n%s",&id,titulo) != EOF) /* Percorre o arquivo até o final */
    {
        lista = inserir_ordenado(id,titulo,lista); /* Organiza de forma ordenada */
        
    }
    fclose(arq);
    printf("%d",lista->id);
    puts("\n");
    imprimir_lista(lista); /*Mostra a lista organizada*/
    arq = fopen(arquivo_saida,"wb");
    inserir_binario(lista,arq); /*insere a nova lista*/
    liberar_lista(lista); /*libera a memoria*/

}
