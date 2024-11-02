#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do nó para o Treap
typedef struct Node {
    int data;              // valor do nó
    int priority;         // Prioridade do nó
    struct Node *left, *right;
} Node;

// Declaração das funções
Node* newNode(int data);
Node* rightRotation(Node* y);
Node* leftRotation(Node* x);
Node* insert(Node* root, int data);
Node* deleteNode(Node* root, int data);
void inOrder(Node* root);
void preOrder(Node* root);
void postOrder(Node* root);
void printTree(Node* root, int space);
Node* search(Node* root, int data);
void menu(Node** root);

int main() {
    srand(time(0));  // Inicializa prioridades aleatórias

    Node* root = NULL;
    menu(&root);  // Chama o menu
    return 0;
}

// Implementação das funções

// Função para criar um novo nó com uma prioridade aleatória
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->priority = rand() % 100;
    node->left = node->right = NULL;
    return node;
}

// Rotação para a direita
Node* rightRotation(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

// Rotação para a esquerda
Node* leftRotation(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

// Inserir um novo valor no Treap
Node* insert(Node* root, int data) {
    if (!root) return newNode(data);

    if (data < root->data) {
        root->left = insert(root->left, data);
        if (root->left->priority > root->priority)
            root = rightRotation(root);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
        if (root->right->priority > root->priority)
            root = leftRotation(root);
    }

    return root;
}

// Excluir um valor do Treap
Node* deleteNode(Node* root, int data) {
    if (!root) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            root = temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            root = temp;
        } else if (root->left->priority < root->right->priority) {
            root = leftRotation(root);
            root->left = deleteNode(root->left, data);
        } else {
            root = rightRotation(root);
            root->right = deleteNode(root->right, data);
        }
    }

    return root;
}

// Funções para percursos
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void preOrder(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// Função para exibir a árvore em uma forma estruturada
void printTree(Node* root, int space) {
    if (root == NULL) return;
    space += 5;
    printTree(root->right, space);
    for (int i = 5; i < space; i++) printf(" ");
    printf("%d (%d)\n", root->data, root->priority);
    printTree(root->left, space);
}

// Função de busca
Node* search(Node* root, int data) {
    if (!root || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Função de menu
void menu(Node** root) {
    int option = 0;
    do {
        printf("\n----------MENU---------\n1 - Inserir Valor\n2 - Excluir Valor\n3 - Buscar Valor\n4 - Imprimir em ordem (InOrder)\n5 - Imprimir em pré-ordem (PreOrder)\n6 - Imprimir em pós-ordem (PostOrder)\n7 - Exibir árvore\n9 - SAIR\n-----------------------\nEscolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                int data;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &data);
                *root = insert(*root, data);
            } break;
            case 2: {
                int data;
                printf("Digite o valor a ser excluído: ");
                scanf("%d", &data);
                *root = deleteNode(*root, data);
            } break;
            case 3: {
                int data;
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &data);
                Node* result = search(*root, data);
                if (result)
                    printf("Valor %d encontrado com prioridade %d.\n", result->data, result->priority);
                else
                    printf("Valor %d não encontrado.\n", data);
            } break;
            case 4:
                printf("Imprimindo em ordem (InOrder): ");
                inOrder(*root);
                printf("\n");
                break;
            case 5:
                printf("Imprimindo em pré-ordem (PreOrder): ");
                preOrder(*root);
                printf("\n");
                break;
            case 6:
                printf("Imprimindo em pós-ordem (PostOrder): ");
                postOrder(*root);
                printf("\n");
                break;
            case 7:
                printf("Exibindo a árvore:\n");
                printTree(*root, 0);
                printf("\n");
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (option != 9);
}
