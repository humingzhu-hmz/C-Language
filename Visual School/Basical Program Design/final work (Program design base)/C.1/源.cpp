//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//typedef struct s
//{
//	int data;
//	struct s* next;
//} node;
//node* creat()
//{
//	FILE* fp;
//	fp = fopen("data.txt", "r");
//	node*tail,* head, * p;
//	tail = head = (node*)malloc(sizeof(node));
//	head->next = NULL;
//	while (!feof(fp))
//	{
//		p = (node*)malloc(sizeof(node));
//		fscanf(fp, "%d", &p->data);
//		tail->next = p;
//		tail = p;
//		p->next = NULL;
//	}
//	return head;
//}
//void view(node* head)
//{
//	node* p;
//	p = head->next;
//	while (p != NULL)
//	{
//		printf("%d", p->data);
//		p = p->next;
//	}
//}
//
//int insert(node* head, int pos, int key)
//{
//	node* p;
//	int count = 0;
//	p = head->next;
//
//	while (count < pos && p != NULL)
//	{
//		count++;
//		p = p->next;
//	}
//	if (count == pos)
//	{
//		node* q;
//		q = (node*)malloc(sizeof(node));
//		q->data = key;
//		q->next = p->next;
//		p->next = q;
//		return 1;
//	}
//	return 0;
//}
//int main()
//{
//	node* head;
//	head = creat();
//	view(head);
//	insert(head, 5, 80);
//	view(head);
//	node* temp = head;
//	while (head)
//	{
//		head = head->next;
//		free(temp);
//		temp = head;
//	}
//	return 0;
//}