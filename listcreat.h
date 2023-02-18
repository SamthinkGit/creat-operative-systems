#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// ------- Constants --------
enum {
	MAX_COLOR_CHARACTERS = 15,
	MAX_SPECIE = 30,
};

// ------- Structs --------
struct Creat {
	long long identificador;
	char color[MAX_COLOR_CHARACTERS];
	char especie[MAX_SPECIE];
	int altura;
	int peso;
	struct Creat *next;
	struct Creat *previous;
};
typedef struct Creat Creat;

struct List {

	Creat *begin;
	Creat *end;
	int numCreates;

};
typedef struct List List;

struct Queue {
	List *list;
};
typedef struct Queue Queue;

// ------- Functions & Methods --------
void initializeCreat(Creat *creat);
void printCreat(Creat *creat);

List *newList();
int isEmpty(List *list);
void setHead(List *list, Creat *creat);
void setTail(List *list, Creat *creat);
Creat *getCreat(List *list, long long id);
void push_back(List *list, Creat *creat);
void push(List *list, Creat *creat);
void pop(List *list, Creat *creat);
void printList(List *list);
int getNumberOfElements(List *list);
void deleteList(List *list);

Queue *newQueue();
void printQueue(Queue *queue);
void enqueue(Queue *queue, Creat *creat);
Creat *dequeue(Queue *queue);
void deleteQueue(Queue *queue);
