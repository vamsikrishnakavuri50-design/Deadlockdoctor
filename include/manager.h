#ifndef MANAGER_H
#define MANAGER_H

#include "banker.h"

/*
 * Initialize a BankerState structure.
 */
void initialize_state(BankerState *state);

/*
 * Validate the number of processes and resources.
 *
 * Returns:
 * 1 -> Valid
 * 0 -> Invalid
 */
int validate_dimensions(int processes, int resources);

/*
 * Validate the Available resource vector.
 *
 * Returns:
 * 1 -> Valid
 * 0 -> Invalid
 */
int validate_available(BankerState *state);

/*
 * Validate the Maximum and Allocation matrices.
 *
 * Returns:
 * 1 -> Valid
 * 0 -> Invalid
 */
int validate_matrices(BankerState *state);

#endif
