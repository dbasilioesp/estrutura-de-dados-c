#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct
{
    char nome[30];
    int idade;
} Pessoa;

typedef struct
{
    Pessoa dados[MAX];
    int inicio, fim;
} Fila;

typedef struct
{
    Pessoa dados[MAX];
    int topo;
} Pilha;

void inicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
}

void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

void adicionarFila(Fila *f, Pessoa p)
{
    if (f->fim < MAX)
    {
        f->dados[f->fim++] = p;
    }
}

Pessoa removerFila(Fila *f)
{
    return f->dados[f->inicio++];
}

void adicionarPilha(Pilha *p, Pessoa pes)
{
    if (p->topo < MAX - 1)
    {
        p->dados[++p->topo] = pes;
    }
}

Pessoa removerPilha(Pilha *p)
{
    return p->dados[p->topo--];
}

void exibirFila(Fila f)
{
    for (int i = f.inicio; i < f.fim; i++)
    {
        printf("Nome: %s | Idade: %d\n", f.dados[i].nome, f.dados[i].idade);
    }
}

int main()
{
    Fila filaOriginal, filaInvertida;
    Pilha auxiliar;

    inicializarFila(&filaOriginal);
    inicializarFila(&filaInvertida);
    inicializarPilha(&auxiliar);

    Pessoa pessoas[] = {
        {"Carlos", 45}, {"Joana", 62}, {"Lucas", 30}, {"Maria", 75}};

    for (int i = 0; i < 4; i++)
    {
        adicionarFila(&filaOriginal, pessoas[i]);
    }

    while (filaOriginal.inicio < filaOriginal.fim)
    {
        adicionarPilha(&auxiliar, removerFila(&filaOriginal));
    }

    while (auxiliar.topo >= 0)
    {
        adicionarFila(&filaInvertida, removerPilha(&auxiliar));
    }

    printf("Fila invertida:\n");
    exibirFila(filaInvertida);

    return 0;
}