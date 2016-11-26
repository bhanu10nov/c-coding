#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define iprintf(...) fprintf(stdout,__VA_ARGS__)
typedef enum blinklist_result {
  SUCCESS = 0,
  FAILED = 0
}eblinklist_result;
struct blist {
  struct blist *next;
  int data;
};
int g_value1 = 0;

eblinklist_result insert(struct blist **head) 
{
  struct blist* newNode;
  struct blist* temp;
  if (*head == NULL) {
    *head = (struct blist *)malloc(sizeof(struct blist));
    (*head)->data = g_value1++;
    (*head)->next = NULL;
  } else {
    temp = *head;
    while(temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = (struct blist *)malloc(sizeof(struct blist));
    (temp->next)->data = g_value1++;
    (temp->next)->next = NULL;
  }
  return SUCCESS;
}
eblinklist_result display(struct blist *head)
{
  iprintf("%s : %d\n",__func__,__LINE__);
  iprintf("Head -->");
  while(head!=NULL)
  {
    iprintf(" %d -->",head->data);
    head = head->next;
  }
  iprintf(" NULL\n");
  return SUCCESS;
}
int main()
{
  struct blist *head = NULL;
  int choice = 0;

  while (choice != 3) {
    iprintf("1. Insert\n2. Display\n3. Exit\n");
    iprintf("Enter your choice:");
    scanf("%d",&choice);
    switch (choice)
    { 
      case 1: insert(&head); break;
      case 2: display(head); break;
      case 3: break;
      default: break;
    }
  }
  return 0;
}
