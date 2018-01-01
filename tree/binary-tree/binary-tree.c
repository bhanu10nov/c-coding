/*
 * @file binary-tree.c
 *
 * @brief The file implements binary search tree for faster operations.
 *
 * @author Bhanu Jha (bhanujha@gmail.com)
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum bTreeReturn_e {
	SUCCESS = 0,
	FAILURE = 1,
	LAST
} bTreeReturn;

typedef struct bTreeNode_s {
	struct bTreeNode_s *left;
	struct bTreeNode_s *right;
	int data;
} bTreeNode;

bTreeNode* insert(int data, bTreeNode *node)
{
	bTreeReturn ret = FAILURE;
	if (NULL == node) {
		/* Allocate root */
		node = (bTreeNode *)malloc(sizeof(bTreeNode));
		if (NULL == node) {
			fprintf(stderr, "Allocation Failed\n");
		} else {
			node->left = NULL;
			node->right = NULL;
			node->data = data;
		}
	} else {
		if (node->data > data) {
			node->left = insert(data, node->left);
		} else {
			node->right = insert(data, node->right);
		}
	}
	return node;
}

void search(bTreeNode *root, int searchItem)
{
	if (NULL == root) {
		fprintf(stderr, "Search Item not found\n");
	} else if (root->data > searchItem) {
		search(root->left, searchItem);
	} else if (root->data < searchItem) {
		search(root->right, searchItem);
	} else {
		fprintf(stdout, "data found\n");
	}
}

void inorder(bTreeNode *root)
{
	if (root != NULL) {
		inorder(root->left);
		printf("%d \n", root->data);
		inorder(root->right);
	}
}

int main()
{
	bTreeNode *root = NULL;
	int temp = 0;
	root = insert(50, root);
	insert(30, root);
	insert(20, root);
	insert(40, root);
	insert(70, root);
	insert(60, root);
	insert(80, root);

	inorder(root);
	fprintf(stdout, "Please enter search data :");
	scanf("%d", &temp);
	search(root, temp);
	return SUCCESS;
}
