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

struct operacoes {
    int n;
    struct valores *valores;
    struct posicoes **posicoes;
};

struct posicoes {
    int pos;
    struct posicoes *proximo;
    
};

struct valores {
    int posAntes;
    int valor;
    int posDepois;
    struct valores *proximo;
};

struct posicoes* criarOp(int pos) {
    struct posicoes* po = (struct posicoes*)malloc(sizeof(struct posicoes));
    po->pos = pos;
    po->proximo = NULL;

    return po;
}

struct valores* criarVal(int antes, int val, int depois) {
    struct valores* va = (struct valores*)malloc(sizeof(struct valores));
    va->posAntes = antes;
    va->valor = val;
    va->posDepois = depois;
    va->proximo = NULL;
    
    return va;
}

struct linhas* criarLinha(int estado, char simbolo) {
    struct linhas* linha = (struct linhas*)malloc(sizeof(struct linhas));
    linha->simbolo = simbolo;
    linha->proximoEstado = estado;
    linha->proximo = NULL;

    return linha;
}

void exibirOperacoes(struct operacoes *op) {
    printf("Operacoes:\n");

    struct valores *val = op->valores;
    printf("Valores: ");
    while (val != NULL) {
        printf("(%d, %d, %d) ", val->posAntes, val->valor, val->posDepois);
        val = val->proximo;
    }
    printf("\n");

    printf("Posicoes de Operacoes:\n");
    for (int i = 0; i < op->n; i++) {
        printf("Operacao %d: ", i);
        struct posicoes *pos = op->posicoes[i];
        while (pos != NULL) {
            printf("%d ", pos->pos);
            pos = pos->proximo;
        }
        printf("\n");
    }
}

void preencherTabela(struct tabela *tabela) {
    tabela->transicao = malloc(tabela->n * sizeof(struct linhas *));

    for (unsigned int i = 0; i < tabela->n; i++) {
        tabela->transicao[i] = NULL;
    }


    for (int j = 0; j < 10; j++) {
        struct linhas *linhaAux = criarLinha(1, j + '0');

        linhaAux->proximo = tabela->transicao[0];
        tabela->transicao[0] = linhaAux;

    }

    struct linhas *linhaAux = criarLinha(2, '-');
    linhaAux->proximo = tabela->transicao[0];
    tabela->transicao[0] = linhaAux;
    
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

    for (int j = 0; j < 10; j++) {
        struct linhas *linhaAux = criarLinha(1, j + '0');

        linhaAux->proximo = tabela->transicao[2];
        tabela->transicao[2] = linhaAux;
   
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

int soma(int a, int b) {
    return a + b;
}

int subtracao(int a, int b) {
    return a - b;
}

int multiplicacao(int a, int b) {
    return a * b;
}

int divisao(int a, int b) {
    return a / b;
}

int resolver(struct operacoes *op) {
    int resul = 0;

    for (int i = 0; i < op->n; i++) {
        struct posicoes *pos = op->posicoes[i];
        while (pos != NULL) {
            struct valores *val = op->valores;
            int achou = 0;

            while ((val != NULL) && (!achou)) {
                if (val->proximo != NULL) {
                    if (val->posDepois == pos->pos) {
                        achou = 1;

                        if (i == 0) {
                            val->valor = multiplicacao(val->valor, val->proximo->valor);
                            val->posDepois = val->proximo->posDepois;
                            val->proximo = val->proximo->proximo;

                        }

                        else if (i == 1) {
                            val->valor = divisao(val->valor, val->proximo->valor);
                            val->posDepois = val->proximo->posDepois;
                            val->proximo = val->proximo->proximo;
                        }

                        else if (i == 2) {
                            val->valor = soma(val->valor, val->proximo->valor);
                            val->posDepois = val->proximo->posDepois;
                            val->proximo = val->proximo->proximo;
                        }

                        else {
                            val->valor = subtracao(val->valor, val->proximo->valor);
                            val->posDepois = val->proximo->posDepois;
                            val->proximo = val->proximo->proximo;
                        }
                    }
                }

                val = val->proximo;
            }

            pos = pos->proximo;

        }

        
    }

    resul = op->valores->valor;
    
    printf("Resultado: %d\n", resul);
    return resul;
}

int match(char *string, struct tabela *t) {
    int estadoAtual = t->inicio, i = 0, mudouUmaVez = 0, locPri = 0, locSeg = 0;
    struct operacoes *op = malloc(sizeof(struct operacoes));
    op->n = 4; // primeira posição é multiplicação, segunda é divisão, depois adição e subtração
    op->posicoes = malloc(op->n * sizeof(struct posicoes));
    op->valores = malloc(sizeof(struct valores));
    op->valores = NULL;
    int aux = 0;

    for (int i = 0; i < op->n; i++) {
        op->posicoes[i] = NULL;

    }

    while (string[i] != '\0') {

        char operacaoAtual, simbolo = string[i];
        int proximoEstado = buscarTransicao(t, estadoAtual, simbolo);

        if ((estadoAtual == 1) && (proximoEstado == 2)) {
            locPri = locSeg;
            locSeg = i;

            struct valores *val = criarVal(locPri, aux, locSeg);

            // Adicionar o novo valor à lista de valores em 'op'
            if (op->valores == NULL) {
                op->valores = val;
            } 
            
            else {
                struct valores *temp = op->valores;
                while (temp->proximo != NULL) {
                    temp = temp->proximo;
                }
                temp->proximo = val;
            }
            
            mudouUmaVez = 1;
            operacaoAtual = simbolo;

            if (operacaoAtual == '+') {
                struct posicoes *aux = criarOp(i);

                aux->proximo = op->posicoes[2];
                op->posicoes[2] = aux;
               
            }

            else if (operacaoAtual == '-') {
                struct posicoes *aux = criarOp(i);

                aux->proximo = op->posicoes[3];
                op->posicoes[3] = aux;
            }

            else if (operacaoAtual == '*') {
                struct posicoes *aux = criarOp(i);

                aux->proximo = op->posicoes[0];
                op->posicoes[0] = aux;
            }

            else {
                struct posicoes *aux = criarOp(i);

                aux->proximo = op->posicoes[1];
                op->posicoes[1] = aux;
            }
            
            aux = 0;
        }

        estadoAtual = proximoEstado;

        if (estadoAtual == 1) {
            aux = (aux * 10) + atoi(&simbolo);
        }

        if (proximoEstado == -1) {
            return estadoAtual;

        }

        
        i++;
    }


    if (!mudouUmaVez) {
        printf("%s\n", string);
    }

    else {
        struct valores *val = criarVal(locSeg, aux, strlen(string));

        if (op->valores == NULL) {
            op->valores = val;
        } 
            
        else {
            struct valores *temp = op->valores;
            while (temp->proximo != NULL) {
                temp = temp->proximo;
            }
            temp->proximo = val;
        }

        resolver(op);
    }

    return estadoAtual;
}

int main(int argc, char** argv) {
    struct tabela tabela;
    tabela.n = 3;
    tabela.inicio = 0;
    tabela.final = 1;
    preencherTabela(&tabela);

    int estado = match(argv[1], &tabela);

    if (estado == tabela.final) {
        printf("É uma string válida! \n");


    }
    else {
        printf("Não é uma string válida! \n");
    }
    
    //exibirTabela(&tabela);
    
    return 0;
}
