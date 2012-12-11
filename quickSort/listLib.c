#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "listLib.h"

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

struct list*
single(int n)
{
	struct list *lst = newList();
	unshiftList(n, lst);
	return lst;
}

void
concat(struct list* lst1, struct list* lst2)
{
	if (empty(lst1)) {
		lst1->head = lst2->head;
		lst1->last = lst2->last;
		return;
	}
	if (empty(lst2)) return;
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
empty(struct list *lst)
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
filter(int p(int, int), int n, struct list* lst)
{
	if (empty(lst)) return newList();
	if (p(n, lst->head->value)) {
		struct list *new = filter(p, n, tail(lst));
		unshiftList(lst->head->value, new);
		return new;
	}
	return filter(p, n, tail(lst));
}

struct list*
makeList(void init(), int fun(), int len)
{
	struct list* lst = newList();
	int i = 0;

	init();
	for (i = 0; i < len; i++) pushList(fun(), lst);

	return lst;
}

void
foreachElems(void fun(int), struct elem* es)
{
	if (es == NULL) return;
	fun(es->value);
	foreachElems(fun, es->next);
}

void
foreach(void fun(int), struct list* lst)
{
	foreachElems(fun, lst->head);
}
