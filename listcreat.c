#include "listcreat.h"

// ------- Creat Functions --------
void
initializeCreat(Creat * creat)
{
	creat->identificador = 0;
	strcpy(creat->color, "UNKNOWN");
	strcpy(creat->especie, "UNKNOWN");
	creat->altura = 0;
	creat->peso = 0;
	creat->next = NULL;
	creat->previous = NULL;
}

void
printCreat(Creat * creat)
{
	printf("[\t%lld\t%s\t%s\t%dg\t%dmm\t]",
	       creat->identificador,
	       creat->color, creat->especie, creat->peso, creat->altura);
}

// ------- List Functions --------
List *
newList()
{
	List *list = (List *) malloc(sizeof(List));

	list->begin = NULL;
	list->end = NULL;
	list->numCreates = 0;
	return list;
}

int
isEmpty(List * list)
{
	// Note that numCreates will return 0 (true) if empty
	return list->numCreates;
}

// [WARNING] Setting the head of the list will break the
// linkage with previous nodes.
void
setHead(List * list, Creat * creat)
{
	creat->previous->next = NULL;
	creat->previous = NULL;
	list->begin = creat;

	// Recalculating number of items
	list->numCreates = 0;
	Creat *iterator;

	for (iterator = list->begin; iterator != NULL;
	     iterator = iterator->next) {
		list->numCreates++;
	}
}

// [WARNING] Setting the tail of the list will break the
// linkage with following nodes.
void
setTail(List * list, Creat * creat)
{
	creat->next->previous = NULL;
	creat->next = NULL;
	list->end = creat;

	// Recalculating number of items
	list->numCreates = 0;
	Creat *iterator;

	for (iterator = list->begin; iterator != NULL;
	     iterator = iterator->next) {
		list->numCreates++;
	}
}

Creat *
getCreat(List * list, long long id)
{
	int numberOfCoincidences = 0;
	Creat *returnCreat;
	Creat *iterator;

	for (iterator = list->begin; iterator != NULL;
	     iterator = iterator->next) {
		if (iterator->identificador == id) {
			numberOfCoincidences++;
			returnCreat = iterator;
		}
	}

	if (numberOfCoincidences == 0) {
		fprintf(stderr,
			"[WARNING] Trying to getCreat() failed finding the pointer.\n");
		return NULL;
	}
	if (numberOfCoincidences > 1) {
		fprintf(stderr,
			"[WARNING] Trying to getCreat() failed. Multiple coincidences found.\n");
		return NULL;
	}
	printf("C: %d", numberOfCoincidences);
	return returnCreat;
}

void
push_back(List * list, Creat * creat)
{
	// Checking if the creat is already in a list. If so,
	// then abort the assignment
	if (creat->next != NULL || creat->previous != NULL) {
		fprintf(stderr,
			"[WARNING] Trying to push_back() a Creat already in a list. Skip.\n");
		return;
	}

	if (list->numCreates == 0) {
		list->begin = creat;
		list->end = creat;

	} else {
		creat->previous = list->end;
		list->end->next = creat;
		list->end = creat;
	}

	list->numCreates++;
}

void
push(List * list, Creat * creat)
{

	// Checking if the creat is already in a list. If so,
	// then abort the assignment
	if (creat->next != NULL || creat->previous != NULL) {
		fprintf(stderr,
			"[WARNING] Trying to push() a Creat already in a list. Skip.\n");
		return;
	}

	if (list->numCreates == 0) {
		list->begin = creat;
		list->end = creat;

	} else {
		creat->next = list->begin;
		list->begin->previous = creat;
		list->begin = creat;
	}
	list->numCreates++;
}

void
printList(List * list)
{

	printf("\t\tID\tColor\tEspecie\tPeso\tAltura\t\n");
	Creat *iterator;
	int index = 0;

	for (iterator = list->begin; iterator != NULL;
	     iterator = iterator->next) {
		printf("%d:\t", index++);
		printCreat(iterator);
		printf("\n");
	}
}

void
pop(List * list, Creat * creat)
{

	// Check if the creat is valid
	if (creat->previous == NULL && creat->next == NULL
	    && list->numCreates > 1) {
		fprintf(stderr,
			"[WARNING] Trying to pop() a creat that is not inside a list.\n");
		return;
	}

	list->numCreates--;

	// Case: The popped creat is the last one
	if (list->begin == list->end) {
		creat->next = NULL;
		creat->previous = NULL;
		list->begin = NULL;
		list->end = NULL;
		return;
	}
	// Case: The creat is at the beginning
	if (creat == list->begin) {
		list->begin = creat->next;
		creat->next->previous = NULL;
		creat->next = NULL;
		creat->previous = NULL;
		return;
	}
	// Case: The creat is at the end
	if (creat == list->end) {
		list->end = creat->previous;
		creat->previous->next = NULL;
		creat->next = NULL;
		creat->previous = NULL;
		return;
	}
	// Default: The creat is between two nodes
	creat->next->previous = creat->previous;
	creat->previous->next = creat->next;
	creat->next = NULL;
	creat->previous = NULL;
}

int
getNumberOfElements(List * list)
{
	return list->numCreates;
}

void
deleteList(List * list)
{
	while (list->begin != list->end) {
		pop(list, list->begin);
	}

	free(list);
}

Queue *
newQueue()
{
	Queue *queue = (Queue *) malloc(sizeof(Queue));

	queue->list = newList();
	return queue;
}

void
printQueue(Queue * queue)
{
	printList(queue->list);
}

void
enqueue(Queue * queue, Creat * creat)
{
	push_back(queue->list, creat);
}

Creat *
dequeue(Queue * queue)
{
	Creat *creat;

	if (queue->list->numCreates <= 0) {
		fprintf(stderr,
			"[WARNING] Trying to dequeue() failed, queue was already empty.\n");
		return NULL;
	}

	creat = queue->list->begin;
	pop(queue->list, creat);

	return creat;
}

void
deleteQueue(Queue * queue)
{
	deleteList(queue->list);
	free(queue);
}
