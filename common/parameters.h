#ifndef PARAMETERS_INCLUDED
#define PARAMETERS_INCLUDED

#include <limits>

using namespace std;

#include "fundamental_types.h"

// Allowed values: 5 - 52
constexpr my_uint_t NUM_CARDS{5};
static_assert(NUM_CARDS >= 5 && NUM_CARDS <= 52, "NUM_CARDS must be in the range 5 - 52, inclusive");

// Set TRIALS to 0 to enumerate all possible hands of NUM_CARDS.
// Setting TRIALS > 0 will result in a Monte Carlo simulation of TRIALS trials.
constexpr my_uint_t TRIALS{0};

// This controls whether or not individual hands are printed as they are considered.
constexpr bool PRINT{false};

// This allows the user to set a limit on the number of threads.
constexpr my_uint_t THREADS_LIMIT{numeric_limits<my_uint_t>::max()};
// constexpr my_uint_t THREADS_LIMIT{<your chosen value>};

#endif
