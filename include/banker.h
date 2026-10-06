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


/*
 * Calculate Need matrix.
 *
 * Need = Maximum - Allocation
 */
void calculate_need(BankerState *state);


/*
 * Check whether the current system state is safe.
 *
 * Returns:
 * 1 -> Safe
 * 0 -> Unsafe
 */
int check_safety(BankerState *state);


/*
 * Process a resource request.
 *
 * Returns:
 * 1 -> Request can be granted
 * 0 -> Request must be denied
 */
int request_resources(
    BankerState *state,
    int process,
    int request[]
);


/*
 * Display the complete Banker state.
 */
void display_state(BankerState *state);


/*
 * Display the safe sequence.
 */
void display_safe_sequence(BankerState *state);

#endif
