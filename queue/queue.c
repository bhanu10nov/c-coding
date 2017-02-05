/**
 * @file    queue.c
 * @author  Bhanu Jha(bhanujha@gmail.com)
 * @brief   server code depicting simple queue
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int array[100];
int tail = 0;

struct linklist {
	int data;
	struct linklist *addr;
};

struct linklist *front = NULL;
struct linklist *rear = NULL;

void queue_en()
{
	int element = 0;
	if (tail >= 100) {
		fprintf(stdout, "The queue limit\n");
	} else {
		fprintf(stdout, "Enter the element:");
		scanf("%d", &element);
		array[tail] = element;
		tail++;
	}
}
void queue_de()
{
	int i = 0;
	if (tail <= 0) {
		fprintf(stdout, "The queue is empty\n");
	} else {
		fprintf(stdout, "Element : %d\n", array[0]);
		while (i < tail) {
			array[i] = array[i+1];
			i++;
		}
		tail--;
	}
}
void arrayimp()
{
	int choice = 0;
	fprintf(stdout, "This is a queue program\n");
	while (choice != 3) {
		fprintf(stdout, "1. En-Queue\n");
		fprintf(stdout, "2. De-Queue\n");
		fprintf(stdout, "3. Exit\n");
		fprintf(stdout, "Please Enter your choice :");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			queue_en();
			break;
		case 2:
			queue_de();
			break;
		case 3:
			break;
		default:
			fprintf(stdout, "Invalid choice\n");
			break;

		}
	}
}
void listqueue_en()
{
	struct linklist *tmp = (struct linklist*)malloc(sizeof(struct linklist*));
	if (tmp == NULL) {
		fprintf(stdout, "Memory is not available\n");
		return;
	}
	tmp->addr = NULL;
	fprintf(stdout, "Enter the data : \n");
	scanf("%d",&tmp->data);
	if  (front == NULL) {
		front = (struct linklist*)malloc(sizeof(struct linklist*));
		if (front == NULL) {
			fprintf(stdout, "Memory is not available\n");
		} else {
			front = rear = tmp;
		}
	} else {
		rear->addr = tmp;
		rear = tmp;
	}
}
void displaylist()
{
	struct linklist *tmp = front;
	while (tmp != NULL) {
		fprintf(stdout, "Data : %d\n",tmp->data);
		tmp = tmp->addr;
	}
}
void listqueue_de()
{
	struct linklist *tmp = NULL;
	if (front == NULL) {
		fprintf(stdout, "No Element in the list\n");
	} else {
		fprintf (stdout, "Queue Element : %d\n",front->data);
		tmp = front;
		front = tmp->addr;
		free(tmp);
		tmp = NULL;
	}
}
void linklistimp()
{
	int choice = 0;
	fprintf(stdout, "This is a queue program\n");
	while (choice != 4) {
		fprintf(stdout, "1. En-Queue\n");
		fprintf(stdout, "2. De-Queue\n");
		fprintf(stdout, "3. Display List\n");
		fprintf(stdout, "4. Exit\n");
		fprintf(stdout, "Please Enter your choice :");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			listqueue_en();
			break;
		case 2:
			listqueue_de();
			break;
		case 3:
			displaylist();
			break;
		case 4:
			break;
		default:
			fprintf(stdout, "Invalid choice\n");
			break;

		}
	}
}

int main()
{
	int choice = 0;
	fprintf(stdout, "1. Array  2.LinkList\n");
	fprintf(stdout, "Enter your choice : ");
	scanf("%d", &choice);
	switch(choice) {
	case 1:
		arrayimp();
		break;
	case 2:
		linklistimp();
		break;
	default:
		fprintf(stdout, "Wrong choice\n");
		break;
	}
	return 0;
}
