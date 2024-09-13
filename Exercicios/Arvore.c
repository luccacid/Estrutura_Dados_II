#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
  int data;
  struct Node *left;
  struct Node *right;
} Node;

Node *createNode(int data){
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node *insert(Node *root, int data) {
  if (root == NULL) {
      return createNode(data);
    }
    
    if (data < root->data) {
      root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
  return root;
}

Node *search(Node *root, int data){
  if(root == NULL || root->data == data){
    return root;
  }
  
  if(root->data > data){
    search(root->left, data);
    
  }else{
    search(root->right, data);
  }

  
}

Node *findMin(Node *root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

Node *deleteNode(Node *root, int data) {
    if(root == NULL){
        return root;
    }
    
    if(data > root->data){
      
        root->right = deleteNode(root->right, data);
      
    }else if(data < root->data){
      
        root->left = deleteNode(root->left, data);
      
    }else{
      
        if(root->left == NULL && root->right==NULL){
          
            printf("Deletando nó %d...\n", root->data);
          
            free(root);
          
            printf("Nó deletado com sucesso!");
          
            return NULL;
          
        } else if(root->left == NULL){
          
            Node *temp = root->right;
          
            printf("Deletando nó %d...\n", root->data);
          
            free(root);
          
            printf("Nó deletado com sucesso!");
          
            return temp;
          
        }else if(root->right == NULL){
          
            Node *temp = root->left;
          
            printf("Deletando nó %d...\n", root->data);
          
            free(root);
          
            printf("Nó deletado com sucesso!");
          
            return temp;
        }
        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);

    }
    return root;
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void printTree(Node *root, int space) {
    if (root == NULL) {
        return;
    }

    space += 10;

    printTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    printTree(root->left, space);
}



void menu() {
    Node* root = NULL;
    int option, value;

    do {
      printf("\nMenu:\n1. Inserir elemento\n2. Buscar elemento\n3. Excluir elemento\n4. Imprimir árvore (in-order)\n5. Imprimir árvore formatada\n6. Sair\nEscolha uma opção: ");
      //tinha feito um print pra cada opção, mas lembrei de um professor que criticou quem faz isso       
      scanf("%d", &option);

      switch (option) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Elemento %d inserido.\n", value);
                break;
            case 2:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &value);
                if (search(root, value) != NULL) {
                    printf("Elemento %d encontrado na árvore.\n", value);
                } else {
                    printf("Elemento %d não encontrado na árvore.\n", value);
                }
                break;
            case 3:
                printf("Digite o valor a ser excluído: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Elemento %d excluído.\n", value);
                break;
            case 4:
                printf("Árvore em ordem: ");
                inorder(root);
                printf("\n");
                break;
            case 5:
                printf("Árvore formatada:\n");
                printTree(root, 0);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (option != 6);
}

int main() {
    menu();
    return 0;
}
