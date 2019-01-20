#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

int main(){

    struct node *head = malloc(sizeof(struct node));
    head->i = 123;
    head->next = NULL;

    printf("head: %p value: %d\n", head, head->i);
    printf("\n");
    
    printf("adding value 444 to front of head\n");
    head = insert_front(head, 444);
    printf("head: %p value: %d\n", head, head->i);
    printf("current list:\n");
    print_list(head);

    printf("\n");

    printf("adding value 4324556 to front of head\n");
    head = insert_front(head, 4324556);
    printf("head: %p value: %d\n", head, head->i);
    printf("current list:\n");
    print_list(head);
    
    printf("\n");

    printf("freeing current list\n");
    head = free_list(head);
    printf("current list:\n");
    print_list(head);
    printf("\n");

    printf("creating a empty node:\n");
    struct node *empty = malloc(sizeof(struct node));
    printf("printing empty list:\n");
    print_list(empty);

    printf("i think random numbers means they're freed :D\n");

    return 0;
}