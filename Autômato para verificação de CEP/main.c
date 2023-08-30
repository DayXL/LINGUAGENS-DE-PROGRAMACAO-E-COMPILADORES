#include <stdio.h>
#include <stdlib.h>

struct linhas {
    char simbolo;
    unsigned int proximoEstado;
    struct linhas *proximo;
};

struct tabela {
    unsigned int n;
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
    tabela->transicao = malloc(tabela->n * sizeof(struct linha *));

    for (unsigned int i = 0; i < tabela->n; i++) {
        tabela->transicao[i] = NULL;
    }

    for (int i = 0; i < tabela->n; i++){
        unsigned posicao = i;

        if (i != 5) {

            for (int j = 0; j < tabela->n; j++) {
                struct linhas *linhaAux = criarLinha(i + 1, j + '0');

                linhaAux->proximo = tabela->transicao[posicao];
                tabela->transicao[posicao] = linhaAux;

            }
        }

        else {
            struct linhas *linhaAux = criarLinha(i + 1, '-');

            linhaAux->proximo = tabela->transicao[posicao];
            tabela->transicao[posicao] = linhaAux;
        }
    }

    
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

int buscarTransicao(struct tabela *tabela, int estadoAtual, char valor) {
    struct linhas *linha = tabela->transicao[estadoAtual];

    while (linha != NULL) {
        if (linha->simbolo == valor) {
            return linha->proximoEstado;
        }

        linha = linha->proximo;
    }

    return -1;
}

int match(char *string, int s, int f, struct tabela *t) {
    int i = 0;
    int estadoAtual = s;

    while (i < f) {
        char simbolo = string[i];
        int proximoEstado = buscarTransicao(t, estadoAtual, simbolo);

        if (proximoEstado == -1) {
            return estadoAtual;
        }

        estadoAtual = proximoEstado;
        i++;
    }

    return estadoAtual;
}

int main(void) {
    struct tabela tabela;
    tabela.n = 10;
    preencherTabela(&tabela);

    char string[100];

    fgets(string, 100, stdin);

    int estado = match(string, 0, 10, &tabela);

    if (estado == 9) {
        printf("O estado terminou em: %d, é uma string válida \n", estado);
    }
    else {
        printf("O estado terminou em: %d, não é uma string válida \n", estado);
    }
    
    //exibirTabela(&tabela);
    
    return 0;
}
