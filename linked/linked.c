#include <stdio.h>
#include <stdlib.h>

struct node { int i; struct node *next; };

void print_list(struct node *head){
    while(head){
        printf("%d\n", head->i);
        head = head->next;
    }
    return;
}

struct node * insert_front(struct node *current, int value){
    struct node * to_add = malloc(sizeof(struct node));
    to_add -> i = value;
    to_add -> next = current;
    return to_add;
}

struct node * free_list(struct node *head){

    struct node * temp = head;
    struct node * current = head;
    while(current){
        current = current->next;
        free(temp);
        temp = current;
    }
    return head;

}

// int main(){
    
    // struct node *tail = malloc(sizeof(struct node)); 
    // tail->i = 1212312312;
    // tail->next = NULL;
    // struct node * next = insert_front(tail, 6);
    // struct node * next_next = insert_front(next, 123);

    // print_list(tail);

    // free_list(tail);

    // print_list(tail);

//     return 0;
// }



