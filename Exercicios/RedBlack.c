#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void leftRotation(Node **root, Node *primaryNode) {
    Node *secondaryNode = primaryNode->right;
    primaryNode->right = secondaryNode->left;
    if (secondaryNode->left != NULL) {
        secondaryNode->left->parent = primaryNode;
    }
    secondaryNode->parent = primaryNode->parent;
    if (primaryNode->parent == NULL) {
        *root = secondaryNode;
    } else if (primaryNode == primaryNode->parent->left) {
        primaryNode->parent->left = secondaryNode;
    } else {
        primaryNode->parent->right = secondaryNode;
    }
    secondaryNode->left = primaryNode;
    primaryNode->parent = secondaryNode;
}

void rightRotation(Node **root, Node *primaryNode) {
    Node *secondaryNode = primaryNode->left;
    primaryNode->left = secondaryNode->right;
    if (secondaryNode->right != NULL) {
        secondaryNode->right->parent = primaryNode;
    }
    secondaryNode->parent = primaryNode->parent;
    if (primaryNode->parent == NULL) {
        *root = secondaryNode;
    } else if (primaryNode == primaryNode->parent->right) {
        primaryNode->parent->right = secondaryNode;
    } else {
        primaryNode->parent->left = secondaryNode;
    }
    secondaryNode->right = primaryNode;
    primaryNode->parent = secondaryNode;
}

void correction(Node **root, Node *primaryNode) {
    while (primaryNode != *root && primaryNode->parent->color == RED) {
        if (primaryNode->parent == primaryNode->parent->parent->left) {
            Node *secondaryNode = primaryNode->parent->parent->right;
            if (secondaryNode != NULL && secondaryNode->color == RED) {
                primaryNode->parent->color = BLACK;
                secondaryNode->color = BLACK;
                primaryNode->parent->parent->color = RED;
                primaryNode = primaryNode->parent->parent;
            } else {
                if (primaryNode == primaryNode->parent->right) {
                    primaryNode = primaryNode->parent;
                    leftRotation(root, primaryNode);
                }
                primaryNode->parent->color = BLACK;
                primaryNode->parent->parent->color = RED;
                rightRotation(root, primaryNode->parent->parent);
            }
        } else {
            Node *secondaryNode = primaryNode->parent->parent->left;
            if (secondaryNode != NULL && secondaryNode->color == RED) {
                primaryNode->parent->color = BLACK;
                secondaryNode->color = BLACK;
                primaryNode->parent->parent->color = RED;
                primaryNode = primaryNode->parent->parent;
            } else {
                if (primaryNode == primaryNode->parent->left) {
                    primaryNode = primaryNode->parent;
                    rightRotation(root, primaryNode);
                }
                primaryNode->parent->color = BLACK;
                primaryNode->parent->parent->color = RED;
                leftRotation(root, primaryNode->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertNode(Node **root, int data) {
    Node *first = createNode(data);
    Node *second = NULL;
    Node *third = *root;

    while (third != NULL) {
        second = third;
        if (first->data < third->data) {
            third = third->left;
        } else {
            third = third->right;
        }
    }

    first->parent = second;

    if (second == NULL) {
        *root = first;
    } else if (first->data < second->data) {
        second->left = first;
    } else {
        second->right = first;
    }

    correction(root, first);
}




void preOrder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        if (root->color == RED) {
            printf("%d RED\n", root->data);
        } else {
            printf("%d BLACK\n", root->data);
        }
        inOrder(root->right);
    }
}

void printTree(Node *root, int space) {
    int COUNT = 10;
    
    if (root == NULL)
        return;

    space += COUNT;

    printTree(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    
    if (root->color == RED)
        printf("%d (RED)\n", root->data);
    else
        printf("%d (BLACK)\n", root->data);

    printTree(root->left, space);
}

void menu(Node **root){
    int option = 0;
    do {

        printf("----------MENU---------\n1 - Inserir Valor\n2 - Imprimir árvore em ordem (InOrder)\n3 - Imprimir árvore em pré-ordem (PreOrder)\n4 - Imprimir árvore em pós-ordem (PostOrder)\n5 - Exibir árvore\n9 - SAIR\n-----------------------\n---SELECIONE A OPÇÃO DESEJADA---\n");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                int data;
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &data);
                insertNode(root, data);
            } break;
            case 2:
                printf("Imprimindo em ordem (InOrder):\n");
                inOrder(*root);
                printf("\n");
                break;
            case 3:
                printf("Imprimindo em pré-ordem (PreOrder):\n");
                preOrder(*root);
                printf("\n");
                break;
            case 4:
                printf("Imprimindo em pós-ordem (PostOrder):\n");
                postOrder(*root);
                printf("\n");
                break;
            case 5:
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

int main() {
    Node *root = NULL;
    menu(&root);
    return 0;
}
