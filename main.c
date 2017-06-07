/********************************************************
* Project: Salesman Tracing
* Code by: danielncs
* Version: 0.0.1
********************************************************/

#define PVERSION "0.0.1"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib\environment.h"

int main(){
    #ifdef DEBUG
        /* Prints project header if DEBUG is enabled. */
        fprintf(stdout, "Project: Salesman Tracing\nCode by: danielncs\nVersion: ");
        fprintf(stdout, PVERSION);
        fprintf(stdout, "\n\n");
    #endif // DEBUG

    /* Creates the labels' array of string */
    char **nodes = malloc(3 * sizeof(char *));
    for (int i=0; i < 3; i++) nodes[i] = malloc(30 * sizeof(char));
    strncpy(nodes[0],  "Florianopolis, SC, Brasil", 30);
    strncpy(nodes[1],  "Joinville, SC, Brasil", 30);
    strncpy(nodes[2],  "Chapeco, SC, Brasil", 30);

    /* Builds environment handle with environment lib. */
    environment_t environment = environment_build(nodes, 3);
    if(environment == NULL){
        fprintf(stderr, "Couldn't build environment.");
        return EXIT_FAILURE;
    }

    /* Destroys previously built environment freeing allocated memory. */
    environment_destroy(environment, 3);

    /* Frees allocated labels' array. */
    for (int i=0; i < 3; i++) free(nodes[i]);
    free(nodes);

    return EXIT_SUCCESS;
}
