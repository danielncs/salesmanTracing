#include <stdlib.h>
#include <stdio.h>
#include "environment.h"
#include "GDM_API.h"

struct environmentStruct{
    unsigned int size;
    unsigned int ** distanceMatrix;
    char ** label;
};

environment_t environment_build(char **nodes, unsigned int nodesNumber){
    /* Allocates memory to returned environment handle. */
    environment_t environment = malloc(sizeof(struct environmentStruct));
    if(environment == NULL){
        fprintf(stderr, "Memory allocation error");
        return NULL;
    }

    /* References struct member to already allocated pointers. */
    environment->label = nodes;
    environment->size = nodesNumber;

    /* Prints DEBUG build information */
    #ifdef DEBUG
        fprintf(stdout, "Environment size: %d nodes\n\n", environment->size);
        for(unsigned int c=0; c<nodesNumber; c++) fprintf(stdout, "%d: %s\n", c, nodes[c]);
        fprintf(stdout, "\n");
    #endif // DEBUG

    /* Allocates and fills distance matrix. */
    environment->distanceMatrix = malloc(nodesNumber * sizeof(unsigned int*));
    if(environment->distanceMatrix == NULL){
        fprintf(stderr, "Memory allocation error");
        return NULL;
    }

    for(unsigned int i=0; i<nodesNumber; i++){
        environment->distanceMatrix[i] = malloc(nodesNumber * sizeof(unsigned int));
        if(environment->distanceMatrix[i] == NULL){
            fprintf(stderr, "Memory allocation error");
            return NULL;
        }

        for(unsigned int j=0; j<nodesNumber; j++){
            if(i == j) environment->distanceMatrix[i][j] = 0;
            else environment->distanceMatrix[i][j] = GDM_API_getDistance(environment->label[i], environment->label[j]);

            #ifdef DEBUG
                fprintf(stdout, "%d ", environment->distanceMatrix[i][j]);
            #endif // DEBUG

        }
        #ifdef DEBUG
            fprintf(stdout, "\n");
        #endif // DEBUG
    }

     #ifdef DEBUG
        fprintf(stdout, "\n");
     #endif // DEBUG

    /* Returns valid environment handle. */
    return environment;
}

int environment_destroy(environment_t environment, unsigned int nodesNumber){
    /* Checks for valid environment handle. */
    if(environment == NULL){
        fprintf(stderr, "Invalid environment handle.");
        return EXIT_FAILURE;
    }

    #ifdef DEBUG
        unsigned int freeCount =    0;
    #endif // DEBUG

    /* Frees distance matrix components */
    for(int i=0; i<nodesNumber; i++){
        free(environment->distanceMatrix[i]);
        #ifdef DEBUG
            freeCount++;
        #endif // DEBUG
    }

    free(environment->distanceMatrix);
    #ifdef DEBUG
        freeCount++;
    #endif // DEBUG

    /* Frees environment handle. */
    free(environment);
    #ifdef DEBUG
        freeCount++;
        fprintf(stdout, "Freed memory count: %d.\n", freeCount);
    #endif // DEBUG

    /* Returns zero if memory free is successful. */
    return EXIT_SUCCESS;
}
