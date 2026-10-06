#ifndef DISPLAY_H
#define DISPLAY_H

#include "banker.h"

/*
 * Display the complete Banker state.
 */
void display_system_state(const BankerState *state);

/*
 * Display the Available resource vector.
 */
void display_available(const BankerState *state);

/*
 * Display the Maximum matrix.
 */
void display_maximum(const BankerState *state);

/*
 * Display the Allocation matrix.
 */
void display_allocation(const BankerState *state);

/*
 * Display the Need matrix.
 */
void display_need(const BankerState *state);

/*
 * Display the safe sequence.
 */
void display_safe_sequence_result(const BankerState *state);

/*
 * Display a resource request.
 */
void display_request(const int request[], int process, int resources);

#endif
