#include <stdio.h>
#include <stdlib.h>

#define DEGREE 3  // Ordem da árvore B (mínimo de filhos)

// Estrutura do nó da Árvore B
typedef struct Node {
    int key[2 * DEGREE - 1];         // Array de chaves
    struct Node* children[2 * DEGREE]; // Array de ponteiros para filhos
    int n;                            // Número de chaves atualmente no nó
    int leaf;                         // 1 se for folha, 0 se não for
} Node;

// Declaração das funções
Node* createNode(int leaf);
void inorder(Node* root);
Node* search(Node* root, int key);
void insert(Node** root, int key);
void insertNonFull(Node* node, int key);
void splitNode(Node* parent, int index, Node* child);
void printTree(Node* root, int level); // Função para imprimir a árvore
void menu(Node** root);

int main() {
    Node* root = NULL;  // Inicializa a árvore B como vazia
    menu(&root);        // Chama o menu
    return 0;
}

// Função para criar um novo nó
Node* createNode(int leaf) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->leaf = leaf;
    newNode->n = 0;
    for (int i = 0; i < 2 * DEGREE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Função para percorrer a árvore e imprimir as chaves em ordem
void inorder(Node* root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            if (!root->leaf) {
                inorder(root->children[i]);
            }
            printf("%d ", root->key[i]);
        }
        if (!root->leaf) {
            inorder(root->children[root->n]);
        }
    }
}

// Função para buscar uma chave na árvore
Node* search(Node* root, int key) {
    if (root == NULL) {
        return NULL; // Se a árvore está vazia
    }

    int i = 0;
    while (i < root->n && key > root->key[i]) {
        i++;
    }

    if (i < root->n && root->key[i] == key) {
        return root;
    }

    if (root->leaf) {
        return NULL;
    }

    return search(root->children[i], key);
}

// Função para inserir uma chave na árvore B
void insert(Node** root, int key) {
    if (*root == NULL) {
        *root = createNode(1);
        (*root)->key[0] = key;
        (*root)->n = 1;
    } else {
        if ((*root)->n == 2 * DEGREE - 1) { // O nó está cheio
            Node* newRoot = createNode(0);
            newRoot->children[0] = *root; // O nó antigo se torna o primeiro filho do novo nó
            splitNode(newRoot, 0, *root);  // Divide o nó cheio
            int i = (newRoot->key[0] < key) ? 1 : 0; // Determina onde inserir a nova chave
            insertNonFull(newRoot->children[i], key);
            *root = newRoot; // Atualiza a raiz
        } else {
            insertNonFull(*root, key); // Insere em um nó que não está cheio
        }
    }
}

// Função auxiliar para inserir em um nó que não está cheio
void insertNonFull(Node* node, int key) {
    int i = node->n - 1; // Começa a inserção pela última chave
    if (node->leaf) {
        // Inserção em um nó folha
        while (i >= 0 && node->key[i] > key) {
            node->key[i + 1] = node->key[i]; // Move a chave para a direita
            i--;
        }
        node->key[i + 1] = key; // Insere a nova chave
        node->n++; // Aumenta o número de chaves
    } else {
        // Inserção em um nó não folha
        while (i >= 0 && node->key[i] > key) {
            i--;
        }
        i++; // Encontra o filho correto
        if (node->children[i]->n == 2 * DEGREE - 1) { // Se o filho está cheio
            splitNode(node, i, node->children[i]); // Divide o filho
            if (node->key[i] < key) {
                i++; // Verifica onde inserir a chave
            }
        }
        insertNonFull(node->children[i], key); // Insere a chave no filho adequado
    }
}

// Função para dividir o nó filho quando ele estiver cheio
void splitNode(Node* parent, int index, Node* child) {
    Node* newChild = createNode(child->leaf); // Cria um novo nó
    newChild->n = DEGREE - 1; // Define o número de chaves no novo nó

    // Move as chaves da metade direita do nó filho para o novo nó
    for (int j = 0; j < DEGREE - 1; j++) {
        newChild->key[j] = child->key[j + DEGREE]; // Mover chaves para o novo nó
    }

    // Se não for folha, move os filhos
    if (!child->leaf) {
        for (int j = 0; j < DEGREE; j++) {
            newChild->children[j] = child->children[j + DEGREE]; // Mover filhos para o novo nó
        }
    }

    child->n = DEGREE - 1; // Atualiza o número de chaves do nó filho

    // Move as chaves e os filhos do pai para abrir espaço para o novo nó
    for (int j = parent->n; j >= index + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[index + 1] = newChild; // Adiciona o novo nó como filho

    for (int j = parent->n - 1; j >= index; j--) {
        parent->key[j + 1] = parent->key[j];
    }
    parent->key[index] = child->key[DEGREE - 1];
    parent->n++; // Aumenta o número de chaves no nó pai
}

// Função para imprimir a árvore de forma estruturada
void printTree(Node* root, int level) {
    if (root != NULL) {
        printf("Nível %d: ", level);
        for (int i = 0; i < root->n; i++) {
            printf("%d ", root->key[i]);
        }
        printf("\n");
        level++;
        for (int i = 0; i <= root->n; i++) {
            printTree(root->children[i], level); // Chama recursivamente para imprimir os filhos
        }
    }
}

// Função de menu
void menu(Node** root) {
    int option = 0;
    do {
        printf("\n----------MENU---------\n1 - Inserir Valor\n2 - Buscar Valor\n3 - Imprimir Árvore\n4 - Exibir Árvore Estruturada\n9 - SAIR\n-----------------------\nEscolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                int key;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &key);
                insert(root, key);
            } break;
            case 2: {
                int key;
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &key);
                Node* result = search(*root, key);
                if (result)
                    printf("Valor %d encontrado.\n", key);
                else
                    printf("Valor %d não encontrado.\n", key);
            } break;
            case 3:
                printf("Imprimindo Árvore em ordem: ");
                inorder(*root);
                printf("\n");
                break;
            case 4:
                printf("Exibindo Árvore Estruturada:\n");
                printTree(*root, 0);
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (option != 9);
}

//Nao consegui fazer funcionar com DEGREE - !, entao joguei no GPT e ele colocou esse [2 * DEGREE - 1] e funcionou, mas agora o nó passa do limite de chaves, eu passei tanto tempo nisso que eu to pensando em fazer vestibular de novo e ir pra medicina
