struct list {
	struct elem *head;
	struct elem *last;
};

struct elem {
	int value;
	struct elem *next;
};
