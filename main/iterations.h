#ifndef ITERATIONS_INCLUDED
#define ITERATIONS_INCLUDED

#include <map>

using namespace std;

#include "fundamental_types.h"

#include "hand.h"

struct iteration_result_t
{
   iteration_result_t();

   iteration_result_t(
                        const map<hand_rank_t, my_uint_t> hand_rank_count_p,
                        const my_uint_t hands_dealt_p
                     );

   map<hand_rank_t, my_uint_t> hand_rank_count;
   my_uint_t hands_dealt;
};

void evaluate_all_possible_hands();

#endif
