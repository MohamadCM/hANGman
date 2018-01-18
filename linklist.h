#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED
#define max 50
struct node{
    char data[max];
    struct node* next;
};
struct node* createNode(char data[max]);
struct node* deleteFront(struct node* oldList);
void deleteNode(struct node * before);
void printList(struct node *list);
void deleteNode(struct node * before);
#endif // LINKLIST_H_INCLUDED
