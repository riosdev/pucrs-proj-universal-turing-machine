#include "T1_RafaelRios.h"
#include "stdlib.h"

void push(List * q, char* t){
    Node* node = malloc(sizeof(Node));
    node->next = NULL;
    node->valor = t;
    if(q->head == NULL){
        q->head = node;
    }
    else{
        Node *aux = q->tail;
        aux->next = node;
    }
    q->tail = node;
}

char *pop(List *q){
    Node *node = NULL;
    if(q->head != NULL){
        node = q->head;
        q->head = node->next;
        return node->valor;
    }
    return NULL;
}

char *peek(List q){
    return q.head != NULL ? q.head->valor : NULL;
}

int size(List* q){
    int i = 0; 
    Node *n = q->head;
    while(n != NULL){
        n = n->next;
        i++;
    }
    return i;
}

void clear(List* q){
    Node *n = q->head;
    while(n != NULL){
        Node *aux = n->next;
        free(n);
        n = aux;
    }
}

void tpush(TList * q, Transicao* t){
    TNode* node = malloc(sizeof(TNode));
    node->next = NULL;
    node->transicao = t;
    if(q->head == NULL){
        q->head = node;
    }
    else{
        TNode *aux = q->tail;
        aux->next = node;
    }
    q->tail = node;
}

Transicao *tpop(TList *q){
    TNode *node = NULL;
    if(q->head != NULL){
        node = q->head;
        q->head = node->next;
        return node->transicao;
    }
    return NULL;
}

Transicao *tpeek(TList q){
    return q.head != NULL ? q.head->transicao : NULL;
}

int tsize(TList* q){
    int i = 0; 
    TNode *n = q->head;
    while(n != NULL){
        n = n->next;
        i++;
    }
    return i;
}