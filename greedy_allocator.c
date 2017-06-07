#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//TODO refactor const ints

const int MAX_CONTAINER_COUNT = 20;
const int MAX_CONTAINER_WEIGHT = 15;
const int MAX_CONTAINER_VALUE = 1000;
const int MAX_TOTAL_WEIGHT = 120;

struct container {
    float value;
    float weight;
};

typedef struct container container_t;


container_t generate_container(float value, float weight){

    container_t new_container;
    new_container.value = value;
    new_container.weight = weight;

    return new_container;
}

float generate_float_under(int upper_bound){
    //(random float[0,1] * random integer [0, upper bound] generates random float[0, upperbound])
    return ((float)rand() / (float)RAND_MAX) * ((float)(rand()%upper_bound));
}

bool is_full(container_t container_ship[]){

    float total_weight = 0;
    float total_count = 0;

    //sum up weight of ships containers
    for(int i = 0; i < 100; i++){
        if(container_ship[i] != NULL){
            total_weight += container_ship[i].weight;
            total_count += 1;
        }
    }


    return total_weight >= MAX_TOTAL_WEIGHT || total_count >= MAX_CONTAINER_COUNT;
}

float relative_worth(container_t container){

    if(container!= NULL){
        return container.value / container.weight;
    }

    perror("relative worth");
    exit(EXIT_FAILURE);
}

void print_containers(container_t container_array[], int length){
    for(int i = 0; i < length; i++){
        if(container_array[i] != NULL){
            printf("value: %f      weight: %f    relative_worth: %f\n", container_array[i].value, container_array[i].weight, relative_worth(container_array[i]));
        }
    }

    return;
}

int main(int argc, char const *argv[]) {

    container_t container_array[MAX_CONTAINER_COUNT];
    for(int i = 0; i < MAX_CONTAINER_COUNT; i++){
        //generate container with randomized value/weight according to the constants.
        container_array[i] = generate_container(generate_float_under(MAX_CONTAINER_VALUE), generate_float_under(MAX_CONTAINER_WEIGHT));
    }

    printf("containers at dock:\n");
    print_containers(container_array[], MAX_CONTAINER_COUNT);

    //SHIP

    //could hold 100 containers with combined weight < MAX_TOTAL_WEIGHT
    container_t container_ship[100];
    int ship_index = 0;

    while(!is_full(container_ship)){

        container_t best_choice_container = NULL;
        //pick container with highest relative worth among container_array.
        for(int i = 0; i < MAX_CONTAINER_COUNT; i++){
            //works thanks to short circuit eval in case of best_choice_container == NULL
            if(best_choice_container == NULL || relative_worth(container_array[i]) > relative_worth(container_array[i])){
                best_choice_container = container_array[i];
            }
        }

        container_ship[ship_index++] = best_choice_container;

    }

    print_containers(container_ship, 100);

    return EXIT_SUCCESS;
}
