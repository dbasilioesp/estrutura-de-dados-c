#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct No
{
    char valor[50];
    struct No *esquerda;
    struct No *direita;
};

int altura(struct No *raiz)
{
    if (raiz == NULL)
        return 0;

    int altEsquerda = altura(raiz->esquerda);
    int altDireita = altura(raiz->direita);
    return 1 + (altEsquerda > altDireita ? altEsquerda : altDireita);
}

int profundidade(struct No *raiz, struct No *alvo, int nivel)
{
    if (raiz == NULL)
        return -1;
    if (raiz == alvo)
        return nivel;
    int esq = profundidade(raiz->esquerda, alvo, nivel + 1);
    if (esq == -1)
        return esq;

    return profundidade(raiz->direita, alvo, nivel + 1);
}

void preOrdem(struct No *raiz)
{
    if (raiz != NULL)
    {
        printf("%s ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(struct No *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esquerda);
        printf("%s ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(struct No *raiz)
{
    if (raiz != NULL)
    {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%s ", raiz->valor);
    }
}

struct No *gerarNo(int *inc)
{
    int i = *inc;

    struct No *novo = (struct No *)malloc(sizeof(struct No));
    novo->esquerda = NULL;
    novo->direita = NULL;

    if (i == 0)
        strcpy(novo->valor, "1");
    if (i == 1)
        strcpy(novo->valor, "2");
    if (i == 2)
        strcpy(novo->valor, "3");
    if (i == 3)
        strcpy(novo->valor, "4");
    if (i == 4)
        strcpy(novo->valor, "5");
    if (i == 5)
        strcpy(novo->valor, "6");
    if (i == 6)
        strcpy(novo->valor, "7");

    *inc += 1;

    return novo;
}

void liberar(struct No *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

int main()
{
    int inc = 0;

    struct No *raiz = gerarNo(&inc);
    raiz->esquerda = gerarNo(&inc);
    raiz->direita = gerarNo(&inc);

    raiz->esquerda->esquerda = gerarNo(&inc);
    raiz->esquerda->direita = gerarNo(&inc);

    raiz->direita->esquerda = gerarNo(&inc);
    raiz->direita->direita = gerarNo(&inc);

    preOrdem(raiz);
    printf("\n");
    emOrdem(raiz);
    printf("\n");
    posOrdem(raiz);

    liberar(raiz);

    return 0;
}