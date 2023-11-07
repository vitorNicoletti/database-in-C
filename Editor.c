#include <stdio.h>

Livro* remover(int livro_id, Livro* lista)
{
    Livro *aux, *remover = NULL;

  if(lista->inicio){
    if(lista->inicio->id == livro_id){
      remover = lista->inicio;
      lista->inicio = remover->proximo;
      lista->tam--;
    }
    else{
      Livro* aux = lista->inicio;
      while(aux->proximo && aux->proximo->id != livro_id){
        aux = aux->proximo;
      if(aux->proximo){
        remover = aux->proximo;
        aux->proximo = remover->proximo;
        lista->tam--;
      }
    }
  }
    return remover;
}   

int main() {
    int opcao;
    Livro* removido;

    do {
        printf("\nSelecione uma opcao:\n");
        printf("1. Exibir todos os livros\n");
        printf("2. Cadastrar um livro\n");
        printf("3. Excluir um livro\n");
        printf("4. Exibir um livro\n");
        printf("0. Sair\n");
        printf("Digite o numero da opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Esses sao os Livros\n");
                imprimir_lista(Livro* lista);
                break;
            case 2:
                printf("Insira a ID e o titulo:\n");
                inserir_ordenado(int novo_valor, char novo_titulo[50],Livro* lista_daora)
                break;
            case 3:
                printf("Informe a ID do livro que deseja excluir\n");
                scanf("%d", &livro_id);
                removido = Livro* remover(%Livro, livro_id);
                if(removido){
                  printf("Livro removido: %d\n", removido->id);
                  free(removido);
                }
                else{
                  printf("Livro nao encontrado\n");
                }
                break;
            case 4:
                printf("Digite o livro que esta procurando:\n");
                buscar();
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
