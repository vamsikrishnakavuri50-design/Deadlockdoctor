#include <stdio.h>
#include "banker.h"

/*
 * Calculate the Need matrix.
 *
 * Need = Maximum - Allocation
 */
void calculate_need(BankerState *state)
{
    for (int i = 0; i < state->processes; i++)
    {
        for (int j = 0; j < state->resources; j++)
        {
            state->need[i][j] =
                state->maximum[i][j] -
                state->allocation[i][j];
        }
    }
}


/*
 * Check whether the current system state is safe.
 *
 * Returns:
 * 1 -> Safe
 * 0 -> Unsafe
 */
int check_safety(BankerState *state)
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    int count = 0;

    /*
     * Work starts with Available resources.
     */
    for (int j = 0; j < state->resources; j++)
    {
        work[j] = state->available[j];
    }

    /*
     * Find a process whose remaining Need
     * can be satisfied by Work.
     */
    while (count < state->processes)
    {
        int found = 0;

        for (int i = 0; i < state->processes; i++)
        {
            if (finish[i])
            {
                continue;
            }

            int possible = 1;

            /*
             * Check:
             * Need[i] <= Work
             */
            for (int j = 0; j < state->resources; j++)
            {
                if (state->need[i][j] > work[j])
                {
                    possible = 0;
                    break;
                }
            }

            if (possible)
            {
                /*
                 * Simulate completion of process i.
                 *
                 * Work = Work + Allocation[i]
                 */
                for (int j = 0; j < state->resources; j++)
                {
                    work[j] += state->allocation[i][j];
                }

                finish[i] = 1;
                state->safe_sequence[count] = i;

                count++;
                found = 1;
            }
        }

        /*
         * No unfinished process can proceed.
         * Therefore, the system is unsafe.
         */
        if (!found)
        {
            return 0;
        }
    }

    return 1;
}


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
)
{
    /*
     * Validate process number.
     */
    if (process < 0 || process >= state->processes)
    {
        printf("\nREQUEST DENIED\n");
        printf("Reason: Invalid process number.\n");

        return 0;
    }

    /*
     * Check:
     * Request <= Need
     */
    for (int j = 0; j < state->resources; j++)
    {
        if (request[j] > state->need[process][j])
        {
            printf("\nREQUEST DENIED\n");
            printf("Reason: Request exceeds the process's remaining Need.\n");

            return 0;
        }
    }

    /*
     * Check:
     * Request <= Available
     */
    for (int j = 0; j < state->resources; j++)
    {
        if (request[j] > state->available[j])
        {
            printf("\nREQUEST CANNOT BE GRANTED NOW\n");
            printf("Reason: Insufficient Available resources.\n");

            return 0;
        }
    }

    /*
     * Temporarily allocate the requested resources.
     */
    for (int j = 0; j < state->resources; j++)
    {
        state->available[j] -= request[j];

        state->allocation[process][j] += request[j];

        state->need[process][j] -= request[j];
    }

    /*
     * Check whether the resulting state is safe.
     */
    if (check_safety(state))
    {
        printf("\nREQUEST GRANTED\n");
        printf("Reason: System remains in a SAFE state.\n");

        return 1;
    }

    /*
     * Unsafe state:
     * Roll back the temporary allocation.
     */
    for (int j = 0; j < state->resources; j++)
    {
        state->available[j] += request[j];

        state->allocation[process][j] -= request[j];

        state->need[process][j] += request[j];
    }

    printf("\nREQUEST DENIED\n");
    printf("Reason: Granting the request would make the system UNSAFE.\n");

    return 0;
}
