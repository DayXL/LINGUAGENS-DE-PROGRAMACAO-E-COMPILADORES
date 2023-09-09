#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct linhas {
    char simbolo;
    unsigned int proximoEstado;
    struct linhas *proximo;
};

struct tabela {
    unsigned int n;
    unsigned int inicio;
    unsigned int final;
    struct linhas **transicao;
};

struct linhas* criarLinha(int estado, char simbolo) {
    struct linhas* linha = (struct linhas*)malloc(sizeof(struct linhas));
    linha->simbolo = simbolo;
    linha->proximoEstado = estado;
    linha->proximo = NULL;

    return linha;
}

void preencherTabela(struct tabela *tabela) {
    tabela->transicao = malloc(tabela->n * sizeof(struct linhas *));

    for (unsigned int i = 0; i < tabela->n; i++) {
        tabela->transicao[i] = NULL;
    }

    // Estado 0 vai para

    for (int j = 0; j < 10; j++) {
        struct linhas *linhaAux = criarLinha(1, j + '0');

        linhaAux->proximo = tabela->transicao[0];
        tabela->transicao[0] = linhaAux;

    }

    struct linhas *linhaAux = criarLinha(2, '-');
    linhaAux->proximo = tabela->transicao[0];
    tabela->transicao[0] = linhaAux;

    linhaAux = criarLinha(3, '(');
    linhaAux->proximo = tabela->transicao[0];
    tabela->transicao[0] = linhaAux;

    linhaAux = criarLinha(3, '[');
    linhaAux->proximo = tabela->transicao[0];
    tabela->transicao[0] = linhaAux;

    linhaAux = criarLinha(3, '{');
    linhaAux->proximo = tabela->transicao[0];
    tabela->transicao[0] = linhaAux;
    
    // Estado 1 vai para

    for (int j = 0; j < 10; j++) {
        struct linhas *linhaAux = criarLinha(1, j + '0');

        linhaAux->proximo = tabela->transicao[1];
        tabela->transicao[1] = linhaAux;

    }

    linhaAux = criarLinha(2, '-');

    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(2, '+');

    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(2, '*');

    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(2, '/');

    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(3, '(');
    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(3, '[');
    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(3, '{');
    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;


    // Estado 2 vai para

    for (int j = 0; j < 10; j++) {
        struct linhas *linhaAux = criarLinha(1, j + '0');

        linhaAux->proximo = tabela->transicao[2];
        tabela->transicao[2] = linhaAux;
   
    }

    linhaAux = criarLinha(3, '(');
    linhaAux->proximo = tabela->transicao[2];
    tabela->transicao[2] = linhaAux;

    linhaAux = criarLinha(3, '[');
    linhaAux->proximo = tabela->transicao[2];
    tabela->transicao[2] = linhaAux;

    linhaAux = criarLinha(3, '{');
    linhaAux->proximo = tabela->transicao[2];
    tabela->transicao[2] = linhaAux;

    // Estado 3 vai para

    for (int j = 0; j < 10; j++) {
        struct linhas *linhaAux = criarLinha(1, j + '0');

        linhaAux->proximo = tabela->transicao[3];
        tabela->transicao[3] = linhaAux;

    }

    linhaAux = criarLinha(2, '-');

    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(2, '+');

    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(2, '*');

    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(2, '/');

    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(3, '(');
    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(3, '[');
    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(3, '{');
    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;
    
}

void exibirTabela(struct tabela *tabela) {
    for (unsigned int i = 0; i < tabela->n; i++) {
        struct linhas *linha = tabela->transicao[i];
        printf("Estado %u:\n", i);

        while (linha != NULL) {
            printf("  Símbolo: %c, Próximo Estado: %u\n", linha->simbolo, linha->proximoEstado);
            linha = linha->proximo;
        }
    }
}


int main(int argc, char** argv) {
    struct tabela tabela;
    tabela.n = 4;
    tabela.inicio = 0;
    tabela.final = 1;
    preencherTabela(&tabela);

    // int estado = match(argv[1], &tabela);

    // if (estado == tabela.final) {
    //     printf("É uma string válida! \n");
    // }
    // else {
    //     printf("Não é uma string válida! \n");
    // }
    
    exibirTabela(&tabela);
    
    return 0;
}
