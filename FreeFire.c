#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITEMS 10
#define MAX_NOME_LENGTH 20
#define MAX_TIPO_LENGTH 20

typedef struct
{
    char nome[MAX_NOME_LENGTH];
    char tipo[MAX_TIPO_LENGTH];
    int quantidade;
    int prioridade;
} Item;

void menuPrincipal(int *opcao);
void limparTela();
void limparBufferEntrada();
void digiteParaContinuar();
void inserirItem(Item mochila[], int *quantidade);
void listarItens(Item mochila[], int *quantidade);
void opcaoRemoverItem(Item *mochila, int *quantidade);
// void removerItem(Item *mochila, int *quantidade, char *procurado[MAX_NOME_LENGTH]);
void removerItem(Item mochila[], int *quantidade, char *procurado);
int buscaPorNome(Item mochila[], int quantidade, char *valor);
int buscaBinariaPorNome(Item mochila[], int tamanho, char *valor);
void opcaoBuscarPorNome(Item mochila[], int *quantidade, bool binaria);
void opcaoOrdenacao(Item mochila[], int *quantidade);
void ordenarPorNomeBubble(Item mochila[], int tamanho);
void ordenarPorTipoBubble(Item mochila[], int tamanho);
void ordenarPorPrioridadeBubble(Item mochila[], int tamanho);
void ordenarPorNomeInsertionSort(Item mochila[], int tamanho);
void ordenarPorTipoInsertionSort(Item mochila[], int tamanho);
void ordenarPorPrioridadeInsertionSort(Item mochila[], int tamanho);
void listarItens(Item mochila[], int *quantidade);

int main()
{
    int opcaoPrincipal = 0;
    // int numItens = 0;
    // Item *mochila = (Item *)malloc((MAX_ITEMS) * sizeof(Item));

    int numItens = 3;
    Item mochila[MAX_ITEMS] = {
        {"Soo", "Arma", 1, 3},
        {"Boo", "Escudo", 1, 2},
        {"Doo", "Cura", 1, 4},
    };

    do
    {
        menuPrincipal(&opcaoPrincipal);
        limparTela();

        switch (opcaoPrincipal)
        {
        case 1:
            inserirItem(mochila, &numItens);
            break;
        case 2:
            opcaoRemoverItem(mochila, &numItens);
            break;
        case 3:
            listarItens(mochila, &numItens);
            break;
        case 4:
            opcaoBuscarPorNome(mochila, &numItens, false);
            break;
        case 5:
            opcaoOrdenacao(mochila, &numItens);
            break;
        case 6:
            opcaoBuscarPorNome(mochila, &numItens, true);
            break;
        default:
            break;
        }
    } while (opcaoPrincipal != 0);

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

void limparTela()
{
    printf("\n\n");
    printf("====================");
    printf("\n\n");
}

void menuPrincipal(int *opcao)
{
    limparTela();
    printf("Menu principal com opções:\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Ordenar items\n");
    printf("6. Busca Binaria por nome\n");
    printf("0. Sair\n\n");

    printf("Digite a opção: ");
    scanf("%d", opcao);
    limparBufferEntrada();
}

void menuOrdenacao(int *opcao)
{
    limparTela();
    printf("Opções de ordenação:\n");
    printf("1. Ordenar por nome (Bubble)\n");
    printf("2. Ordenar por tipo (Bubble)\n");
    printf("3. Ordenar por prioridade (Bubble)\n");
    printf("4. Ordenar por nome (InsertionSort)\n");
    printf("5. Ordenar por tipo (InsertionSort)\n");
    printf("6. Ordenar por prioridade (InsertionSort)\n");
    printf("0. Voltar\n\n");

    printf("Digite a opção: ");
    scanf("%d", opcao);
    limparBufferEntrada();
}

void opcaoOrdenacao(Item *mochila, int *quantidade)
{
    int opcaoOrdenacao = 0;

    do
    {
        menuOrdenacao(&opcaoOrdenacao);

        switch (opcaoOrdenacao)
        {
        case 1:
            ordenarPorNomeBubble(mochila, *quantidade);
            break;
        case 2:
            ordenarPorTipoBubble(mochila, *quantidade);
            break;
        case 3:
            ordenarPorPrioridadeBubble(mochila, *quantidade);
            break;
        case 4:
            ordenarPorNomeInsertionSort(mochila, *quantidade);
            break;
        case 5:
            ordenarPorTipoInsertionSort(mochila, *quantidade);
            break;
        case 6:
            ordenarPorPrioridadeInsertionSort(mochila, *quantidade);
            break;
        default:
            break;
        }

        if (opcaoOrdenacao != 0)
        {
            printf(">>> Ordenado!\n\n");
            listarItens(mochila, quantidade);
        }

    } while (opcaoOrdenacao != 0);
}

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void digiteParaContinuar()
{
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n')
        ;
}

void inserirItem(Item mochila[], int *index)
{
    if (*index >= MAX_ITEMS)
    {
        printf("----- Não há espaço na mochila! ------\n");
        return;
    }

    printf(">>> Adicionando novo item\n");

    printf("Nome: ");
    fgets(mochila[*index].nome, MAX_NOME_LENGTH, stdin);

    printf("Tipo: ");
    fgets(mochila[*index].tipo, MAX_NOME_LENGTH, stdin);

    printf("Quantidade: ");
    scanf("%d", &mochila[*index].quantidade);

    printf("Prioridade: ");
    scanf("%d", &mochila[*index].prioridade);

    mochila[*index].nome[strcspn(mochila[*index].nome, "\n")] = '\0';
    mochila[*index].tipo[strcspn(mochila[*index].tipo, "\n")] = '\0';

    *index = *index + 1;
}

void printItem(Item *item, int pos)
{
    printf("%d - %s [%s] (Qt. %d) (Prioridade %d)\n", pos, item->nome, item->tipo, item->quantidade, item->prioridade);
}

void listarItens(Item mochila[], int *quantidade)
{
    printf(">>> Lista de itens da mochila:\n");

    for (int i = 0; i < *quantidade; i++)
    {
        printItem(&mochila[i], i + 1);
    }

    digiteParaContinuar();
}

void informeNome(char *procurado)
{
    printf("Informe o nome do item: ");
    fgets(procurado, MAX_NOME_LENGTH, stdin);
    procurado[strcspn(procurado, "\n")] = '\0';
}

void opcaoRemoverItem(Item mochila[], int *quantidade)
{
    printf(">>> Removendo item da mochila:\n");

    int pos;
    char procurado[MAX_NOME_LENGTH];
    informeNome(procurado);

    removerItem(mochila, quantidade, procurado);

    printf(">>> Item removido!");
    digiteParaContinuar();
}

void removerItem(Item mochila[], int *quantidade, char *procurado)
{
    int pos = buscaPorNome(mochila, *quantidade, procurado);

    if (pos == -1)
    {
        printf(">>> Item não encontrado! \n");
        return;
    }

    for (int i = pos; i < *quantidade; i++)
    {
        strcpy(mochila[i].nome, mochila[i + 1].nome);
        strcpy(mochila[i].tipo, mochila[i + 1].tipo);
        mochila[i].quantidade = mochila[i + 1].quantidade;
    }

    *quantidade -= 1;
}

void opcaoBuscarPorNome(Item mochila[], int *quantidade, bool binaria)
{
    int pos;
    char procurado[MAX_NOME_LENGTH];
    informeNome(procurado);

    if (binaria)
    {
        pos = buscaPorNome(mochila, *quantidade, procurado);
    }
    else
    {
        pos = buscaBinariaPorNome(mochila, *quantidade, procurado);
    }

    limparTela();

    if (pos >= 0)
    {
        printf(">>>> ITEM ENCONTRADO!");
        printItem(&mochila[pos], pos + 1);
    }
    else
    {
        printf(">>>> Não foi encontrdo o item. <<<<");
    }

    digiteParaContinuar();
}

int buscaPorNome(Item mochila[], int quantidade, char *valor)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(mochila[i].nome, valor) == 0)
        {
            return i; // Retorna o índice onde encontrou o valor
        }
    }
    return -1; // Retorna -1 se não encontrou
}

int buscaBinariaPorNome(Item mochila[], int tamanho, char *valor)
{
    int iteracoes = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, valor);

        if (cmp == 0)
        {
            printf("Iterações: %d\n", iteracoes);
            return meio;
        }
        else if (cmp < valor)
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

void trocarItem(Item *a, Item *b)
{
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarPorNomeBubble(Item mochila[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0)
            {
                trocarItem(&mochila[j], &mochila[j + 1]);
            }
        }
    }
}

void ordenarPorTipoBubble(Item mochila[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if (strcmp(mochila[j].tipo, mochila[j + 1].tipo) > 0)
            {
                trocarItem(&mochila[j], &mochila[j + 1]);
            }
        }
    }
}

void ordenarPorPrioridadeBubble(Item mochila[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if (mochila[j].prioridade > mochila[j + 1].prioridade)
            {
                trocarItem(&mochila[j], &mochila[j + 1]);
            }
        }
    }
}

void ordenarPorNomeInsertionSort(Item mochila[], int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        int ant = i - 1;
        char valor2[MAX_NOME_LENGTH];
        Item temp = mochila[i];
        strcpy(valor2, mochila[i].nome);

        // Move os elementos maiores que a valor2 uma posição à frente
        while (ant >= 0 && strcmp(mochila[ant].nome, valor2) > 0)
        {
            mochila[ant + 1] = mochila[ant];
            ant--;
        }

        mochila[ant + 1] = temp;
    }
}

void ordenarPorTipoInsertionSort(Item mochila[], int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        int ant = i - 1;
        char valor2[MAX_NOME_LENGTH];
        Item temp = mochila[i];
        strcpy(valor2, mochila[i].tipo);

        // Move os elementos maiores que a valor2 uma posição à frente
        while (ant >= 0 && strcmp(mochila[ant].tipo, valor2) > 0)
        {
            mochila[ant + 1] = mochila[ant];
            ant--;
        }

        mochila[ant + 1] = temp;
    }
}

void ordenarPorPrioridadeInsertionSort(Item mochila[], int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        Item temp = mochila[i];
        int ant = i - 1;
        int valor2 = mochila[i].prioridade;

        // Move os elementos maiores que a valor2 uma posição à frente
        while (ant >= 0 && mochila[ant].prioridade > valor2)
        {
            mochila[ant + 1] = mochila[ant];
            ant--;
        }

        mochila[ant + 1] = temp;
    }
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// menuPrincipal():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.