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

    //Data inserted is greater than parent right node data, and right node height is more then 1
    if (balance < -1 && data > currentNode->right->data)
        return leftRotate(currentNode);

    //Data inserted is less than parent left node data, and left node height is more than 1
    if (balance > 1 && data < currentNode->left->data)
        return rightRotate(currentNode);

    //Data inserted is greater than parent left node data, and right node height is more than 1
    if (balance > 1 && data > currentNode->left->data) {
        currentNode->left = leftRotate(currentNode->left);
        return rightRotate(currentNode);
    }

    //Data inserted is less than parent right node data, and right node height is more than 1
    if (balance < -1 && data < currentNode->right->data) {
        currentNode->right = rightRotate(currentNode->right);
        return leftRotate(currentNode);
    }

    //If node is balanced, no need balance
    return currentNode;


}

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
