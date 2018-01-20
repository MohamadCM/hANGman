#include <stdio.h>
#include <stdlib.h>
#define max 50
struct node{
    char data[max];
    struct node* next;
};
struct node* createNode(char data[max]){
    struct node *newnode = malloc(sizeof(struct node));
    int i=0;
    for(i=0;i<max;i++)
        newnode->data[i] = data[i];
    newnode->next = NULL;
    return newnode;
}
struct node* deleteFront(struct node* oldList)
{
    struct node* list;
    list=oldList->next;
    free(oldList);
    return list;
}
void printList(struct node *list)
{
    struct node * current;
    for(current=list;current!=NULL;current=current->next)
        printf("%s\n",current->data);
}
void deleteNode(struct node * before)
{
    struct node * current=before->next;
    before->next=before->next->next;
    free(current);
}
void deletEnd(struct node *list)
{
    struct node * current=list;
    while(current->next->next!=NULL)
        current=current->next;
    free(current->next);
    current->next=NULL;
}
