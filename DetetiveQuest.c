#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

#define MAX_NOME 30

struct Sala
{
    char nome[MAX_NOME];
    struct Sala *esquerda;
    struct Sala *direita;
};

struct Sala *criarSala(char *nome)
{
    struct Sala *sala = (struct Sala *)malloc(sizeof(struct Sala));
    strcpy(sala->nome, nome);
    sala->esquerda = NULL;
    sala->direita = NULL;

    return sala;
}

void conectarSalas(struct Sala *raiz, struct Sala *esq, struct Sala *dir)
{
    raiz->esquerda = esq;
    raiz->direita = dir;
}

void mostrarSalaAtual(struct Sala **atual)
{
    printf("\n");
    printf(">>> Sala Atual: %s\n", (*atual)->nome);
}

void explorarSalas(char direcao, struct Sala **atual);

void menuPrincipal(char *opcao, struct Sala **atual);

int main()
{
    struct Sala *entrada = criarSala("Entrada");
    struct Sala *biblioteca = criarSala("Biblioteca");
    struct Sala *salaEstar = criarSala("Sala de Estar");
    struct Sala *cozinha = criarSala("Cozinha");
    struct Sala *sotao = criarSala("Sotão");
    struct Sala *garagem = criarSala("Garagem");
    struct Sala *banheiro = criarSala("Banheiro");

    conectarSalas(entrada, biblioteca, salaEstar);
    conectarSalas(biblioteca, sotao, garagem);
    conectarSalas(salaEstar, cozinha, banheiro);

    struct Sala **atual = &entrada;

    char opcao;

    do
    {
        mostrarSalaAtual(atual);

        menuPrincipal(&opcao, atual);

        explorarSalas(opcao, atual);

    } while (opcao != 's');

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

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

void menuPrincipal(char *opcao, struct Sala **atual)
{
    limparTela();
    printf("Escolha próxima caminho:\n");

    if ((*atual)->esquerda != NULL)
        printf("(e). %s\n", (*atual)->esquerda->nome);

    if ((*atual)->direita != NULL)
        printf("(d). %s\n", (*atual)->direita->nome);

    printf("(s). Sair\n\n");

    printf("Digite a opção: ");
    scanf("%c", opcao);

    limparBufferEntrada();
    // limparTela();
}

void explorarSalas(char direcao, struct Sala **atual)
{
    if (direcao == 'e')
    {
        *atual = (*atual)->esquerda;
    }

    if (direcao == 'd')
    {
        *atual = (*atual)->direita;
    }
}
