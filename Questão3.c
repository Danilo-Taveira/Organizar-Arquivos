/*3) Construa um programa que utilize uma �rvore bin�ria de busca para simular uma �rvore de diret�rios de um sistema de arquivos. Os dados de cada diret�rio s�o: nome, data de cria��o, tamanho em bytes. A �rvore deve ser organizada utilizando-se os nomes dos diret�rios. Lembre que cada opera��o do programa deve ser realizada por uma fun��o. Construa um ?menu? para que o usu�rio escolha a op��o que desejar no programa.

    a) Inserir os dados de um diret�rio na �rvore.
    b) Consultar os dados de um diret�rio na �rvore.
    c) Exibir os dados de todos os diret�rios, utilizando o percurso em ordem.
    d) Remover um diret�rio. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

struct arvore {
    char nome[40];
    char data_criacao[15];
    int tamanho;
    struct arvore *esquerda, *direita;
};

typedef struct arvore *Pont_arvore;

int vazia(Pont_arvore ponteiro) {
    return(ponteiro == NULL);
}

void inserir(Pont_arvore *ponteiro, char nome[], char data[], int tamanho) {
    Pont_arvore novo_no;

    if ((*ponteiro) == NULL) {
        novo_no = (Pont_arvore)malloc(sizeof(struct arvore));
        strcpy(novo_no->nome, nome);
        strcpy(novo_no->data_criacao, data);
        novo_no->tamanho = tamanho;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        *ponteiro = novo_no;
    }
    else {
        if(strcmp(nome, (*ponteiro)->nome) < 0) {
            inserir(&(*ponteiro)->esquerda, nome, data, tamanho);
        }
        else {
            inserir(&(*ponteiro)->direita, nome, data, tamanho);
        }
    }
}

void consultar_dados(Pont_arvore ponteiro, char nome[]) {
    if (ponteiro != NULL) {
        if (strcmp(nome, (ponteiro)->nome) == 0) {
            printf("\nNome: %s\n", ponteiro->nome);
            printf("\nData de cria��o: %s\n", ponteiro->data_criacao);
            printf("\nTamanho(em Bytes): %d\n", ponteiro->tamanho);
        }
        else {
            if (strcmp(nome, ponteiro->nome) < 0) {
                consultar_dados(ponteiro->esquerda, nome);
            }
            else {
                consultar_dados(ponteiro->direita, nome);
            }
        }   
    }
    else {
        printf("\nDiret�rio n�o registrado!\n");
    }
}
void exibir_dados (Pont_arvore ponteiro) {
   if (ponteiro != NULL) {
        exibir_dados(ponteiro->esquerda);
        printf("\nNome: %s\n",ponteiro->nome);
        printf("\nData de cria��o: %s\n", ponteiro->data_criacao);
        printf("\nTamanho(em Bytes): %d\n", ponteiro->tamanho);
        exibir_dados(ponteiro->direita);
   }
}
Pont_arvore getmax (Pont_arvore ponteiro) {
    if (ponteiro->direita == NULL) {
        return(ponteiro);
    }
    else {
        return(getmax(ponteiro->direita));
    }
}
void excluir(Pont_arvore *ponteiro, char nome[]) {
    Pont_arvore aux_1, aux_2;

    if ((*ponteiro) != NULL) {
        if (strcmp(nome, (*ponteiro)->nome) == 0) {
            aux_1 = (*ponteiro);
            if ((*ponteiro)->esquerda == NULL) {
                (*ponteiro) = (*ponteiro)->direita;
            }
            else {
                aux_1 = (*ponteiro)->esquerda;
                aux_2 = getmax(aux_1);
                strcpy((*ponteiro)->nome, aux_2->nome);
                if((aux_1->direita == NULL) && (aux_1->esquerda == NULL)) {
                    (*ponteiro)->esquerda = NULL;
                }
                else {
                    if (aux_1->direita != NULL) {
                        while (strcmp(aux_1->direita->nome, aux_2->nome) != 0) {
                            aux_1 = aux_1->direita;
                        }
                        if (aux_2->esquerda == NULL) {
                            aux_1->direita = NULL;
                        }
                        else {
                            aux_1->direita = aux_2->esquerda;
                        }
                    }
                    else {
                        (*ponteiro)->esquerda = aux_2->esquerda;
                    }
                }
                free(aux_2);
                aux_2 = NULL;
            }
        }
        else {
            if (strcmp(nome, (*ponteiro)->nome) < 0) {
                excluir(&((*ponteiro)->esquerda), nome);
            }
            else {
                excluir(&((*ponteiro)->direita), nome);
            }
        }
    }
    else {
        printf("\nDiret�rio n�o encontrado!\n");
    } 
}
int main() {
    setlocale (LC_ALL, "");
    Pont_arvore raiz = NULL;
    int tamanho, opcao;
    char nome[40], data[15];

    
    do {
        printf("\n---------------------------------------");
        printf("\n                 MENU                  ");
        printf("\n---------------------------------------\n");
        printf("\n1- INSERIR DADOS DO DIRET�RIO NA �RVORE\n");
        printf("2- CONSULTAR OS DADOS DE UM DIRET�RIO\n");
        printf("3- EXIBIR DADOS DE TODOS OS DIRET�RIOS\n");
        printf("4- REMOVER UM DIRET�RIO\n");
        printf("5- SAIR\n");
        printf("\n\nDigite a sua op��o: ");
        scanf("%d",&opcao);
        switch (opcao) {
            case 1:
                printf("\nDigite o nome do diret�rio: ");
                scanf("%s",nome);
                printf("\nDigite a data de cria��o do diret�rio: ");
                scanf("%s",data); 
                printf("\nDigite o tamanho do diret�rio (em Bytes): ");
                scanf("%d",&tamanho);
                inserir(&raiz,nome,data,tamanho);
                break;
            case 2:
                if (vazia(raiz)) {
                    printf("\n�rvore vazia.\n");
                }
                else {
                    printf("\nDigite o nome do diret�rio que quer buscar: ");
                    scanf("%s", nome);
                    consultar_dados(raiz, nome);
                }
                break;
            case 3:
                if (vazia(raiz)) {
                    printf("\n�rvore vazia!\n");
                }
                else {
                    exibir_dados(raiz);
                }
                break;
            case 4:
                if (vazia(raiz)) {
                    printf("\n�rvore vazia!\n");
                }
                else {
                    printf("\nDigite o nome do diret�rio que quer excluir: ");
                    scanf("%s", nome);
                    excluir(&raiz, nome);
                }
                break;
        }
    } while (opcao!=5);
    printf("\n              Saindo.....");
    printf("\n---------------------------------------");
    printf("\n            VOLTE SEMPRE               ");
    printf("\n---------------------------------------\n");
    return 0;
}