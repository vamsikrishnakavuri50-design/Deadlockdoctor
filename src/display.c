#include <stdio.h>
#include "display.h"

/*
 * Display the Available resource vector.
 */
void display_available(const BankerState *state)
{
    int j;

    printf("\nAvailable Resources:\n");

    for (j = 0; j < state->resources; j++)
    {
        printf("R%d ", j);
    }

    printf("\n");

    for (j = 0; j < state->resources; j++)
    {
        printf("%d  ", state->available[j]);
    }

    printf("\n");
}

/*
 * Display the Maximum matrix.
 */
void display_maximum(const BankerState *state)
{
    int i, j;

    printf("\nMaximum Matrix:\n");

    for (j = 0; j < state->resources; j++)
    {
        printf("R%d ", j);
    }

    printf("\n");

    for (i = 0; i < state->processes; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < state->resources; j++)
        {
            printf("%d  ", state->maximum[i][j]);
        }

        printf("\n");
    }
}

/*
 * Display the Allocation matrix.
 */
void display_allocation(const BankerState *state)
{
    int i, j;

    printf("\nAllocation Matrix:\n");

    for (j = 0; j < state->resources; j++)
    {
        printf("R%d ", j);
    }

    printf("\n");

    for (i = 0; i < state->processes; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < state->resources; j++)
        {
            printf("%d  ", state->allocation[i][j]);
        }

        printf("\n");
    }
}

/*
 * Display the Need matrix.
 */
void display_need(const BankerState *state)
{
    int i, j;

    printf("\nNeed Matrix:\n");

    for (j = 0; j < state->resources; j++)
    {
        printf("R%d ", j);
    }

    printf("\n");

    for (i = 0; i < state->processes; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < state->resources; j++)
        {
            printf("%d  ", state->need[i][j]);
        }

        printf("\n");
    }
}

/*
 * Display the complete Banker state.
 */
void display_system_state(const BankerState *state)
{
    printf("\n========================================\n");
    printf("        CURRENT BANKER STATE\n");
    printf("========================================\n");

    display_available(state);
    display_maximum(state);
    display_allocation(state);
    display_need(state);

    printf("========================================\n");
}

/*
 * Display the safe sequence.
 */
void display_safe_sequence_result(const BankerState *state)
{
    int i;

    printf("\nSafe Sequence: ");

    for (i = 0; i < state->processes; i++)
    {
        printf("P%d", state->safe_sequence[i]);

        if (i < state->processes - 1)
        {
            printf(" -> ");
        }
    }

    printf("\n");
}

/*
 * Display a resource request.
 */
void display_request(const int request[], int process, int resources)
{
    int j;

    printf("\nResource Request from P%d:\n", process);

    for (j = 0; j < resources; j++)
    {
        printf("R%d: %d\n", j, request[j]);
    }
}
