#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct mcdonalds {char *state; int locations;};



char * print_struct(struct mcdonalds name){
    printf("State: %s\n", name.state);
    printf("Number of Locations: %d\n", name.locations);
}

struct mcdonalds make_struct(char *state, int num_locations){
    struct mcdonalds x;
    x.state = state;
    x.locations = num_locations;
    return x;
}

struct mcdonalds modify_struct_state(struct mcdonalds s, char * state){
    s.state = state;
    return s;
}
struct mcdonalds modify_struct_num_locations(struct mcdonalds s, int num_locations){
    s.locations = num_locations;
    return s;
}


int main(){

    srand(time(NULL));

    char states[5][3] = {
        "NY", "NJ", "CA", "PA", "TX"
    };

    int num_locations[5] = {
        767, 311, 1492, 583, 1224
    };

    int r = rand() % 5;
    struct mcdonalds current_struct = make_struct(states[r], num_locations[r]);

    printf("current struct:\n");
    print_struct(current_struct);
    printf("\n");

    printf("changing the state to MA:\n");
    current_struct = modify_struct_state(current_struct, "MA");
    print_struct(current_struct);
    printf("\n");

    printf("changing the number of locations to 423423:\n");
    current_struct = modify_struct_num_locations(current_struct, 423423);
    print_struct(current_struct);
    printf("-----------------------------------------\n");

    r = rand() % 5;
    current_struct = make_struct(states[r], num_locations[r]);

    printf("another struct (run again if it's the same):\n");
    print_struct(current_struct);
    printf("\n");

    printf("changing the state to MA:\n");
    current_struct = modify_struct_state(current_struct, "MA");
    print_struct(current_struct);
    printf("\n");

    printf("changing the number of locations to 423423:\n");
    current_struct = modify_struct_num_locations(current_struct, 423423);
    print_struct(current_struct);

    return 0;
}