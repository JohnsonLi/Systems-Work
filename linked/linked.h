struct node { int i; struct node *next; };
void print_list(struct node *head);
struct node * insert_front(struct node *current, int value);
struct node * free_list(struct node *head);