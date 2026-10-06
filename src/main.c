#include <stdio.h>
#include "banker.h"

int main(void)
{
    BankerState state = {0};

    /*
     * Project Header
     */
    printf("\n=========================================\n");
    printf("           DEADLOCKDOCTOR\n");
    printf("       BANKER'S ALGORITHM\n");
    printf("=========================================\n");


    /*
     * -------------------------------------------------
     * STEP 1: Get number of processes and resources
     * -------------------------------------------------
     */

    printf("\nEnter number of processes (1-%d): ",
           MAX_PROCESSES);

    scanf("%d", &state.processes);

    if (state.processes < 1 ||
        state.processes > MAX_PROCESSES) {

        printf("\nInvalid number of processes.\n");
        return 1;
    }


    printf("Enter number of resources (1-%d): ",
           MAX_RESOURCES);

    scanf("%d", &state.resources);

    if (state.resources < 1 ||
        state.resources > MAX_RESOURCES) {

        printf("\nInvalid number of resources.\n");
        return 1;
    }


    /*
     * -------------------------------------------------
     * STEP 2: Enter Available resources
     * -------------------------------------------------
     */

    printf("\n=========================================\n");
    printf("          AVAILABLE RESOURCES\n");
    printf("=========================================\n");

    for (int j = 0; j < state.resources; j++) {

        printf("Available Resource %d: ", j);

        scanf("%d", &state.available[j]);

        if (state.available[j] < 0) {

            printf("\nInvalid resource value.\n");
            return 1;
        }
    }


    /*
     * -------------------------------------------------
     * STEP 3: Enter Maximum Matrix
     * -------------------------------------------------
     */

    printf("\n=========================================\n");
    printf("           MAXIMUM MATRIX\n");
    printf("=========================================\n");

    for (int i = 0; i < state.processes; i++) {

        printf("\nMaximum resources for P%d:\n", i);

        for (int j = 0; j < state.resources; j++) {

            printf("Resource %d: ", j);

            scanf("%d", &state.maximum[i][j]);

            if (state.maximum[i][j] < 0) {

                printf("\nInvalid maximum value.\n");
                return 1;
            }
        }
    }


    /*
     * -------------------------------------------------
     * STEP 4: Enter Allocation Matrix
     * -------------------------------------------------
     */

    printf("\n=========================================\n");
    printf("          ALLOCATION MATRIX\n");
    printf("=========================================\n");

    for (int i = 0; i < state.processes; i++) {

        printf("\nAllocated resources for P%d:\n", i);

        for (int j = 0; j < state.resources; j++) {

            printf("Resource %d: ", j);

            scanf("%d", &state.allocation[i][j]);

            if (state.allocation[i][j] < 0) {

                printf("\nInvalid allocation value.\n");
                return 1;
            }


            /*
             * Allocation cannot exceed Maximum.
             */
            if (state.allocation[i][j] >
                state.maximum[i][j]) {

                printf("\nInvalid state.\n");

                printf("Allocation of P%d for Resource %d "
                       "cannot exceed Maximum.\n",
                       i, j);

                return 1;
            }
        }
    }


    /*
     * -------------------------------------------------
     * STEP 5: Calculate Need
     * -------------------------------------------------
     */

    calculate_need(&state);


    /*
     * -------------------------------------------------
     * STEP 6: Display complete Banker state
     * -------------------------------------------------
     */

    printf("\n\n=========================================\n");
    printf("          INITIAL BANKER STATE\n");
    printf("=========================================\n");

    display_state(&state);


    /*
     * -------------------------------------------------
     * STEP 7: Check system safety
     * -------------------------------------------------
     */

    printf("\nSYSTEM SAFETY CHECK\n");
    printf("-----------------------------------------\n");

    if (check_safety(&state)) {

        printf("SYSTEM STATUS: SAFE\n");

        display_safe_sequence(&state);

    } else {

        printf("SYSTEM STATUS: UNSAFE\n");
        printf("No safe sequence exists.\n");

        /*
         * We can still display the state,
         * but resource requests should not
         * be processed from an initially
         * unsafe state.
         */
        return 0;
    }


    /*
     * -------------------------------------------------
     * STEP 8: Resource Request
     * -------------------------------------------------
     */

    int process;
    int request[MAX_RESOURCES];


    printf("\n=========================================\n");
    printf("          RESOURCE REQUEST\n");
    printf("=========================================\n");


    printf("\nEnter process number (0-%d): ",
           state.processes - 1);

    scanf("%d", &process);


    if (process < 0 ||
        process >= state.processes) {

        printf("\nInvalid process number.\n");
        return 1;
    }


    printf("\nEnter resource request for P%d:\n",
           process);


    for (int j = 0; j < state.resources; j++) {

        printf("Resource %d: ", j);

        scanf("%d", &request[j]);


        if (request[j] < 0) {

            printf("\nInvalid request.\n");
            printf("Resource request cannot be negative.\n");

            return 1;
        }
    }


    /*
     * Display request.
     */

    printf("\nRequest from P%d: ", process);

    for (int j = 0; j < state.resources; j++) {

        printf("%d ", request[j]);
    }

    printf("\n");


    /*
     * -------------------------------------------------
     * STEP 9: Process the request
     * -------------------------------------------------
     */

    request_resources(
        &state,
        process,
        request
    );


    /*
     * -------------------------------------------------
     * STEP 10: Display state after request
     * -------------------------------------------------
     */

    printf("\n========== STATE AFTER REQUEST ==========\n");

    display_state(&state);


    /*
     * -------------------------------------------------
     * STEP 11: Final safety check
     * -------------------------------------------------
     */

    if (check_safety(&state)) {

        printf("\nFINAL SYSTEM STATUS: SAFE\n");

        display_safe_sequence(&state);

    } else {

        printf("\nFINAL SYSTEM STATUS: UNSAFE\n");
    }


    printf("\n=========================================\n");
    printf("       DEADLOCKDOCTOR EXECUTION END\n");
    printf("=========================================\n");


    return 0;
}
