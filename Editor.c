#include "funcoes_editor.h"

int main(int argc, char* argv[]) /*Recebe o arquivo de entrada e arquivo de saida como parametro*/
{
    if (argc != 3){ /*Verifica se os parametro foram informados*/
        printf("Necessario inserir o nome do programa, arquiovo de entrada e o arquivo de saida");
        return 1;
    }

    const char* arquivo_entrada = argv[1];
    const char* arquivo_saida = argv[2];

    FILE *arq = fopen(arquivo_entrada, "rb");
    verif_arq(arq); /*Verifica se o arquivo foi aberto corretamente*/

    Livro *lista = NULL;
    lista = armazenar_binario(lista, arq); /* Armazena a lista*/
    int opcao;
    int livro_id;
    bool modificado = false; /*Booleano para verificar se o arquivo foi modificado*/

    do {
        char opcoes[] = 
        "\nSelecione uma opcao:\n"
        "1. Exibir todos os livros\n"
        "2. Cadastrar um livro\n"
        "3. Excluir um livro\n"
        "4. Exibir um livro\n"
        "5. Gerar arquivo binario com as modificacoes\n"
        "0. Sair\n"
        "Digite o numero da opcao desejada: ";
        
        puts(opcoes);
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("Esses sao os Livros\n");
                imprimir_lista(lista);  /*Imprime todos os lvros*/
                break;

            case 2:
                printf("Insira a ID e o titulo:\n");
                int novo_valor;
                char novo_titulo[MAX];
                scanf("%d", &novo_valor);
                scanf("%s", novo_titulo);

                if (buscar_por_id(lista, novo_valor) == NULL) { /*Procura se o valor do id nao existe*/
                    inserir_ordenado(novo_valor, novo_titulo, lista); /*se nao existir insere de forma ordenada*/
                    puts("Adicionado com sucesso!");
                    modificado = true;
                } else {
                    puts("ID ja existente!");
                }
                break;

            case 3:
                printf("Informe a ID do livro que deseja excluir\n");
                scanf("%d", &livro_id);
                
                if (buscar_por_id(lista, livro_id) == NULL) {  /*Procura se o ID existe*/
                    puts("Livro nao encontrado!");
                } else {
                    lista = remover(lista, livro_id); /* Se encontrado exclui o livro*/
                    printf("Livro removido: %d\n", livro_id);
                    modificado = true;
                }
                break;

            case 4:
                puts("Digite o ID do livro que esta procurando:\n");
                scanf("%d", &livro_id);
                Livro* L = buscar_por_id(lista, livro_id); /*Procura o ID*/
                if (L == NULL)
                    printf("Livro de ID:%d nao encontrado!\n", livro_id);
                else
                    printf("Livro Encontrado!\nID:%d\nTITULO:%s\n", L->id, L->titulo);
                break;

            case 5:
                arq = fopen(arquivo_saida, "wb");
                verif_arq(arq); /*Verifica se o arquivo foi aberto*/
                inserir_binario(lista, arq); /*Insere a nova lista*/
                puts("Arquivo criado com sucesso!");
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    if (modificado) { /*Salva a modificaçao feita na nova lista*/
        arq = fopen(arquivo_saida, "wb");
        inserir_binario(lista, arq);
    }
    
    liberar_lista(lista); /*Libera a memoria*/

    return 0;
}
