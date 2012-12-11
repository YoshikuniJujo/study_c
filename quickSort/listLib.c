#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "listLib.h"

struct list* newList();
void printList(struct list* lst);
void unshiftList(int n, struct list* lst);
void pushList(int n, struct list* lst);
void concatList(struct list* lst1, struct list* lst2);
struct list* arrayToList(int *array, int size);
struct list* makeRandomList(int max, int len);
struct list* larges(int n, struct list* lst);
struct list* notLarges(int n, struct list* lst);
struct list* tail(struct list* lst);
struct list* single(int n);
struct list* quickSort(struct list* lst);
int isEmptyList(struct list *lst);

int
main(int argc, char *argv[])
{
	int array[] = {8, 9, 10, 11};
	struct list *test = NULL, *test2 = NULL;
	struct list *randomList = makeRandomList(6, 10);

	test = newList();
	unshiftList(5, test);
	pushList(6, test);
	unshiftList(4, test);
	unshiftList(3, test);
	pushList(7, test);
//	printList(test);

	test2 = arrayToList(array, 4);
//	printList(test2);

	concatList(test, test2);
//	printList(test);

	printList(randomList);
//	printList(larges(3, randomList));
//	printList(notLarges(3, randomList));

	printList(quickSort(randomList));

	return 0;
}

struct list*
quickSort(struct list* lst)
{
	if (isEmptyList(lst)) return lst;
	int h = lst->head->value;
	struct list *t = tail(lst);
	struct list *nl = notLarges(h, t);
	struct list *l = larges(h, t);

	struct list *snl = quickSort(nl);
	struct list *sl = quickSort(l);

	concatList(snl, single(h));
	concatList(snl, sl);

	return snl;
}

struct list*
newList()
{
	struct list *new = NULL;
	new = calloc(1, sizeof(struct list*));
	new->head = NULL;
	new->last = NULL;
	return new;
}

struct elem*
unshiftElem(int n, struct elem* es)
{
	struct elem *e = calloc(1, sizeof(struct elem*));
	e->value = n;
	e->next = es;
	return e;
}

void
unshiftList(int n, struct list* lst)
{
	struct elem *e = unshiftElem(n, lst->head);
	lst->head = e;
	if (lst->last == NULL) lst->last = e;
}

void
pushList(int n, struct list* lst)
{
	if (lst->last == NULL) {
		lst->head = unshiftElem(n, NULL);
		lst->last = lst->head;
	} else {
		lst->last->next = unshiftElem(n, NULL);
		lst->last = lst->last->next;
	}
}

void
printElems(struct elem* es)
{
	if (es == NULL) {
		printf("\n");
		return;
	}
	printf("%d ", es->value);
	printElems(es->next);
}

void
printList(struct list* lst)
{
	printElems(lst->head);
}

struct list*
single(int n)
{
	struct list *lst = newList();
	unshiftList(n, lst);
	return lst;
}

void
concatList(struct list* lst1, struct list* lst2)
{
	if (isEmptyList(lst1)) {
		lst1->head = lst2->head;
		lst1->last = lst2->last;
		return;
	}
	if (isEmptyList(lst2)) return;
	lst1->last->next = lst2->head;
	lst1->last = lst2->last;
}

struct list*
arrayToList(int *array, int size)
{
	struct list* lst = newList();
	int i;
	for (i = 0; i < size; i++) pushList(array[i], lst);
	return lst;
}

int
isEmptyList(struct list *lst)
{
	if (lst->head == NULL && lst->last == NULL) return 1;
	if (lst->head != NULL && lst->last != NULL) return 0;
	printf("bad list\n");
	exit(1);
}

struct list*
tail(struct list* lst)
{
	struct list* new = newList();
	new->head = lst->head->next;
	if (lst->head->next != NULL) new->last = lst->last;
	return new;
}

struct list*
larges(int n, struct list* lst)
{
	if (isEmptyList(lst)) return newList();
	if (lst->head->value > n) {
		struct list *new = larges(n, tail(lst));
		unshiftList(lst->head->value, new);
		return new;
	}
	return larges(n, tail(lst));
}

struct list*
notLarges(int n, struct list* lst)
{
	if (isEmptyList(lst)) return newList();
	if (lst->head->value > n) return notLarges(n, tail(lst));
	struct list *new = notLarges(n, tail(lst));
	unshiftList(lst->head->value, new);
	return new;
}

struct list*
makeRandomList(int max, int len)
{
	struct list* lst = newList();
	int i = 0;

	srand(time(NULL));
	for (i = 0; i < len; i++) pushList(rand() % max + 1, lst);

	return lst;
}
