#include <stdio.h>
#include "banker.h"

/*
 * Calculate the Need matrix.
 *
 * Formula:
 *
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
 * 1 -> System is SAFE
 * 0 -> System is UNSAFE
 */
int check_safety(BankerState *state)
{
    int work[MAX_RESOURCES];

    int finish[MAX_PROCESSES] = {0};

    /*
     * Work initially contains Available resources.
     */
    for (int j = 0; j < state->resources; j++) {

        work[j] = state->available[j];
    }

    int count = 0;

    /*
     * Find a process that can finish.
     */
    while (count < state->processes) {

        int found = 0;

        for (int i = 0; i < state->processes; i++) {

            /*
             * Skip processes that have already finished.
             */
            if (finish[i]) {
                continue;
            }

            int can_finish = 1;

            /*
             * Check:
             *
             * Need[i] <= Work
             */
            for (int j = 0; j < state->resources; j++) {

                if (state->need[i][j] > work[j]) {

                    can_finish = 0;
                    break;
                }
            }

            /*
             * If the process can finish,
             * simulate its completion.
             */
            if (can_finish) {

                /*
                 * Work = Work + Allocation
                 */
                for (int j = 0; j < state->resources; j++) {

                    work[j] += state->allocation[i][j];
                }

                /*
                 * Store process in safe sequence.
                 */
                state->safe_sequence[count] = i;

                finish[i] = 1;

                count++;

                found = 1;
            }
        }

        /*
         * No process could finish.
         *
         * Therefore, the system is unsafe.
         */
        if (!found) {

            return 0;
        }
    }

    /*
     * Every process can finish.
     *
     * Therefore, the system is safe.
     */
    return 1;
}


/*
 * Banker's Resource Request Algorithm
 *
 * Steps:
 *
 * 1. Check Request <= Need
 * 2. Check Request <= Available
 * 3. Temporarily allocate resources
 * 4. Run Safety Algorithm
 * 5. Grant if the state remains safe
 * 6. Roll back if the state becomes unsafe
 *
 * Returns:
 * 1 -> Request granted
 * 0 -> Request denied
 */
int request_resources(
    BankerState *state,
    int process,
    int request[]
)
{
    /*
     * Validate process number.
     */
    if (process < 0 || process >= state->processes) {

        printf("\nREQUEST DENIED\n");
        printf("Reason: Invalid process number.\n");

        return 0;
    }


    /*
     * STEP 1
     *
     * Check:
     *
     * Request <= Need
     *
     * A process cannot request more than
     * its declared remaining maximum need.
     */
    for (int j = 0; j < state->resources; j++) {

        if (request[j] > state->need[process][j]) {

            printf("\nREQUEST DENIED\n");
            printf("Reason: Request exceeds the process's remaining Need.\n");

            return 0;
        }
    }


    /*
     * STEP 2
     *
     * Check:
     *
     * Request <= Available
     *
     * If resources are currently unavailable,
     * the request cannot be granted immediately.
     */
    for (int j = 0; j < state->resources; j++) {

        if (request[j] > state->available[j]) {

            printf("\nREQUEST CANNOT BE GRANTED NOW\n");
            printf("Reason: Insufficient Available resources.\n");

            return 0;
        }
    }


    /*
     * STEP 3
     *
     * Temporarily allocate the requested resources.
     */
    for (int j = 0; j < state->resources; j++) {

        state->available[j] -= request[j];

        state->allocation[process][j] += request[j];

        state->need[process][j] -= request[j];
    }


    /*
     * STEP 4
     *
     * Check whether the resulting state is safe.
     */
    if (check_safety(state)) {

        /*
         * STEP 5
         *
         * The resulting state is safe.
         *
         * Keep the allocation.
         */
        printf("\nREQUEST GRANTED\n");
        printf("Reason: System remains in a SAFE state.\n");

        return 1;
    }


    /*
     * STEP 6
     *
     * The resulting state is unsafe.
     *
     * Roll back the temporary allocation.
     */
    for (int j = 0; j < state->resources; j++) {

        state->available[j] += request[j];

        state->allocation[process][j] -= request[j];

        state->need[process][j] += request[j];
    }


    printf("\nREQUEST DENIED\n");
    printf("Reason: Granting the request would make the system UNSAFE.\n");

    return 0;
}


/*
 * Display the complete Banker state.
 */
void display_state(BankerState *state)
{
    printf("\n========== BANKER STATE ==========\n");


    /*
     * Display Available resources.
     */
    printf("\nAvailable:\n");

    for (int j = 0; j < state->resources; j++) {

        printf("%d ", state->available[j]);
    }

    printf("\n");


    /*
     * Display Maximum matrix.
     */
    printf("\nMaximum Matrix:\n");

    for (int i = 0; i < state->processes; i++) {

        printf("P%d: ", i);

        for (int j = 0; j < state->resources; j++) {

            printf("%d ", state->maximum[i][j]);
        }

        printf("\n");
    }


    /*
     * Display Allocation matrix.
     */
    printf("\nAllocation Matrix:\n");

    for (int i = 0; i < state->processes; i++) {

        printf("P%d: ", i);

        for (int j = 0; j < state->resources; j++) {

            printf("%d ", state->allocation[i][j]);
        }

        printf("\n");
    }


    /*
     * Display Need matrix.
     */
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


/*
 * Display the safe sequence.
 */
void display_safe_sequence(BankerState *state)
{
    printf("\nSafe Sequence: ");

    for (int i = 0; i < state->processes; i++) {

        printf("P%d", state->safe_sequence[i]);

        if (i < state->processes - 1) {

            printf(" -> ");
        }
    }

    printf("\n");
}
