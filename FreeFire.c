#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_MOCHILA 10

// =============== Estrutura para Itens ===============
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[CAPACIDADE_MOCHILA];
int totalItens = 0;
int comparacoes = 0;

// =============== Funções Auxiliares ===============

// Leitura segura de inteiro
int lerInteiroSeguro() {
    int valor;
    while (scanf("%d", &valor) != 1) {
        printf("[Erro] Digite um número válido: ");
        while (getchar() != '\n'); 
    }
    getchar(); 
    return valor;
}

// =============== Inserção de Itens ===============
void inserirItem() {
    if (totalItens >= CAPACIDADE_MOCHILA) {
        printf("\n[Erro] Mochila cheia! Máximo atingido.\n");
        return;
    }

    Item novo;

    printf("\n=== Cadastrar Novo Item ===\n");

    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo (Arma/Armadura/Munição/Cura): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    novo.quantidade = lerInteiroSeguro();

    if (novo.quantidade < 0) {
        printf("[Erro] Quantidade não pode ser negativa!\n");
        return;
    }

    mochila[totalItens++] = novo;

    printf("[Sucesso] Item cadastrado com sucesso!\n");
}

// =============== Remover Item ===============
void removerItem() {
    if (totalItens == 0) {
        printf("\n[Erro] Mochila vazia!\n");
        return;
    }

    char nomeRemover[30];

    printf("\n=== Remover Item ===\n");
    printf("Nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("[Sucesso] Item '%s' removido.\n", nomeRemover);
    } else {
        printf("[Erro] Item não encontrado.\n");
    }
}

// =============== Listar Itens ===============
void listarItens() {
    printf("\n=== Itens na Mochila (%d/%d)===\n\n", totalItens, CAPACIDADE_MOCHILA);

    if (totalItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    printf(" %-20s | %-15s | %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf(" %-20s | %-15s | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("----------------------------------------------------\n");
}

// =============== Busca Sequencial ===============
void buscarSequencial() {
    if (totalItens == 0) {
        printf("\n[Erro] Mochila vazia!\n");
        return;
    }

    char nomeBuscar[30];

    printf("\n=== Busca Sequencial ===\n");
    printf("Nome do item: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    comparacoes = 0;

    for (int i = 0; i < totalItens; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("[Encontrado] Comparações: %d\n", comparacoes);
            return;
        }
    }

    printf("[Não Encontrado] Comparações: %d\n", comparacoes);
}

// =============== Ordenação usando Bubble Sort ===============
void ordenarMochila() {
    if (totalItens < 2) {
        printf("[Aviso] Poucos itens para ordenar.\n");
        return;
    }

    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    printf("[Sucesso] Mochila ordenada.\n");
}

// =============== Busca Binária ===============
void buscarBinaria() {
    if (totalItens == 0) {
        printf("\n[Erro] Mochila vazia!\n");
        return;
    }

    char nomeBuscar[30];

    printf("\n=== Busca Binária ===\n");
    printf("Nome do item: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin); 
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0'; 

    comparacoes = 0;
    int inicio = 0;
    int fim = totalItens - 1;

    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, nomeBuscar);

        if (resultado == 0) {
            printf("[Encontrado] Comparações: %d\n", comparacoes);
            return;
        }
        if (resultado < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("[Não Encontrado] Comparações: %d\n", comparacoes);
}

// =============== Menu Principal ===============
void exibirMenu() {
    printf("\n╔══════════════════════════════════╗\n");
    printf("║        MOCHILA DO JOGADOR        ║\n");
    printf("╠══════════════════════════════════╣\n");
    printf("║ [1] Cadastrar novo item          ║\n");
    printf("║ [2] Remover item                 ║\n");
    printf("║ [3] Listar itens                 ║\n");
    printf("║ [4] Buscar (Sequencial)          ║\n");
    printf("║ [5] Ordenar Mochila              ║\n");
    printf("║ [6] Buscar (Binária)             ║\n");
    printf("║ [0] Sair                         ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("Total de Itens: %d/%d\n\n", totalItens, CAPACIDADE_MOCHILA);
    printf("Escolha uma opção: ");

}

// =============== Função Principal ===============
int main() {
    int opcao;

    printf("======= Acesso ao Inventário! =======\n");

    do {
        exibirMenu();
        opcao = lerInteiroSeguro();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarSequencial(); break;
            case 5: ordenarMochila(); break;
            case 6: buscarBinaria(); break;
            case 0: printf("\n[Saída] Encerrando o sistema.\n"); break;
            default: printf("[Erro] Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}