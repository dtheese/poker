#ifndef ITERATIONS_INCLUDED
#define ITERATIONS_INCLUDED

#include <map>

#include "hand.h"

using namespace std;

struct iteration_result_t
{
   iteration_result_t(
                        const map<hand_rank_t, unsigned long long int> hand_rank_count_p,
                        const unsigned long long int hands_dealt_p
                     );

   const map<hand_rank_t, unsigned long long int> hand_rank_count;
   const unsigned long long int hands_dealt;
};

void evaluate_all_possible_hands(unsigned int num_cards);

#endif
