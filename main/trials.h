#ifndef TRIALS_INCLUDED
#define TRIALS_INCLUDED

#include "fundamental_types.h"

#include "hand.h"

struct trial_result_t
{
   trial_result_t(const hand_t &hand_p, const my_uint_t hands_dealt_p);

   const hand_t &hand;
   const my_uint_t hands_dealt;
};

void average_random_hands_until_target_hand_rank_hit(
                                                       hand_rank_t target_hand_rank,
                                                       my_uint_t target_hand_count
                                                    );

#endif
