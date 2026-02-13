#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constante para capacidade máxima da mochila
#define CAPACIDADE_MOCHILA 10

// Definição da struct Item para armazenar dados do item
typedef struct {
    char nome[30];      
    char tipo[20];     
    int quantidade;    
} Item;

// Variáveis globais para gerenciar a mochila
Item mochila[CAPACIDADE_MOCHILA];  
int totalItens = 0;                 

// Função para inserir um novo item na mochila
void inserirItem() {
    if (totalItens >= CAPACIDADE_MOCHILA) {
        printf("\n[Erro] Mochila cheia! Máximo de 10 itens atingido.\n");
        return;
    }

    printf("\n=== CADASTRAR NOVO ITEM ===\n");
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, sizeof(mochila[totalItens].nome), stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';

    printf("Tipo (Arma/Armadura/Munição/Cura): ");
    fgets(mochila[totalItens].tipo, sizeof(mochila[totalItens].tipo), stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    getchar(); // Limpar buffer do scanf

    if (mochila[totalItens].quantidade < 0) {
        printf("[Erro] Quantidade não pode ser negativa!\n");
        return;
    }

    totalItens++;
    printf("[Sucesso] Item cadastrado com sucesso!\n");
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n[Erro] Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    printf("\n=== REMOVER ITEM ===\n");
    char nomeRemover[30];
    printf("Nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    // Busca sequencial do item a remover
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Deslocar elementos para remover o item
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("[Sucesso] Item '%s' removido da mochila.\n", nomeRemover);
            return;
        }
    }

    printf("[Erro] Item '%s' não encontrado na mochila.\n", nomeRemover);
}

// Função para listar todos os itens cadastrados na mochila
void listarItens() {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (totalItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    printf("Total de itens: %d/%d\n\n", totalItens, CAPACIDADE_MOCHILA);

    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %s\n", i + 1, mochila[i].nome);
        printf("    Tipo: %s\n", mochila[i].tipo);
        printf("    Quantidade: %d\n", mochila[i].quantidade);
        printf("    ---------------\n");
    }
}

// Função de busca sequencial para encontrar um item pelo nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n[Erro] Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    printf("\n=== BUSCAR ITEM ===\n");
    char nomeBuscar[30];
    printf("Nome do item a buscar: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    // Busca sequencial
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\n[Encontrado]\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("[Não Encontrado] Item '%s' não está na mochila.\n", nomeBuscar);
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("╔══════════════════════════════════╗\n");// Menu estilizado usando capslock + alt + 200, 201 e 205
    printf("║        MOCHILA DO JOGADOR        ║\n");
    printf("╠══════════════════════════════════╣\n");
    printf("║ [1] Cadastrar novo item          ║\n");
    printf("║ [2] Remover item                 ║\n");
    printf("║ [3] Listar itens                 ║\n");
    printf("║ [4] Buscar item                  ║\n");
    printf("║ [5] Sair                         ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

// Função principal com loop de menu
int main() {
    int opcao;

    printf("======= Acesso ao Inventário! =======\n");

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar buffer após scanf

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\n[Saída] Encerrando o sistema. Obrigado por jogar!\n");
                return 0;
            default:
                printf("[Erro] Opção inválida! Digite um número de 1 a 5.\n");
        }
    }

    return 0;
}