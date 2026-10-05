#include <stdio.h>
#include "banker.h"

/*
 * Need = Maximum - Allocation
 */
void calculate_need(BankerState *state)
{
    for (int i = 0; i < state->processes; i++) {
        for (int j = 0; j < state->resources; j++) {
            state->need[i][j] =
                state->maximum[i][j] -
                state->allocation[i][j];
        }
    }
}

/*
 * Banker's Safety Algorithm
 *
 * Returns:
 * 1 -> Safe state
 * 0 -> Unsafe state
 */
int check_safety(BankerState *state)
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    /* Work initially equals Available */
    for (int j = 0; j < state->resources; j++) {
        work[j] = state->available[j];
    }

    int count = 0;

    while (count < state->processes) {

        int found = 0;

        for (int i = 0; i < state->processes; i++) {

            if (finish[i])
                continue;

            int can_finish = 1;

            /*
             * Check:
             * Need[i] <= Work
             */
            for (int j = 0; j < state->resources; j++) {
                if (state->need[i][j] > work[j]) {
                    can_finish = 0;
                    break;
                }
            }

            if (can_finish) {

                /*
                 * Simulate process completion:
                 * Work = Work + Allocation
                 */
                for (int j = 0; j < state->resources; j++) {
                    work[j] += state->allocation[i][j];
                }

                state->safe_sequence[count] = i;

                finish[i] = 1;
                count++;
                found = 1;
            }
        }

        /*
         * No process could finish.
         * Therefore the state is unsafe.
         */
        if (!found) {
            return 0;
        }
    }

    return 1;
}

/*
 * Display Banker state
 */
void display_state(BankerState *state)
{
    printf("\n========== BANKER STATE ==========\n");

    printf("\nAvailable:\n");

    for (int j = 0; j < state->resources; j++) {
        printf("%d ", state->available[j]);
    }

    printf("\n\nMaximum Matrix:\n");

    for (int i = 0; i < state->processes; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < state->resources; j++) {
            printf("%d ", state->maximum[i][j]);
        }

        printf("\n");
    }

    printf("\nAllocation Matrix:\n");

    for (int i = 0; i < state->processes; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < state->resources; j++) {
            printf("%d ", state->allocation[i][j]);
        }

        printf("\n");
    }

    printf("\nNeed Matrix:\n");

    for (int i = 0; i < state->processes; i++) {
        printf("P%d: ", i);

        for (int j = 0; j < state->resources; j++) {
            printf("%d ", state->need[i][j]);
        }

        printf("\n");
    }

    printf("\n==================================\n");
}
