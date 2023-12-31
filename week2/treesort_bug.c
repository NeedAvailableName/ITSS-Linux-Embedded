#include <stdio.h>
#include <stdlib.h>

struct node {
  int           value;
  struct node*  left;
  struct node*  right;
};

void AddTree(struct node**, int);
void WalkTree(struct node*);
void FreeTree(struct node*);

/* Tree sort */
int main(void)
{
  struct node* rootp = NULL; // 0x1
  int i;
  int array[15] = {50, 12, 18, 70, 41, 19, 91, 1, 7, 6, 81, 65, 55, 20, 0};
  
  for (i = 0; i < 15; i++) {
    AddTree(&rootp, array[i]);
  }
  
  WalkTree(rootp);
  printf("\n");

  FreeTree(rootp);
  
  return 0;
}

void AddTree(struct node** pp, int val)
{
  /* create new node if *p is null */
  if (*pp == (struct node *)0) {
    *pp = (struct node *)malloc(sizeof(struct node));
    (*pp)->value = val;
  }
  else if ((*pp)->value > val) {
    AddTree(&(*pp)->left, val);
  }
  else if ((*pp)->value < val) {
    AddTree(&(*pp)->right, val);
  }
  /* (*pp)->value == val */
  else {
    /* do nothing */
  }
}

void WalkTree(struct node* p)
{
  if(p->left != NULL) {
    WalkTree(p->left);
  }
  if(p != NULL)
    printf("%d ", p->value);
  if(p->right != NULL) {
    WalkTree(p->right);
  }
}

void FreeTree(struct node* p)
{
  if(p->left != NULL) {
    FreeTree(p->left);
  }
  if(p->right != NULL) {
    FreeTree(p->right);
  }
  if(p != NULL) {
    free(p);
  }
  return;
}