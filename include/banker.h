#ifndef BANKER_H
#define BANKER_H

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

typedef struct {
    int processes;
    int resources;

    int available[MAX_RESOURCES];

    int maximum[MAX_PROCESSES][MAX_RESOURCES];

    int allocation[MAX_PROCESSES][MAX_RESOURCES];

    int need[MAX_PROCESSES][MAX_RESOURCES];

    int safe_sequence[MAX_PROCESSES];

} BankerState;

/* Calculate Need matrix */
void calculate_need(BankerState *state);

/* Check whether the current state is safe */
int check_safety(BankerState *state);

/* Display the current Banker state */
void display_state(BankerState *state);

#endif
