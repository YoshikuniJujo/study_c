#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "listLib.h"

struct list* quickSort(struct list* lst);

void initRandom() { srand(time(NULL)); }
int getRandom() { return rand() % 6 + 1; }
void printInt(int n) { printf("%d ", n); }

int
main(int argc, char *argv[])
{
	struct list *randomList = makeList(initRandom, getRandom, 10);

	foreach(printInt, randomList);
	printf("\n");

	foreach(printInt, quickSort(randomList));
	printf("\n");

	return 0;
}

int large(int n, int x) { return x > n; }
int notLarge(int n, int x) { return x <= n; }

struct list*
quickSort(struct list* lst)
{
	if (empty(lst)) return lst;

	int h = lst->head->value;
	struct list *t = tail(lst);

	struct list *nl = quickSort(filter(notLarge, h, t));
	struct list *l = quickSort(filter(large, h, t));

	concat(nl, single(h));
	concat(nl, l);

	return nl;
}
