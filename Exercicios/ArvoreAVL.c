#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Prototipos das funções usadas
struct Node* insertNode(struct Node *node, int data);
struct Node* deleteNode(struct Node *root, int data);
void printPreOrder(struct Node *root);
void displayTree(struct Node *root);
void menu();


// Função principal
int main() {
    menu(); // Chama a função do menu interativo
    return 0;
}

// Função para exibir o menu e lidar com as opções
void menu() {
    struct Node *root = NULL;
    int option, value;

    do {
        printf("\nMenu:\n"
               "1 - Inserir valor\n"
               "2 - Excluir valor\n"
               "3 - Exibir árvore (pré-ordem)\n"
               "4 - Exibir árvore (formato gráfico)\n"
               "5 - Sair\n"
               "Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("Valor inserido!\n");
                break;

            case 2:
                printf("Digite o valor a ser excluído: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Valor excluído (se existir)!\n");
                break;

            case 3:
                printf("Árvore em pré-ordem: ");
                printPreOrder(root);
                printf("\n");
                break;

            case 4:
                printf("Exibindo a árvore no formato gráfico:\n");
                displayTree(root);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (option != 5);
}


// Retorna a altura do nó
int height(struct Node *N) {
    if (N == NULL) {
        return 0;
    }
    return N->height;
}

// Retorna o maior valor
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Cria um nó
struct Node *newNode(int data) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Rotação à esquerda
struct Node *rotateLeft(struct Node *node) {
    struct Node *rightChild = node->right;
    struct Node *leftSubtree = rightChild->left;

    // Realiza a rotação
    rightChild->left = node;
    node->right = leftSubtree;

    // Atualiza as alturas
    node->height = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

    // Retorna a nova raiz
    return rightChild;
}

// Rotação à direita
struct Node *rotateRight(struct Node *node) {
    struct Node *leftChild = node->left;
    struct Node *rightSubtree = leftChild->right;

    // Realiza a rotação
    leftChild->right = node;
    node->left = rightSubtree;

    // Atualiza as alturas
    node->height = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

    // Retorna a nova raiz
    return leftChild;
}


// Retorna o fator de balanceamento de um nó
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insere um nó
struct Node *insertNode(struct Node *node, int data) {
  // Encontra a posição correta para inserir o nó e insere-o
  if (node == NULL)
    return (newNode(data));

  if (data < node->data)
    node->left = insertNode(node->left, data);
  else if (data > node->data)
    node->right = insertNode(node->right, data);
  else
    return node;

  // Atualiza o fator de balanceamento de cada nó e
  // balanceia a árvore
  node->height = 1 + max(height(node->left), height(node->right));

  int balance = getBalance(node);

  // Rotação à direita
  if (balance > 1 && data < node->left->data)
    return rotateRight(node);

  // Rotação à esquerda
  if (balance < -1 && data > node->right->data)
    return rotateLeft(node);

  // Rotação dupla esquerda-direita
  if (balance > 1 && data > node->left->data) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // Rotação dupla direita-esquerda
  if (balance < -1 && data < node->right->data) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

// Encontra o nó com o menor valor (subárvore da direita)
struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  // Encontra o nó mais à esquerda
  while (current->left != NULL)
    current = current->left;

  return current;
}

// Exclui um nó
struct Node *deleteNode(struct Node *root, int data) {
  // Encontra o nó e o exclui
  if (root == NULL)
    return root;

  if (data < root->data)
    root->left = deleteNode(root->left, data);

  else if (data > root->data)
    root->right = deleteNode(root->right, data);

  else {
    // Caso o nó tenha um filho ou nenhum
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      // Caso não tenha filhos
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else // Caso tenha um único filho
        *root = *temp; // Copia os dados do filho
      free(temp);
    } else {
      // Caso tenha dois filhos
      struct Node *temp = minValueNode(root->right);

      // Substitui os dados do nó pela menor chave da subárvore direita
      root->data = temp->data;

      // Exclui o nó que foi substituído
      root->right = deleteNode(root->right, temp->data);
    }
  }

  if (root == NULL)
    return root;

  // Atualiza o fator de balanceamento de cada nó e
  // balanceia a árvore
  root->height = 1 + max(height(root->left), height(root->right));

  int balance = getBalance(root);

  // Rotação à direita
  if (balance > 1 && getBalance(root->left) >= 0)
    return rotateRight(root);

  // Rotação dupla esquerda-direita
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }

  // Rotação à esquerda
  if (balance < -1 && getBalance(root->right) <= 0)
    return rotateLeft(root);

  // Rotação dupla direita-esquerda
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }

  return root;
}

// Imprime a árvore em pré-ordem
void printPreOrder(struct Node *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

// Função auxiliar para exibir a árvore em um formato visual de árvore
void printTree(struct Node *root, int space) {
    // Define o espaço entre níveis
    int count = 5;

    // Caso base
    if (root == NULL)
        return;

    // Aumenta a distância entre os níveis
    space += count;

    // Imprime a subárvore da direita primeiro
    printTree(root->right, space);

    // Imprime o nó atual após um espaço adequado
    printf("\n");
    for (int i = count; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // Imprime a subárvore da esquerda
    printTree(root->left, space);
}

// Função para exibir a árvore, chamando a função auxiliar
void displayTree(struct Node *root) {
    printTree(root, 0);
}
