#ifndef TRIALS_INCLUDED
#define TRIALS_INCLUDED

#include "hand.h"

using namespace std;

struct trial_result_t
{
   trial_result_t(const hand_t &hand_p, const unsigned long long int hands_dealt_p);

   const hand_t &hand;
   const unsigned long long int hands_dealt;
};

void average_random_hands_until_target_hand_rank_hit(
                                                       hand_rank_t target_hand_rank,
                                                       unsigned long long int target_hand_count,
                                                       unsigned int num_cards
                                                    );

#endif
