#include <stdio.h>
#include <string.h>
#include "banker.h"


/*
 * Global test counters
 */
int passed = 0;
int failed = 0;


/*
 * Print test result
 */
void test_result(const char *test_name, int result)
{
    if (result) {

        printf("[PASS] %s\n", test_name);
        passed++;

    } else {

        printf("[FAIL] %s\n", test_name);
        failed++;
    }
}


/*
 * Create the standard SAFE Banker state.
 */
void setup_safe_state(BankerState *state)
{
    memset(state, 0, sizeof(BankerState));

    state->processes = 5;
    state->resources = 3;

    /*
     * Available resources
     */
    state->available[0] = 3;
    state->available[1] = 3;
    state->available[2] = 2;


    /*
     * Maximum matrix
     */
    int maximum[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };


    /*
     * Allocation matrix
     */
    int allocation[5][3] = {
        {0, 1, 0},
        {2, 1, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };


    /*
     * Copy matrices into BankerState.
     */
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 3; j++) {

            state->maximum[i][j] = maximum[i][j];

            state->allocation[i][j] = allocation[i][j];
        }
    }


    /*
     * Calculate Need matrix.
     */
    calculate_need(state);
}


/*
 * TC-1
 *
 * Test whether the standard state is SAFE.
 */
void test_safe_state(void)
{
    BankerState state;

    setup_safe_state(&state);

    int result = check_safety(&state);

    test_result(
        "TC-1: Safe initial state",
        result
    );
}


/*
 * TC-2
 *
 * Create an UNSAFE state.
 */
void test_unsafe_state(void)
{
    BankerState state;

    setup_safe_state(&state);

    /*
     * Make Available resources insufficient
     * for every process to finish.
     */
    state.available[0] = 0;
    state.available[1] = 0;
    state.available[2] = 0;

    int result = check_safety(&state);

    test_result(
        "TC-2: Unsafe initial state",
        !result
    );
}


/*
 * TC-3
 *
 * Test a valid request that should be GRANTED.
 */
void test_valid_request(void)
{
    BankerState state;

    setup_safe_state(&state);

    int request[3] = {1, 0, 2};

    int result = request_resources(
        &state,
        1,
        request
    );

    test_result(
        "TC-3: Valid request is granted",
        result
    );
}


/*
 * TC-4
 *
 * Request more resources than the process Need.
 */
void test_request_exceeds_need(void)
{
    BankerState state;

    setup_safe_state(&state);

    /*
     * P1 Need = 1 1 2
     *
     * Requesting 2 units of Resource 0
     * exceeds its remaining Need.
     */
    int request[3] = {2, 0, 0};

    int result = request_resources(
        &state,
        1,
        request
    );

    test_result(
        "TC-4: Request exceeds Need",
        !result
    );
}


/*
 * TC-5
 *
 * Request more resources than currently Available.
 */
void test_request_exceeds_available(void)
{
    BankerState state;

    setup_safe_state(&state);

    /*
     * P0 Need = 7 4 3
     *
     * Requesting 4 units of Resource 0
     * exceeds Available = 3 3 2.
     */
    int request[3] = {4, 0, 0};

    int result = request_resources(
        &state,
        0,
        request
    );

    test_result(
        "TC-5: Request exceeds Available",
        !result
    );
}


/*
 * TC-6
 *
 * Request satisfies Need and Available,
 * but results in an UNSAFE state.
 *
 * The request must be denied and rolled back.
 */
void test_unsafe_request_rollback(void)
{
    BankerState state;

    setup_safe_state(&state);

    /*
     * Save original state.
     */
    int original_available[3];

    int original_allocation[3];

    for (int j = 0; j < 3; j++) {

        original_available[j] =
            state.available[j];

        original_allocation[j] =
            state.allocation[0][j];
    }


    /*
     * P0 requests 0 0 2.
     */
    int request[3] = {0, 0, 2};

    int result = request_resources(
        &state,
        0,
        request
    );


    /*
     * Request should be denied.
     */
    int denied = !result;


    /*
     * Check whether Available was restored.
     */
    int available_restored = 1;

    for (int j = 0; j < 3; j++) {

        if (state.available[j] !=
            original_available[j]) {

            available_restored = 0;
        }
    }


    /*
     * Check whether Allocation was restored.
     */
    int allocation_restored = 1;

    for (int j = 0; j < 3; j++) {

        if (state.allocation[0][j] !=
            original_allocation[j]) {

            allocation_restored = 0;
        }
    }


    int result_final =
        denied &&
        available_restored &&
        allocation_restored;


    test_result(
        "TC-6: Unsafe request denied and rolled back",
        result_final
    );
}


/*
 * TC-7
 *
 * Test invalid process number.
 */
void test_invalid_process(void)
{
    BankerState state;

    setup_safe_state(&state);

    int request[3] = {1, 0, 0};

    int result = request_resources(
        &state,
        10,
        request
    );

    test_result(
        "TC-7: Invalid process rejected",
        !result
    );
}


/*
 * Main test runner
 */
int main(void)
{
    printf("\n=========================================\n");
    printf("       DEADLOCKDOCTOR TEST SUITE\n");
    printf("=========================================\n\n");


    test_safe_state();

    test_unsafe_state();

    test_valid_request();

    test_request_exceeds_need();

    test_request_exceeds_available();

    test_unsafe_request_rollback();

    test_invalid_process();


    printf("\n=========================================\n");
    printf("              TEST SUMMARY\n");
    printf("=========================================\n");

    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);

    printf("=========================================\n");


    return failed == 0 ? 0 : 1;
}
