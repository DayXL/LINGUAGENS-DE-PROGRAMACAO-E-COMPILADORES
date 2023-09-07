#include <stdio.h>
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

int match(char *string, struct tabela *t) {
    int i = 0;
    int estadoAtual = t->inicio;

    while (string[i] != '\0') {
        char simbolo = string[i];
        int proximoEstado = buscarTransicao(t, estadoAtual, simbolo);

        estadoAtual = proximoEstado;

        if (proximoEstado == -1) {
            return estadoAtual;

        }

        i++;
    }
 
    return estadoAtual;
}

int main(int argc, char** argv) {
    struct tabela tabela;
    tabela.n = 10;
    tabela.inicio = 0;
    tabela.final = 9;
    preencherTabela(&tabela);

    int estado = match(argv[1], &tabela);

    if (estado == tabela.final) {
        printf("É uma string válida! \n");
    }
    else {
        printf("Não é uma string válida! \n");
    }
    
    //cleexibirTabela(&tabela);
    
    return 0;
}
