#include <stdio.h>

#include "banker.h"
#include "manager.h"
#include "display.h"

int main(void)
{
    BankerState state;

    int i, j;
    int process;
    int request[MAX_RESOURCES];

    int safety_result;
    int request_result;

    /*
     * Initialize the Banker state.
     */
    initialize_state(&state);

    printf("=========================================\n");
    printf("              DeadlockDoctor\n");
    printf("       Banker's Algorithm Simulator\n");
    printf("=========================================\n");

    /*
     * Get number of processes.
     */
    printf("\nEnter number of processes (1-%d): ",
           MAX_PROCESSES);

    if (scanf("%d", &state.processes) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    /*
     * Get number of resources.
     */
    printf("Enter number of resources (1-%d): ",
           MAX_RESOURCES);

    if (scanf("%d", &state.resources) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    /*
     * Validate dimensions.
     */
    if (!validate_dimensions(state.processes,
                             state.resources))
    {
        printf("\nERROR: Invalid number of processes or resources.\n");
        return 1;
    }

    /*
     * Input Available resources.
     */
    printf("\nEnter Available resources:\n");

    for (j = 0; j < state.resources; j++)
    {
        printf("Available R%d: ", j);

        if (scanf("%d", &state.available[j]) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    /*
     * Validate Available resources.
     */
    if (!validate_available(&state))
    {
        printf("\nERROR: Available resources cannot be negative.\n");
        return 1;
    }

    /*
     * Input Maximum matrix.
     */
    printf("\nEnter Maximum Resource Matrix:\n");

    for (i = 0; i < state.processes; i++)
    {
        printf("\nMaximum resources for P%d:\n", i);

        for (j = 0; j < state.resources; j++)
        {
            printf("P%d R%d: ", i, j);

            if (scanf("%d", &state.maximum[i][j]) != 1)
            {
                printf("Invalid input.\n");
                return 1;
            }
        }
    }

    /*
     * Input Allocation matrix.
     */
    printf("\nEnter Allocation Matrix:\n");

    for (i = 0; i < state.processes; i++)
    {
        printf("\nAllocated resources for P%d:\n", i);

        for (j = 0; j < state.resources; j++)
        {
            printf("P%d R%d: ", i, j);

            if (scanf("%d", &state.allocation[i][j]) != 1)
            {
                printf("Invalid input.\n");
                return 1;
            }
        }
    }

    /*
     * Validate Maximum and Allocation matrices.
     */
    if (!validate_matrices(&state))
    {
        printf("\nERROR: Invalid Maximum or Allocation matrix.\n");
        printf("Allocation cannot exceed Maximum.\n");
        return 1;
    }

    /*
     * Calculate Need matrix.
     */
    calculate_need(&state);

    /*
     * Display complete initial state.
     */
    display_system_state(&state);

    /*
     * Perform initial safety check.
     */
    printf("\nChecking initial system safety...\n");

    safety_result = check_safety(&state);

    if (safety_result)
    {
        printf("\nSYSTEM STATUS: SAFE\n");

        display_safe_sequence_result(&state);
    }
    else
    {
        printf("\nSYSTEM STATUS: UNSAFE\n");
        printf("No safe sequence exists.\n");

        return 0;
    }

    /*
     * Input process for resource request.
     */
    printf("\n=========================================\n");
    printf("       RESOURCE REQUEST SECTION\n");
    printf("=========================================\n");

    printf("\nEnter process number making the request (0-%d): ",
           state.processes - 1);

    if (scanf("%d", &process) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    /*
     * Validate process number.
     */
    if (process < 0 || process >= state.processes)
    {
        printf("\nERROR: Invalid process number.\n");
        return 1;
    }

    /*
     * Input resource request.
     */
    printf("\nEnter resource request for P%d:\n", process);

    for (j = 0; j < state.resources; j++)
    {
        printf("Request R%d: ", j);

        if (scanf("%d", &request[j]) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }

        /*
         * Negative requests are invalid.
         */
        if (request[j] < 0)
        {
            printf("\nERROR: Resource request cannot be negative.\n");
            return 1;
        }
    }

    /*
     * Display requested resources.
     */
    display_request(request,
                    process,
                    state.resources);

    /*
     * Process the resource request.
     */
    request_result = request_resources(&state,
                                       process,
                                       request);

    /*
     * Display state after request processing.
     */
    printf("\n=========================================\n");
    printf("          STATE AFTER REQUEST\n");
    printf("=========================================\n");

    display_system_state(&state);

    /*
     * Check final system safety.
     */
    printf("\nChecking final system safety...\n");

    safety_result = check_safety(&state);

    if (safety_result)
    {
        printf("\nFINAL SYSTEM STATUS: SAFE\n");

        display_safe_sequence_result(&state);
    }
    else
    {
        printf("\nFINAL SYSTEM STATUS: UNSAFE\n");
    }

    /*
     * Final request result.
     */
    printf("\n=========================================\n");

    if (request_result)
    {
        printf("Resource request was successfully granted.\n");
    }
    else
    {
        printf("Resource request was not granted.\n");
    }

    printf("=========================================\n");

    return 0;
}
