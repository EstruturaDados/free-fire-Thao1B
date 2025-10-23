#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// =============================================================================
// DEFINIÇÃO DA ESTRUTURA DE DADOS (STRUCT)
// =============================================================================
// Representa um único item que pode ser armazenado na mochila do jogador.
typedef struct {
    char nome[30];      // Nome do item (ex: "M4A1", "Pilha", "Bandagem")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;     // Quantidade do item (ex: 1, 30, 5)
} Item;

// Capacidade máxima da mochila, conforme o requisito.
#define MAX_ITENS 10

// Variável global para armazenar o inventário (mochila) e controlar o número de itens.
Item mochila[MAX_ITENS];
int numItens = 0; // Contador de itens atualmente registrados na mochila.

// =============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// =============================================================================
void limparBuffer();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// =============================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// =============================================================================
int main() {
    int opcao;
    // Inicializa a mochila com a quantidade 0 (embora o contador 'numItens' já faça isso,
    // esta é uma prática que garante a inicialização).
    for (int i = 0; i < MAX_ITENS; i++) {
        mochila[i].quantidade = 0;
    }

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        
        // Leitura da opção, com verificação básica de erro de entrada
        if (scanf("%d", &opcao) != 1) {
            limparBuffer(); // Limpa o buffer em caso de entrada não numérica
            opcao = 0;      // Define uma opção inválida para forçar a repetição do loop
            continue;
        }
        limparBuffer(); // Limpa o buffer após a leitura de um número

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                buscarItem();
                break;
            case 4:
                listarItens();
                break;
            case 5:
                printf("\nEncerrando o sistema de inventario. Boa sorte na sua coleta de loot!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida. Tente novamente.\n");
        }
        
        // Garante o desempenho (resposta rápida) ao pausar brevemente após a operação.
        // Em sistemas reais, a resposta é instantânea, mas aqui simula uma pequena pausa para a UX.
        if (opcao != 5) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Aguarda o jogador pressionar ENTER
        }

    } while (opcao != 5);

    return 0;
}

// =============================================================================
// FUNÇÕES AUXILIARES E DE OPERAÇÃO
// =============================================================================

/**
 * @brief Limpa o buffer de entrada (stdin) para evitar problemas com fgets() e scanf().
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Exibe o menu principal de opções para o jogador.
 */
void exibirMenu() {
    system("clear || cls"); // Comando para limpar a tela (funciona em Linux/Mac e Windows)
    printf("==============================================\n");
    printf("       MOCHILA DE LOOT INICIAL (Cap. %d)      \n", MAX_ITENS);
    printf("==============================================\n");
    printf("1. Cadastrar Novo Item\n");
    printf("2. Remover Item (Pelo Nome)\n");
    printf("3. Buscar Item (Pelo Nome)\n");
    printf("4. Listar Todo o Inventario\n");
    printf("5. Sair do Sistema\n");
    printf("----------------------------------------------\n");
    listarItens(); // Lista os itens após o menu para dar feedback imediato
    printf("----------------------------------------------\n");
}

/**
 * @brief Insere um novo item na mochila se houver espaço.
 */
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n[ALERTA] A mochila esta cheia! Nao e possivel adicionar mais itens (Limite: %d).\n", MAX_ITENS);
        return;
    }

    Item novoItem;
    
    // Leitura cuidadosa das strings (nome e tipo)
    printf("\n--- CADASTRO DE ITEM ---\n");
    printf("Nome do Item (max 29 caracteres): ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    // Remove o caractere de nova linha ('\n') que fgets() armazena
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; 

    printf("Tipo do Item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    // Leitura da quantidade
    printf("Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade <= 0) {
        printf("[ERRO] Quantidade invalida ou negativa. Item nao cadastrado.\n");
        limparBuffer();
        return;
    }
    limparBuffer(); // Limpa o buffer após o scanf de int

    // Adiciona o item ao vetor e incrementa o contador
    mochila[numItens] = novoItem;
    numItens++;
    printf("\n[SUCESSO] O item '%s' foi adicionado a mochila!\n", novoItem.nome);
}

/**
 * @brief Remove um item da mochila com base no seu nome.
 */
void removerItem() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia. Nada a remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- REMOCAO DE ITEM ---\n");
    printf("Digite o NOME exato do item a ser removido: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; 

    int indiceRemocao = -1;

    // 1. Busca sequencial pelo nome (case-sensitive)
    for (int i = 0; i < numItens; i++) {
        // strcmp retorna 0 se as strings forem iguais
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceRemocao = i;
            break; // Item encontrado!
        }
    }

    if (indiceRemocao != -1) {
        // 2. Desloca os itens seguintes para preencher a lacuna (simulando remoção em vetor)
        for (int i = indiceRemocao; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        numItens--; // Decrementa o contador de itens
        printf("\n[SUCESSO] O item '%s' foi removido da mochila.\n", nomeBusca);
    } else {
        printf("\n[ATENCAO] Item com nome '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

/**
 * @brief Lista todos os itens atualmente registrados na mochila.
 */
void listarItens() {
    printf("\n--- ITENS ATUAIS (%d/%d) ---\n", numItens, MAX_ITENS);
    
    if (numItens == 0) {
        printf("Mochila VAZIA. Hora de explorar e coletar recursos!\n");
        return;
    }

    printf("%-4s | %-30s | %-20s | %-10s\n", "ID", "NOME", "TIPO", "QTD");
    printf("----------------------------------------------------------------------\n");
    
    // Percorre o vetor sequencialmente
    for (int i = 0; i < numItens; i++) {
        printf("%-4d | %-30s | %-20s | %-10d\n", 
               i + 1,                      // ID (começa em 1)
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
}

/**
 * @brief Realiza uma busca sequencial por um item baseado no nome e exibe seus dados.
 */
void buscarItem() {
    if (numItens == 0) {
        printf("\nA mochila esta vazia. Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- BUSCA DE ITEM ---\n");
    printf("Digite o NOME do item a ser localizado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; 

    int encontrado = 0;

    // Implementação da busca sequencial
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[SUCESSO] Item encontrado no indice %d:\n", i + 1);
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break; // Para a busca assim que encontrar o item
        }
    }

    if (!encontrado) {
        printf("\n[ATENCAO] Item com nome '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}
