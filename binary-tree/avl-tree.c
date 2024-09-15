#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Rotate Cases
// Y child of Z, and X grandchild of Z
// a) y is left child of z and x is left child of y (Left Left Case) -
// b) y is left child of z and x is right child of y (Left Right Case) -
// c) y is right child of z and x is right child of y (Right Right Case) -
// d) y is right child of z and x is left child of y (Right Left Case) -

struct node {
    int data;
    struct node *right;
    struct node *left;
};

typedef struct node node;

node *createNode(){
    node *new_node = (node *) malloc(sizeof(node));

    return new_node;

}

node *reset() {
    node *new_node = createNode();
    new_node ->right = NULL;
    new_node ->left = NULL;

    return new_node;
}

int height(node *node) {
    int right, left;

    if (node == NULL) {
        return 0;
    }

    right = height(node->right);
    left = height(node->left);

    if (left > right) {
        return left + 1;
    }
    else {
        return right + 1;
    }
}

int balanceFactor(node *root) {
    if (root == NULL) {
        return 0;
    }

    return height(root->left) - height(root->right);
}

node *rightRotate(node *nodeUnbalanced) { //Solution to a) CASE
    node *leftNode = nodeUnbalanced->left;
    node *leftRightNode = leftNode->right;

    //1. Perform Rotation
    leftNode->right = nodeUnbalanced;
    nodeUnbalanced->left = leftRightNode;

    //2. Return new root
    return leftNode;
}

node *leftRotate(node *nodeUnbalanced) {
    node *rightNode = nodeUnbalanced->right;
    node *rightLeftNode = rightNode->left;

    //1. Perform Rotation
    rightNode->left = nodeUnbalanced;
    nodeUnbalanced->right = rightNode->left;

    //2. Return new root
    return rightNode;
}

node *balanceAfterInsert(node * currentNode, int data, int balance) {
    //

    //  Data inserted is greater than parent right node data, and right node height is more then 1
    if (balance < -1 && data > currentNode->right->data)
        return leftRotate(currentNode);

    //  Data inserted is less than parent left node data, and left node height is more than 1
    if (balance > 1 && data < currentNode->left->data)
        return rightRotate(currentNode);

    //  Data inserted is greater than parent left node data, and right node height is more than 1
    if (balance > 1 && data > currentNode->left->data) {
        currentNode->left = leftRotate(currentNode->left);
        return rightRotate(currentNode);
    }

    //  Data inserted is less than parent right node data, and right node height is more than 1
    if (balance < -1 && data < currentNode->right->data) {
        currentNode->right = rightRotate(currentNode->right);
        return leftRotate(currentNode);
    }

    //  If node is balanced, no need balance
    return currentNode;
}
    node * balanceAfterDelete(node *currentNode, int balance){

        //  Simple right rotation
        if(balance > 1 && balanceFactor(currentNode->left) >= 0)
            currentNode = rightRotate(currentNode);

        //  Double rotation - left right
        if (balance > 1 && balanceFactor(currentNode->left) < 0) {
            currentNode->left = leftRotate(currentNode->left);
            currentNode = rightRotate(currentNode);
        }

        //  Simple left rotation
        if (balance < -1 && balanceFactor(currentNode->right) <= 0)
                currentNode = leftRotate(currentNode);

        //  Double rotation - right left
        if (balance < -1 && balanceFactor(currentNode->right) > 0) {
            currentNode->right = rightRotate(currentNode->right);
            currentNode = leftRotate(currentNode);
        }

        //If the node keeps balanced after delete
        return currentNode;
    }

    node * insert(node *currentNode, int data){
        if (currentNode == NULL) {
            //  Creates the new node
            currentNode = reset();
            if(currentNode == NULL) {
                printf("\n ERROR! Memory allocation problem");
                exit (-1);
            }

            //  Set the new node data
            currentNode->data = data;
        }

        if (currentNode->data > data) {

            //  Call the insert function, that some point of the recursion will return a node
            //  And this node will be setted at the left of the current node
            currentNode->left = insert(currentNode->left, data);
        }
        else if(currentNode->data < data) {

            //  Same case as previous, but the node will be setted to the right of current node
            currentNode->right = insert(currentNode->right, data);
        }

        int balance = balanceFactor(currentNode);
        currentNode = balanceAfterInsert(currentNode, data, balance);
        return currentNode;
    }

    node * minValueNode(node * root) {
    node *currentNode = root;

    while(currentNode && currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;
}

    node * delete(node *currentNode, int data){
        if(currentNode == NULL)
            return currentNode;

        /**
         *  If the Data to be Deleted is smaller
         *  than the currentNode data
         *  then it go to the left subtree
         */
        if (data < currentNode->data)
            currentNode->left = delete(currentNode->left, data);

        /**
         *  If data to be deleted is greater
         *  than the currentNode data
         *  then it go to the right subtree
         */
        else if(data > currentNode->data)
            currentNode->right = delete(currentNode->right, data);

        /**
         *  if data is equal to the currentNode data,
         *  then currentNode is the one to be deleted.
         */
        else if(data == currentNode->data) {
            if(currentNode->left == NULL) { //in the left case
                node *temp = currentNode->right;
                free(currentNode);
                return temp;
            }

        else if (currentNode-> right == NULL) { //in the right case
            node *temp = currentNode->left;
            free(currentNode);
            return temp;
        }

        //  node with two children:
        //  Get sucessor - (smallest in the right subtree)
        node *temp = minValueNode(currentNode->right);

        //  Copy the sucessor's data to currentNode
        currentNode->data = temp->data;

        //  Delete the sucessor node
        currentNode->right = delete(currentNode->right, temp->data);
        }

        int balance = balanceFactor(currentNode);
        currentNode = balanceAfterDelete(currentNode, balance);
        return currentNode;
    }

    int empty(node *root) {
    if (root  == NULL) {
        printf("\n WARN: Empty Tree");
        return 1;
    }
    return 0;
}

    void clear(node *root) {
        node *currentNode = root;

        if (currentNode != NULL) {
            clear(currentNode->left);
            clear(currentNode->right);
        }
        free(currentNode);

        return;
    }

    void print(node *root, int level) {
        node *currentNode = root;

        if(currentNode != NULL) {

            //1. Print the current node and all its children from left to right
            printf("\n LEVEL: %d - %d", level, currentNode->data);

            //2. All children recieves its parents level + 1, represents his depht level on the tree
            print(currentNode->left, level + 1);
            print(currentNode->right, level + 1);
        }

        return;
}

int menu() {

    int option = 0;

    do {
        printf("=====================================\n");
        printf("|               MENU                |\n");
        printf("=====================================\n");
        printf("| 1 - Insert                        |\n");
        printf("| 2 - Remove                        |\n");
        printf("| 3 - Print Elements                |\n");
        printf("| 4 - Clear List                    |\n");
        printf("| 5 - Exit                          |\n");
        printf("=====================================\n");
        printf("Escolha sua opção: ");
        scanf("%d", &option);
    }while (option < 1 || option > 5);
    getchar();
    return option;
}

int main(void) {

    node *root;
    int data;

    root = NULL;

    while(1) {
        int option = menu();
        switch (option) {
            case 1:
                printf("\nINSERT: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                if (empty(root) == 0) {
                    printf("\nREMOVE: ");
                    scanf("%d", &data);
                    root = delete(root, data);
                }
                break;
            case 3:
                if(empty(root) == 0) {
                    print(root, 1);
                }
                break;
            case 4:
                clear(root);
                root == NULL;
                break;
            case 5:
                clear(root);
                exit(0);
                break;
        }
    }
    return 0;
}
