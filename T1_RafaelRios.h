#ifndef T1_HEADER
#define T1_HEADER
#include "stdio.h"

typedef struct Transicao{
    char * e_in;
    char * e_out;
    char * entrada;
    char * saida;
    char * movimento;
} Transicao;

typedef struct Node{
    char *valor;
    struct Node *next;
} Node;

typedef struct {
    Node *head, *tail;
} List;

typedef struct TNode{
    Transicao *transicao;
    struct TNode *next;
} TNode;

typedef struct {
    TNode *head, *tail;
} TList;

//List
void push(List * q, char *t);
char *pop(List *q);
char *peek(List q);
int size(List *q);
void clear(List *q);
int find(List *q, char *t);
//TList
void tpush(TList * q, Transicao *t);
Transicao *tpop(TList *q);
Transicao *tpeek(TList q);
int tsize(TList *q);
//Main
void init_transition(Transicao *, char *, char *, char *, char *, char *);
void parse_machine(FILE* fd);
void parse_input();
void exec(int step);
void codificar();
void decodificar();

#endif