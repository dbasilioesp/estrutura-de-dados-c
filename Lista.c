#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct No
{
    int dado;
    struct No *proximo;
    struct No *anterior;
};

void listarSequencial(int vetor[], int tamanho);
void inserirNoInicio(struct No **inicio, int valor);
void removerDoInicio(struct No **inicio);
void listarEncadeado(struct No *inicio);
int buscaLinearSequencial(int lista[], int tamanho, int valor);
int buscaLinearEncadeada(struct No *inicio, int valor);
int buscaBinariaSequencial(int vetor[], int tamanho, int valor);
int buscaBinariaRecursivaAux(int vetor[], int tamanho, int valor);
int buscaBinariaRecursiva(int vetor[], int inicio, int fim, int valor, int iteracoes);
void trocar(int *a, int *b);
void bubbleSort(int vetor[], int tamanho);
void insertionSort(int vetor[], int tamanho);
void selectionSort(int vetor[], int tamanho);

int main()
{
    // LISTAS SEQUENCIAIS

    // int numeros[5] = {10, 20, 30, 40, 50};
    int *numeros = (int *)malloc(3 * sizeof(int));

    numeros[0] = 30;
    numeros[1] = 20;
    numeros[2] = 10;

    numeros = (int *)realloc(numeros, 5 * sizeof(int));

    numeros[3] = 50;
    numeros[4] = 40;

    // bubbleSort(numeros, 5);
    // insertionSort(numeros, 5);
    selectionSort(numeros, 5);

    // printf("Busca sequencial: %d\n", buscaLinearSequencial(numeros, 5, 50));
    // printf("Busca binaria sequencial: %d\n", buscaBinariaSequencial(numeros, 5, 50));
    // printf("Busca binaria sequencial recursiva: %d\n", buscaBinariaRecursivaAux(numeros, 5, 50));

    listarSequencial(numeros, 5);

    // LISTAS ENCADEADAS

    struct No *primeiro = (struct No *)malloc(sizeof(struct No));
    struct No *segundo = (struct No *)malloc(sizeof(struct No));
    struct No *terceiro = (struct No *)malloc(sizeof(struct No));

    primeiro->dado = 4;
    primeiro->proximo = segundo;
    segundo->dado = 5;
    segundo->proximo = terceiro;
    terceiro->dado = 6;
    terceiro->proximo = NULL;

    inserirNoInicio(&primeiro, 3);
    listarEncadeado(primeiro);
    removerDoInicio(&primeiro);
    listarEncadeado(primeiro);

    int indexEn = buscaLinearEncadeada(primeiro, 6);
    printf("Busca encadeada: %d\n", indexEn);
}

void listarSequencial(int vetor[], int tamanho)
{
    printf("Lista (S): ");

    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }

    printf("\n");
}

void inserirNoInicio(struct No **inicio, int valor)
{
    struct No *novo = (struct No *)malloc(sizeof(struct No));
    novo->dado = valor;
    novo->proximo = *inicio;
    *inicio = novo;
}

void removerDoInicio(struct No **inicio)
{
    if (*inicio != NULL)
    {
        struct No *temp = *inicio;
        *inicio = (*inicio)->proximo;
        free(temp);
    }
}

void listarEncadeado(struct No *inicio)
{
    struct No *atual = inicio;

    printf("Lista (E): ");
    while (atual != NULL)
    {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

int buscaLinearSequencial(int lista[], int tamanho, int valor)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (lista[i] == valor)
        {
            return i; // Retorna o índice onde encontrou o valor
        }
    }
    return -1; // Retorna -1 se não encontrou
}

int buscaLinearEncadeada(struct No *inicio, int valor)
{
    int pos = 0;
    struct No *atual = inicio;
    while (atual != NULL)
    {
        if (atual->dado == valor)
        {
            return pos;
        }

        atual = atual->proximo;
        pos++;
    }

    return -1;
}

int buscaBinariaSequencial(int vetor[], int tamanho, int valor)
{
    int iteracoes = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        if (vetor[meio] == valor)
        {
            printf("Iterações: %d\n", iteracoes);
            return meio;
        }
        else if (vetor[meio] < valor)
        {

            inicio = meio + 1;
        }
        else
        {

            fim = meio - 1;
        }

        iteracoes++;
    }
}

int buscaBinariaRecursivaAux(int vetor[], int tamanho, int valor)
{
    return buscaBinariaRecursiva(vetor, 0, tamanho, valor, 0);
}

int buscaBinariaRecursiva(int vetor[], int inicio, int fim, int valor, int iteracoes)
{
    if (inicio > fim)
        return -1;

    int meio = (inicio + fim) / 2;

    if (vetor[meio] == valor)
    {
        printf("Iterações: %d\n", iteracoes);
        return meio;
    }
    else if (vetor[meio] < valor)
        return buscaBinariaRecursiva(vetor, meio + 1, fim, valor, iteracoes + 1);
    else
        return buscaBinariaRecursiva(vetor, inicio, meio - 1, valor, iteracoes + 1);
}

void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - 1 - i; j++)
        {
            if (vetor[j] > vetor[j + 1])
            {
                trocar(&vetor[j], &vetor[j + 1]);
            }
        }
    }
}

void insertionSort(int vetor[], int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        int ant = i - 1;
        int valor2 = vetor[i];

        // Move os elementos maiores que a valor2 uma posição à frente
        while (ant >= 0 && vetor[ant] > valor2)
        {
            vetor[ant + 1] = vetor[ant];
            ant--;
        }

        vetor[ant + 1] = valor2;
    }
}

void selectionSort(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        int indiceMenor = i;

        for (int j = i + 1; j < tamanho; j++)
        {
            if (vetor[j] < vetor[indiceMenor])
            {
                indiceMenor = j;
            }
        }

        if (indiceMenor != i)
        {
            trocar(&vetor[i], &vetor[indiceMenor]);
        }
    }
}