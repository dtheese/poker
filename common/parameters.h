#ifndef PARAMETERS_INCLUDED
#define PARAMETERS_INCLUDED

// Allowed values: 5 - 52
constexpr unsigned int NUM_CARDS{5};
static_assert(NUM_CARDS >= 5 && NUM_CARDS <= 52, "NUM_CARDS must be in the range 5 - 52, inclusive");

// Allowed values: 1 - 4
constexpr unsigned int MAX_THREADS{4};
static_assert(MAX_THREADS >= 1 && MAX_THREADS <= 4, "MAX_THREADS must be in the range 1 - 4, inclusive");

// Allowed values: true, false
constexpr bool MONTE_CARLO(false);
#endif
