#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX_PECAS 5
#define MAX_TIPO_PECAS 4

typedef enum
{
    L,
    I,
    O,
    T
} Tipo;

typedef struct
{
    int id;
    char tipo;
} Peca;

typedef struct
{
    Peca pecas[MAX_PECAS];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *f);
void inserirFila(Fila *f, Peca e);
Peca retirarFila(Fila *f);
Peca espiar(Fila *f);
void mostrarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca();

void menuPrincipal(int *opcao);
void opcaoAdicionarPeca(Fila *fila);
void opcaoJogarPeca(Fila *fila);

int main()
{
    srand(time(0));
    int opcaoPrincipal = 0;

    Fila fila;
    inicializarFila(&fila);

    mostrarFila(&fila);

    do
    {
        menuPrincipal(&opcaoPrincipal);

        switch (opcaoPrincipal)
        {
        case 1:
            opcaoJogarPeca(&fila);
            break;
        default:
            break;
        }
    } while (opcaoPrincipal != 0);

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

    return 0;
}

// INTERFACE

void digiteParaContinuar()
{
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n')
        ;
}

void limparTela()
{
    printf("\n");
    printf("====================");
    printf("\n\n");
}

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void menuPrincipal(int *opcao)
{
    limparTela();
    printf("Menu principal com opções:\n");
    printf("1. Jogar a peça\n");
    printf("0. Sair\n\n");

    printf("Digite a opção: ");
    scanf("%d", opcao);
    limparBufferEntrada();
    limparTela();
}

void opcaoAdicionarPeca(Fila *fila)
{

    if (filaCheia(fila))
    {
        printf("Fila está cheia, é preciso jogar uma peça!");
        return;
    }

    Peca peca;
    peca.id = 1;
    printf("Adicione um dos tipos de peças: [L] [O] [I] [T]\n");

    printf("Informe o nome do item: ");
    scanf("%c", &peca.tipo);
    limparBufferEntrada();
    inserirFila(fila, peca);

    printf("\n");
    mostrarFila(fila);

    digiteParaContinuar();
}

void opcaoJogarPeca(Fila *fila)
{
    if (filaVazia(fila))
    {
        printf("Fila está cheia, é preciso jogar uma peça!");
        digiteParaContinuar();
        return;
    }

    Peca peca = retirarFila(fila);

    printf("Peça jogada: %c\n\n", peca.tipo);

    Peca nova = gerarPeca();

    inserirFila(fila, nova);

    printf("Peça adicionada a fila: %c\n\n", nova.tipo);

    mostrarFila(fila);

    digiteParaContinuar();
}

// FILA

int filaCheia(Fila *f)
{
    return f->total == MAX_PECAS;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

Peca gerarPeca()
{
    Peca peca;

    peca.id = rand() % 10000;
    int rTipo = rand() % (MAX_TIPO_PECAS - 1);

    switch (rTipo)
    {
    case 0:
        peca.tipo = 'L';
        break;
    case 1:
        peca.tipo = 'I';
        break;
    case 2:
        peca.tipo = 'O';
        break;
    case 3:
        peca.tipo = 'T';
        break;
    }

    return peca;
}

void inicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;

    for (int i = 0; i < MAX_PECAS; i++)
    {
        inserirFila(f, gerarPeca());
    }
}

void inserirFila(Fila *f, Peca e)
{
    if (filaCheia(f))
        return;
    f->pecas[f->fim] = e;
    f->fim = (f->fim + 1) % MAX_PECAS;
    f->total++;
}

void mostrarFila(Fila *f)
{

    if (filaVazia(f))
    {
        printf(">>> Fila vazia!");
        return;
    }

    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_PECAS)
    {
        printf("[%c] ", f->pecas[idx].tipo);
    }
    printf("\n");
}

Peca retirarFila(Fila *f)
{
    Peca vazio = {-1};
    if (filaVazia(f))
        return vazio;
    Peca e = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PECAS;
    f->total--;
    return e;
}