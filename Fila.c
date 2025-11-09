#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 3

typedef struct
{
    char nome[30];
    int idade;
} Elemento;

typedef struct
{
    Elemento itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inserirFila(Fila *f, Elemento e);
int filaCheia(Fila *f);
Elemento retirarFila(Fila *f);
void inicializarFila(Fila *f);
Elemento espiar(Fila *f);
void mostrarFila(Fila *f);

int main()
{
    Fila fila;
    inicializarFila(&fila);

    Elemento e;
    strcpy(e.nome, "Teste");

    Elemento e2;
    strcpy(e2.nome, "Teste2");

    Elemento e3;
    strcpy(e3.nome, "Teste3");

    inserirFila(&fila, e);
    inserirFila(&fila, e2);
    inserirFila(&fila, e3);
    retirarFila(&fila);
    retirarFila(&fila);

    // printf("Espiar: %s", espiar(&fila));
    mostrarFila(&fila);

    return 0;
}

int filaCheia(Fila *f)
{
    return f->total == MAX;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

void inserirFila(Fila *f, Elemento e)
{
    if (filaCheia(f))
        return;
    f->itens[f->fim] = e;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

Elemento retirarFila(Fila *f)
{
    Elemento vazio = {-1};
    if (filaVazia(f))
        return vazio;
    Elemento e = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return e;
}

Elemento espiar(Fila *f)
{
    Elemento vazio = {-1};
    if (filaVazia(f))
        return vazio;
    return f->itens[f->inicio];
}

void inicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void mostrarFila(Fila *f)
{
    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
    {
        printf("[%s]", f->itens[idx].nome);
    }
    printf("\n");
}