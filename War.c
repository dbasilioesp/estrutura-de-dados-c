#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 50
#define MAX_COLOR 10
#define MAX_TERRITORIOS 5

typedef struct  {
    char nome[MAX_NOME];
    char cor[MAX_COLOR];
    int num_tropas;
} Territorio;

int opcao;

void limparBufferEntrada();
void digiteParaContinuar();
void alocarMapa(int* maxTerritorios, Territorio* territorios);
void inicializarTerritorios(int* maxTerritorios, Territorio* territorios);
void exibirMapa(int* maxTerritorios, Territorio* territorios);
void faseDeAtaque(int* atacante, int* defensor, bool* faseAtaque, int* maxTerritorios);
void simularAtaque(int* atacante, int* defensor, Territorio* territorios);
void verificarVitoria(int* maxTerritorios, bool* faseAtaque, int* vitorioso, Territorio* territorios);

// --- Função Principal (main) ---
int main() {
    srand(time(0));

    Territorio* territorios;
    int maxTerritorios;
    int atacante, defensor;
    bool faseAtaque = true;
    int vitorioso = -1;

    printf("============================================================================\n");
    printf("PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO\n");
    printf("============================================================================\n");

    alocarMapa(&maxTerritorios, territorios);
    inicializarTerritorios(&maxTerritorios, territorios);
    
    while(faseAtaque) {
        exibirMapa(&maxTerritorios, territorios);
        faseDeAtaque(&atacante, &defensor, &faseAtaque, &maxTerritorios);
        
        if (atacante != 0) {
            simularAtaque(&atacante, &defensor, territorios);
            verificarVitoria(&maxTerritorios, &faseAtaque, &vitorioso, territorios);
        }
    };

    if (atacante == 0) {
        printf("\n\nJogo encerrado e memoria liberada. Até a proxima!\n");
    }
    
    if (vitorioso != -1) {
        printf("\n\n*************  O GRANDE VENCEDOR %s  *************\n\n", territorios[vitorioso].nome);
    }

    free(territorios);
    return 0;
}

void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void digiteParaContinuar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    limparBufferEntrada();
}

void alocarMapa(int* maxTerritorios, Territorio* territorios) {
    printf("Digite quantos territorios no mapa: ");
    scanf("%d", maxTerritorios);
    limparBufferEntrada();

    territorios = (Territorio*)malloc((*maxTerritorios) * sizeof(Territorio));
}

void inicializarTerritorios(int* maxTerritorios, Territorio* territorios) {
    for (int i = 0; i < *maxTerritorios; i++) {
        printf("\n----- Cadastro Territorio %d ------\n\n", i + 1);

        printf("Digite o nome: ");
        fgets(territorios[i].nome, MAX_NOME, stdin);

        printf("Digite a cor: ");
        fgets(territorios[i].cor, MAX_COLOR, stdin);

        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        printf("Digite quantidade de tropas: ");
        scanf("%d", &territorios[i].num_tropas);
        limparBufferEntrada();
    }

    printf("\n\nTERRITORIOS CADASTRADOS.\n\n");
}

void exibirMapa(int* maxTerritorios, Territorio* territorios) {
    printf("=============================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=============================\n\n");

    for (int i = 0; i < *maxTerritorios; i++) {
        printf("%d. %s (%s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].num_tropas);
    }
}

void faseDeAtaque(int* atacante, int* defensor, bool* faseAtaque, int* maxTerritorios) {
    printf("\n");
    printf("--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", *maxTerritorios);
    scanf("%d", atacante);
    limparBufferEntrada();

    if ((*atacante) == 0) {
        *faseAtaque = false;
        return;
    }

    printf("Escolha o territorio defensor (1 a %d): ", *maxTerritorios);
    scanf("%d", defensor);
    limparBufferEntrada();
}

void simularAtaque(int* atacante, int* defensor, Territorio* territorios) {
    int ataque = rand() % 20;
    int defesa = rand() % 20;
    int atacanteI = *atacante - 1;
    int defensorI = *defensor - 1;

    printf("\n");
    printf("--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d \n", territorios[atacanteI].nome, ataque);
    printf("O defensor %s rolou um dado e tirou: %d \n", territorios[defensorI].nome, defesa);

    if (ataque >= defesa) {
        territorios[defensorI].num_tropas = territorios[defensorI].num_tropas - 1;
        printf("VITORIA DO ATAQUE! O defensor perdeu uma 1 tropa.\n");

        if (territorios[defensorI].num_tropas == 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s\n", territorios[defensorI].nome, territorios[atacanteI].cor);
        }
    } else {
        printf("ATAQUE FALHOU!\n");
    }

    digiteParaContinuar();
}

void verificarVitoria(int* maxTerritorios, bool* faseAtaque, int* vitorioso, Territorio* territorios) {
    int abatidos = 0;

    for (int i = 0; i < *maxTerritorios; i++) {
        if (territorios[i].num_tropas == 0) {
            abatidos += 1;
        }
    }

    if (abatidos == *maxTerritorios - 1) {
        *faseAtaque = false;

        for (int i = 0; i < *maxTerritorios; i++) {
            if (territorios[i].num_tropas > 0) {
                *vitorioso = i;
            }
        }
    }
}


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
