#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 10

// =============== Estrutura para Itens ===============
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 5
} Componente;

Componente torre[MAX_COMPONENTES];
int numComponentes = 0;
int comparacoes = 0;
int ordenadoPorNome = 0;

// ================= Funções Auxiliares =================
void limparBuffer() {
    while (getchar() != '\n');
}

int lerInteiroSeguro() {
    int valor;
    while (scanf("%d", &valor) != 1) {
        printf("Digite um número válido: ");
        limparBuffer();
    }
    limparBuffer();
    return valor;
}

// ================= Exibir Componentes =================
void mostrarComponentes() {
    printf("\n======= COMPONENTES (%d/%d) =======\n", numComponentes, MAX_COMPONENTES);

    if (numComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "PRIOR.");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < numComponentes; i++) {
        printf("%-20s | %-15s | %d\n",
               torre[i].nome,
               torre[i].tipo,
               torre[i].prioridade);
    }
}

// ================= Adicionar Componentes =================
void cadastrarComponente() {
    if (numComponentes >= MAX_COMPONENTES) {
        printf("Limite máximo atingido!\n");
        return;
    }

    printf("\n======= Novo Componente =======\n");

    printf("Nome: ");
    fgets(torre[numComponentes].nome, sizeof(torre[numComponentes].nome), stdin);
    torre[numComponentes].nome[strcspn(torre[numComponentes].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(torre[numComponentes].tipo, sizeof(torre[numComponentes].tipo), stdin);
    torre[numComponentes].tipo[strcspn(torre[numComponentes].tipo, "\n")] = '\0';

    printf("Prioridade (1-5): ");
    torre[numComponentes].prioridade = lerInteiroSeguro();

    if (torre[numComponentes].prioridade < 1 || torre[numComponentes].prioridade > 5) {
        printf("Prioridade inválida! Ajustada para 1.\n");
        torre[numComponentes].prioridade = 1;
    }

    numComponentes++;
    ordenadoPorNome = 0;

    printf("Componente cadastrado com sucesso!\n");
}

// =============== Remover Componente ===============
void removerComponente() {
    if (numComponentes == 0) {
        printf("Nenhum componente para remover.\n");
        return;
    }

    char nome[30];
    printf("Nome do componente para remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = -1;

    for (int i = 0; i < numComponentes; i++) {
        if (strcmp(torre[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Componente não encontrado.\n");
        return;
    }

    for (int i = pos; i < numComponentes - 1; i++)
        torre[i] = torre[i + 1];

    numComponentes--;
    ordenadoPorNome = 0;

    printf("Componente removido com sucesso!\n");
}

// ================= Bubble Sort (NOME) =================
void bubbleSortNome() {
    comparacoes = 0;

    for (int i = 0; i < numComponentes - 1; i++) {
        for (int j = 0; j < numComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                Componente temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }

    ordenadoPorNome = 1;
}

// ================= Insertion Sort (TIPO) =================
void insertionSortTipo() {
    comparacoes = 0;

    for (int i = 1; i < numComponentes; i++) {
        Componente chave = torre[i];
        int j = i - 1;

        while (j >= 0 && strcmp(torre[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            torre[j + 1] = torre[j];
            j--;
        }
        torre[j + 1] = chave;
    }

    ordenadoPorNome = 0;
}

// ================= Selection Sort (PRIORIDADE) =================
void selectionSortPrioridade() {
    comparacoes = 0;

    for (int i = 0; i < numComponentes - 1; i++) {
        int min = i;

        for (int j = i + 1; j < numComponentes; j++) {
            comparacoes++;
            if (torre[j].prioridade < torre[min].prioridade)
                min = j;
        }

        if (min != i) {
            Componente temp = torre[i];
            torre[i] = torre[min];
            torre[min] = temp;
        }
    }

    ordenadoPorNome = 0;
}

// ================= Menu de ordenação =================
void menuOrdenacao() {
    int opcao;

    printf("\n======= MENU DE ORDENAÇÃO =======\n");
    printf("1 - Ordenar por Nome\n"); // Bubble Sort
    printf("2 - Ordenar por Tipo\n"); // Insertion Sort
    printf("3 - Ordenar por Prioridade\n"); // Selection Sort
    printf("Escolha: ");

    opcao = lerInteiroSeguro();

    clock_t inicio = clock();

    switch (opcao) {
        case 1:
            bubbleSortNome();
            break;
        case 2:
            insertionSortTipo();
            break;
        case 3:
            selectionSortPrioridade();
            break;
        default:
            printf("Opção inválida.\n");
            return;
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Comparações: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);

    mostrarComponentes();
}

// =============== Busca Binária ===============
void buscaBinariaPorNome() {
    if (!ordenadoPorNome) {
        printf("A lista precisa estar ordenada alfabeticamente por NOME.\n");
        return;
    }

    char chave[30];
    printf("Nome do componente-chave: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int inicio = 0, fim = numComponentes - 1;

    comparacoes = 0;

    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int res = strcmp(torre[meio].nome, chave);

        if (res == 0) {
            printf("Componente encontrado!\n");
            printf("Tipo: %s | Prioridade: %d\n",
                   torre[meio].tipo,
                   torre[meio].prioridade);
            printf("Comparações: %d\n", comparacoes);
            return;
        }
        else if (res < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Componente não encontrado.\n");
    printf("Comparações: %d\n", comparacoes);
}

// =============== Menu Principal ===============
void exibirMenu() {
    printf("╔══════════════════════════════════╗\n");
    printf("║        MONTAGEM DA TORRE         ║\n");
    printf("╠══════════════════════════════════╣\n");
    printf("║1 - Adicionar Componente          ║\n");
    printf("║2 - Remover Componente            ║\n");
    printf("║3 - Mostrar Componentes           ║\n");
    printf("║4 - Menu de Ordenação             ║\n");
    printf("║5 - Busca Binária por Nome        ║\n");
    printf("║0 - Sair                          ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("\n======= COMPONENTES (%d/%d) =======\n", numComponentes, MAX_COMPONENTES);
    printf("Status da ordenação por nome: %s\n",
           ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");

    printf("Escolha: ");
}

// =============== Função Principal ===============
int main() {
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiroSeguro();

        switch (opcao) {
            case 1: cadastrarComponente(); break;
            case 2: removerComponente(); break;
            case 3: mostrarComponentes(); break;
            case 4: menuOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Fuga concluída com sucesso.\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}