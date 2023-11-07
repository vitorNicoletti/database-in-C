#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct {
    int id;
    char titulo[MAX];
} Livro;

int main() {
    FILE *file;
    char *filename = "D:/Jogos/code/Programacao Imperativa/trabalho 2/texto-base.bin";
    file = fopen(filename, "rb");

    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Obtendo o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    // Alocando memória heap para armazenar os dados
    Livro *livros = (Livro *)malloc(file_size);
    if (!livros) {
        fclose(file);
        fprintf(stderr, "Erro ao alocar memória");
        return 1;
    }

    fread(livros, sizeof(Livro), file_size / sizeof(Livro), file);

    // Exibindo os dados
    int num_livros = file_size / sizeof(Livro);
    for (int i = 0; i < num_livros; i++) {
        printf("ID: %d, Título: %s", livros[i].id, livros[i].titulo);
    }

    free(livros);
    fclose(file);

    return 0;
}
