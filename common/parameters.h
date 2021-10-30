#ifndef PARAMETERS_INCLUDED
#define PARAMETERS_INCLUDED

#include "fundamental_types.h"

// Allowed values: 5 - 52
constexpr my_uint_t NUM_CARDS{5};
static_assert(NUM_CARDS >= 5 && NUM_CARDS <= 52, "NUM_CARDS must be in the range 5 - 52, inclusive");

// Set TRIALS to 0 to enumerate all possible hands of NUM_CARDS.
// Setting TRIALS > 0 will result in a Monte Carlo simulation of TRIALS trials.
constexpr my_uint_t TRIALS{0};

#endif
