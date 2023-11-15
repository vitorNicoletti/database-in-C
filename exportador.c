#include "funcoes_exportador.h"

int main(int argc, char* argv[]) /*recebe o arquivo de entrada e o de saida como parametro*/
{
    if (argc != 3){ /*verifica se os parametros foram informados*/
        printf("Necessario inserir o nome do programa, arquiovo de entrada e o arquivo de saida");
        return 1;
    }

    const char* arquivo_entrada = argv[1];
    char* arquivo_saida = argv[2];

    Livro *lista = NULL;
    FILE *arq = fopen(arquivo_entrada, "rb");

    lista = armazenar_binario(lista, arq); /*Define a nova lista*/

    fclose(arq);

    binario_para_texto(lista, arquivo_saida); /*converte de binario para texto*/
    liberar_lista(lista); /*libera a memoria*/

    return 0;
}
