#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 */

typedef struct tnode {
  int val;
  struct tnode *left;
  struct tnode *right;
} TreeNode;

void postorderTraversal1(TreeNode* root, int* returnSize, int** array) {
  int l_size = 0;
  int r_size = 0;
  int* left_size = &l_size;
  int* right_size = &r_size;
  TreeNode *troot = root;

  // printf("node val: %d\n\n", root->val);

  if (root->left != NULL) {
    postorderTraversal1(root->left, left_size, array);
  }

  if (root->right != NULL) {
    postorderTraversal1(root->right, right_size, array);
  }

  printf("append %d to array\n", troot->val);

  **array = troot->val;
  (*array)++;

  *returnSize = *left_size + *right_size + 1;

  // printf("returnSize: %d\n", *returnSize);
}

int* postorderTraversal(TreeNode* root, int* returnSize) {
  printf("\nstart traversal\n");
  const int MAX = 10000;
  int* array = malloc(MAX * sizeof(int));
  int * array_start = array;
  int ** array_p = &array;
  if (root == NULL ) {
    *returnSize = 0;
    return array_start;
  }
  postorderTraversal1(root, returnSize, array_p);
  return array_start;
}


void add_node(TreeNode *root, int val) {
  printf("%d\n", val);
  while(1) {
    if (val < root->val) {
      printf("left %d\n", val);
      if ( root->left != NULL) {
        root = root->left;
      } else {
        TreeNode *node = malloc(sizeof(TreeNode));
        node->val  = val;
        node->left = NULL;
        node->right = NULL;
        root->left = node;
        return;
      }
    } else {
      printf("right %d\n", val);
      if (root->right != NULL) {
        printf("root -> right\n");
        root = root->right;
      } else {
        TreeNode* node = malloc(sizeof(TreeNode));
        node->val =  val;
        node->left = NULL;
        node->right = NULL;
        root->right = node;
        return;
      }
    }
  }
}

TreeNode* create_tree_node(int *array, int size) {
  TreeNode *tree = malloc(sizeof(TreeNode));
  tree->val = array[0];
  tree->left = NULL;
  tree->right = NULL;
  for(int i = 1; i < size; i++) {
    add_node(tree, array[i]);
  }
  return tree;
}

int mu_check_array(int* nums1,  int* nums2, int size) {
  for (int i = 0; i < size; i++) {
    if (*nums1++ != *nums2++) {
      return 0;
    }
  }
  return 1;
}


MU_TEST(test_check) {
  int a[] = {5,2,3,10,6,4};
  int b = 0;
  int *size = &b;

  TreeNode * tree = create_tree_node(a, 6);
  printf("\nStage2 traversal tree node");
  int* array = postorderTraversal(tree,size);
  // printf("size: %d", *sizne);
  for(int i = 0; i < *size; i++) {
    printf("%d", *array++);
  }

  int a2[] = {};
  TreeNode * t2 = create_tree_node(a2, 0);
  printf("\nStage2 traversal tree node");
  int* array2 = postorderTraversal(t2,size);
  // printf("size: %d", *sizne);
  for(int i = 0; i < *size; i++) {
    printf("%d", *array2++);
  }
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
}
