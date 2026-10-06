#include <stdio.h>
#include "manager.h"

/*
 * Initialize a BankerState structure.
 */
void initialize_state(BankerState *state)
{
    int i, j;

    state->processes = 0;
    state->resources = 0;

    for (i = 0; i < MAX_RESOURCES; i++)
    {
        state->available[i] = 0;
    }

    for (i = 0; i < MAX_PROCESSES; i++)
    {
        state->safe_sequence[i] = -1;

        for (j = 0; j < MAX_RESOURCES; j++)
        {
            state->maximum[i][j] = 0;
            state->allocation[i][j] = 0;
            state->need[i][j] = 0;
        }
    }
}

/*
 * Validate the number of processes and resources.
 *
 * Returns:
 * 1 -> Valid
 * 0 -> Invalid
 */
int validate_dimensions(int processes, int resources)
{
    if (processes < 1 || processes > MAX_PROCESSES)
    {
        return 0;
    }

    if (resources < 1 || resources > MAX_RESOURCES)
    {
        return 0;
    }

    return 1;
}

/*
 * Validate the Available resource vector.
 *
 * Returns:
 * 1 -> Valid
 * 0 -> Invalid
 */
int validate_available(BankerState *state)
{
    int i;

    for (i = 0; i < state->resources; i++)
    {
        if (state->available[i] < 0)
        {
            return 0;
        }
    }

    return 1;
}

/*
 * Validate the Maximum and Allocation matrices.
 *
 * Conditions:
 * 1. Maximum cannot be negative.
 * 2. Allocation cannot be negative.
 * 3. Allocation cannot exceed Maximum.
 *
 * Returns:
 * 1 -> Valid
 * 0 -> Invalid
 */
int validate_matrices(BankerState *state)
{
    int i, j;

    for (i = 0; i < state->processes; i++)
    {
        for (j = 0; j < state->resources; j++)
        {
            if (state->maximum[i][j] < 0)
            {
                return 0;
            }

            if (state->allocation[i][j] < 0)
            {
                return 0;
            }

            if (state->allocation[i][j] >
                state->maximum[i][j])
            {
                return 0;
            }
        }
    }

    return 1;
}
