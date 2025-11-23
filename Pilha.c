#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5

typedef struct
{
    int id;
    int valor;
} Elemento;

typedef struct
{
    int topo;
    Elemento itens[MAX];
} Pilha;

void inicializarPilha(Pilha *p);
void push(Pilha *p, Elemento e);
void pop(Pilha *p, Elemento *e);
void peek(Pilha *p, Elemento *e);
void mostrarPilha(Pilha *p);

int main()
{
    Pilha p;
    inicializarPilha(&p);

    Elemento a = {1, 20};
    push(&p, a);

    mostrarPilha(&p);

    return 0;
}

void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

int pilhaCheia(Pilha *p)
{
    return p->topo == MAX - 1;
}

void push(Pilha *p, Elemento e)
{
    if (pilhaCheia(p))
    {
        printf("Erro: pilha cheia. Não é possível inserir.\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = e;
}

void pop(Pilha *p, Elemento *e)
{
    if (pilhaVazia(p))
    {
        printf("Erro: pilha vazia. Não há elementos para remover.");
        e->valor = -1;
        return;
    }

    *e = p->itens[p->topo];
    p->topo--;
}

void peek(Pilha *p, Elemento *e)
{
    if (pilhaVazia(p))
    {
        printf("Erro: pilha vazia. Não há elementos no topo.\n");
        e->valor = -1;
        return;
    }

    *e = p->itens[p->topo];
}

void liberarPilha(Pilha *p)
{
    p->topo = -1;
}

void mostrarPilha(Pilha *p)
{
    printf("Pilha (topo -> base):\n");
    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%d, %d]\n", p->itens[i].id, p->itens[i].valor);
    }
    printf("\n");
}

// void liberarPilhaDinamica(Pilha *p)
// {
//     while(p->topo != NULL)
//     {
//         No *remover = p->topo;
//         p->topo = p->topo->prox;
//         free(remover);
//     }
// }