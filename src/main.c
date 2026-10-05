#include <stdio.h>
#include "banker.h"

int main(void)
{
    BankerState state = {0};

    /*
     * Example system:
     *
     * 5 processes
     * 3 resource types
     *
     * Resources:
     * A = 10
     * B = 5
     * C = 7
     */

    state.processes = 5;
    state.resources = 3;

    /*
     * Available resources
     */
    state.available[0] = 3;
    state.available[1] = 3;
    state.available[2] = 2;

    /*
     * Maximum resource requirements
     */
    int maximum[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    /*
     * Currently allocated resources
     */
    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    /*
     * Copy Maximum and Allocation
     */
    for (int i = 0; i < state.processes; i++) {

        for (int j = 0; j < state.resources; j++) {

            state.maximum[i][j] = maximum[i][j];

            state.allocation[i][j] = allocation[i][j];
        }
    }

    /*
     * Calculate Need
     */
    calculate_need(&state);

    /*
     * Display system state
     */
    display_state(&state);

    /*
     * Check whether system is safe
     */
    if (check_safety(&state)) {

        printf("\nSYSTEM STATUS: SAFE\n");

        printf("Safe Sequence: ");

        for (int i = 0; i < state.processes; i++) {

            printf("P%d", state.safe_sequence[i]);

            if (i < state.processes - 1)
                printf(" -> ");
        }

        printf("\n");

    } else {

        printf("\nSYSTEM STATUS: UNSAFE\n");

        printf("No safe sequence exists.\n");
    }

    return 0;
}
