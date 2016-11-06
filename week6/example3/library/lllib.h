#include "mystring.h"

/////////////////////////////////////////////////////
typedef struct node node;
struct node
{
  elementtype element;
  node *next;
};

node *root;
node *cur;
node *prev;
/////////////////////////////////////////////////////
node *makenewnode(elementtype);
void list_reverse(node **);
void insertaffter(elementtype);
void insertbefore(elementtype);
void insertatbegining(elementtype);
void insertatend(elementtype);
node *insertatposition(node*, elementtype, int);

void deleteatbegining();
void deletecur();
void deleteatend();
void deletelist();
node *deleteatposition(node*, int);

node *searchfunc(int (*func)());
void traveser(void (*func)());
///////////////////////////////////////////////////// Linked list functions
node *makenewnode(elementtype add)
{
  node *new;
  new = (node *)malloc(sizeof(node));
  if (new == NULL)
    {
      printf("Khong cap phat duoc bo nho\n");
      return 0;
    }
  new->element = add;
  new->next = NULL;
  return new;
}

void list_reverse(node **li)
{

}
///////////////////////////////////////////////////// insert functions
void insertaffter(elementtype a)
{
  node *new;
  new = makenewnode(a);
  if (root == NULL)
    {
      root = new;
      cur = root;
    }
  else
    {
      new->next = cur->next;
      cur->next = new;
      prev = cur;
      cur = new;
    }
}

void insertbefore(elementtype a)
{
  node *new;
  new = makenewnode(a);
  if (root == NULL)
    {
      root = new;
      cur = root;
    }
  else
    {
      new->next = cur;
      if (prev != NULL) prev->next = new;
      if (cur == root) root = new;
      cur = new;
    }
}

void insertatbegining(elementtype a)
{
  node *new;
  new = makenewnode(a);
  new->next = root;
  root = new;
}

void insertatend(elementtype a)
{
  node *new;
  new = makenewnode(a);
  if (root == NULL)
    {
      root = new;
      cur = new;
    }
  else
    {
      for (cur = root; cur->next != NULL; cur = cur->next);
      prev = cur;
      cur->next = new;
    }
}

node *insertatposition(node *root1, elementtype a, int n)
{
  int i = 0;
  node *prev2;
  prev = NULL;
  for (cur=root1; cur != NULL; cur=cur->next)
    {
      if (i == n) break;
      i++;
      prev2 = prev;
      prev = cur;
    }
  if (cur == NULL)
    {
      cur = prev;
      prev = prev2;
      printf("Loi, khong co phan tu thu %d trong danh sach\n",n);
      return NULL;
    }
  insertbefore(a);
  return root;
}
///////////////////////////////////////////////////// delete functions
void deleteatbegining()
{
  node *temp;
  temp = root;
  if (root == NULL) return;
  if (cur == root) cur = root->next;
  root = root->next;
  free(temp);
}

void deleteatend()
{
  node *prev2;
  if (root == NULL) return;
  for (cur = root; cur->next != NULL; cur = cur->next)
    {
      prev2 = prev;
      prev = cur;
    }
  free(cur);
  cur = prev;
  prev = prev2;
  if (cur != NULL) cur->next = NULL;
}

void deletecur()
{
  if (root == NULL) return;
  if (cur == root) deleteatbegining();
  else
    if (cur->next == NULL) deleteatend();
    else
      {
	prev->next = cur->next;
	free(cur);
	cur = prev->next;
      }
}

void deletelist()
{
  if (root == NULL) return;
  node *temp;
  temp = root;
  while (temp != NULL)
    {
      root = root->next;
      free(temp);
      temp = root;
    }
}

node *deleteatposition(node *root1, int n)
{
  int i = 0;
  node *prev2;
  prev = NULL;
  for (cur=root1; cur != NULL; cur=cur->next)
    {
      if (i == n) break;
      i++;
      prev2 = prev;
      prev = cur;
    }
  if (cur == NULL)
    {
      cur = prev;
      prev = prev2;
      printf("Loi, khong co phan tu thu %d trong danh sach\n",n);
      return NULL;
    }
  deletecur();
  return root1;
}
///////////////////////////////////////////////////// traveser functions
void traveser(void (*func)())
{
  node *prev2;
  for (cur = root; cur != NULL; cur = cur->next)
    {
      func();
      prev2 = prev;
      prev = cur;
    }
  cur = prev;
  prev = prev2;
}
///////////////////////////////////////////////////// find functions
node *searchfunc(int (*func)())
{
  node *prev2, *temp;
  cur = root;
  prev = NULL;
  while (cur != NULL)
    {
      if(func()) break;
      prev2=prev; prev = cur;
      cur = cur->next;
    }
  temp = cur;
  if (cur == NULL)
    {
      cur = prev;
      prev = prev2;
    }
  return temp;
}
