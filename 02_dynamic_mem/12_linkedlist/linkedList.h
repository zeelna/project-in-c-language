/**
 * File:        linkedList.h
 * Author:      Frank Christopher Kirch
 * Created:     12.04.2024
 * Modified:    30.05.2026
 *
 * Description: Header for the linked list lab task
 */
#ifndef LINKED_LIST_LAB_TASK
#define LINKED_LIST_LAB_TASK

#define MAX_STR 64

//~ #define DEBUG 1

typedef struct node
{
    int id;
    char *name;
    struct node *pNext;
} list;

int GetInput(void);
void PrintList(list *pHead);
bool isListEmpty(list *pHead);


void PrintNode(list *pNode);
struct node *CreateNode(char *name);
void InsertNode(list **pHead, struct node *pNode);  
void Unload(list *pHead);
struct node *FindNodeByName(list *pHead, char *name);
struct node *FindNodeByID(list *pHead, int id);


int AskId(void);
char *AskName(char str[MAX_STR], int len);

unsigned GetSequence(void);
void SafeFree(void **p);
char *AllocateString(size_t n);
void DebugString(char str[]);


void RemoveNodeByID(list **pHead, int id);
void RemoveNodeByName(list **pHead, char *name);

#endif
