#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

    typedef struct environmentStruct* environment_t;

    environment_t environment_build(char **nodes, unsigned int nodesNumber);        // Creates environment handle, allocates memory and fills it.
    int environment_destroy(environment_t environment, unsigned int nodesNumber);   // Frees previously allocated memory for handle.

#endif // ENVIRONMENT_H_INCLUDED
