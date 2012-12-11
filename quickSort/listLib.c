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

int
empty(struct list *lst)
{
	if (lst->head == NULL && lst->last == NULL) return 1;
	if (lst->head != NULL && lst->last != NULL) return 0;
	printf("bad list\n");
	exit(1);
}

struct elem*
unshiftElem(int n, struct elem* es)
{
	struct elem *new = calloc(1, sizeof(struct elem*));
	new->value = n;
	new->next = es;
	return new;
}

void
unshiftList(int n, struct list* lst)
{
	struct elem *new = unshiftElem(n, lst->head);
	if (empty(lst)) lst->last = new;
	lst->head = new;
}

void
pushList(int n, struct list* lst)
{
	struct elem *new = unshiftElem(n, NULL);
	if (empty(lst)) lst->head = new;
	else lst->last->next = new;
	lst->last = new;
}

struct list*
tail(struct list* lst)
{
	struct list* new = newList();
	new->head = lst->head->next;
	if (new->head != NULL) new->last = lst->last;
	return new;
}

struct list*
single(int n)
{
	struct list *lst = newList();
	unshiftList(n, lst);
	return lst;
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
concat(struct list* lst1, struct list* lst2)
{
	if (empty(lst1)) { *lst1 = *lst2; return; }
	if (empty(lst2)) return;
	lst1->last->next = lst2->head;
	lst1->last = lst2->last;
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
