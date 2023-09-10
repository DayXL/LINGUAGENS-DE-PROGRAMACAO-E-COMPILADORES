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

typedef struct memoria {
    int tam;
    char **lista;
} Memoria;

int removeFila(Memoria* memoria, char simbolo) {
    if (simbolo == ')') {
        simbolo = '(';

    }

    else if (simbolo == ']') {
        simbolo = '[';

    }

    else {
        simbolo = '{';
    }

    if ((memoria->lista[(memoria->tam) - 1])[0] == simbolo) {
        Memoria nova;
        nova.tam = memoria->tam - 1;
        nova.lista = malloc(sizeof(char*) * nova.tam);

        for (int i = 0; i < nova.tam; i++) {
            nova.lista[i] = memoria->lista[i + 1];

        }

        free(memoria->lista);
    
        (*memoria) = nova;

        return 1;

    } 

    return -1;

}

void adicionarFila(Memoria* memoria, char* novoValor) {
    Memoria nova;
    nova.tam = memoria->tam + 1;
    nova.lista = (char **)malloc(sizeof(char *) * nova.tam);

    for (int i = 0; i < nova.tam - 1; i++) {
        nova.lista[i] = memoria->lista[i];
    }

    nova.lista[nova.tam - 1] = (char *)malloc(sizeof(char));
    *(nova.lista[nova.tam - 1]) = *novoValor;

    free(memoria->lista);
    (*memoria) = nova;
}

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

    linhaAux = criarLinha(4, '}');

    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(4, ']');

    linhaAux->proximo = tabela->transicao[1];
    tabela->transicao[1] = linhaAux;

    linhaAux = criarLinha(4, ')');

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

    linhaAux = criarLinha(3, '(');
    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(3, '[');
    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    linhaAux = criarLinha(3, '{');
    linhaAux->proximo = tabela->transicao[3];
    tabela->transicao[3] = linhaAux;

    // Estado 4 vai para

    linhaAux = criarLinha(2, '-');

    linhaAux->proximo = tabela->transicao[4];
    tabela->transicao[4] = linhaAux;

    linhaAux = criarLinha(2, '+');

    linhaAux->proximo = tabela->transicao[4];
    tabela->transicao[4] = linhaAux;

    linhaAux = criarLinha(2, '*');

    linhaAux->proximo = tabela->transicao[4];
    tabela->transicao[4] = linhaAux;

    linhaAux = criarLinha(2, '/');

    linhaAux->proximo = tabela->transicao[4];
    tabela->transicao[4] = linhaAux;

    
    linhaAux = criarLinha(4, '}');

    linhaAux->proximo = tabela->transicao[4];
    tabela->transicao[4] = linhaAux;

    linhaAux = criarLinha(4, ']');

    linhaAux->proximo = tabela->transicao[4];
    tabela->transicao[4] = linhaAux;

    linhaAux = criarLinha(4, ')');

    linhaAux->proximo = tabela->transicao[4];
    tabela->transicao[4] = linhaAux;
    
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
        printf("%c %c ", linha->simbolo, valor);
        getchar();
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
    Memoria memoria;
    memoria.tam = 0;

    while (string[i] != '\0') {
        char simbolo = string[i];
        int proximoEstado;

        if ((simbolo == ')') || (simbolo == '}') || (simbolo == ']')) {
            if (memoria.tam == 0) {
                return -1;
            }
            proximoEstado = removeFila(&memoria, simbolo);

            if (proximoEstado == -1) {
                return -1;
            }
        }

        else {
            
            proximoEstado = buscarTransicao(t, estadoAtual, simbolo);

            estadoAtual = proximoEstado;
           
            if (estadoAtual == 3) {
                adicionarFila(&memoria, &simbolo);
            }
        }

        if (proximoEstado == -1) {
            return estadoAtual;

        }
   
        i++;
    }

    if (memoria.tam != 0) {
        return -1;
    }

    return estadoAtual;
}

int main(int argc, char** argv) {
    struct tabela tabela;
    tabela.n = 5;
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
