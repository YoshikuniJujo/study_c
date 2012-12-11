struct list {
	struct elem *head;
	struct elem *last;
};

struct elem {
	int value;
	struct elem *next;
};

struct list* makeList(void init(), int fun(), int len);
struct list* single(int n);
void concat(struct list* lst1, struct list* lst2);
struct list* tail(struct list* lst);

int empty(struct list *lst);

void foreach(void fun(int), struct list* lst);
struct list* filter(int p(int, int), int, struct list* lst);
