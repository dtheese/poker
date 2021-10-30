#include "dynamic_loop_functor.h"

dynamic_loop_functor_t::dynamic_loop_functor_t(const array<my_uint_t, NUM_CARDS> &indexes_all_p):
indexes_all{indexes_all_p}
{
}

void dynamic_loop_functor_t::operator()(const indexes_t<my_uint_t> &indexes_5)
{
   array<my_uint_t, 5> indexes_into_deck{};
   my_uint_t j{0};

   for (auto i : indexes_5)
      indexes_into_deck[j++] = indexes_all[i];

   auto encoded_value_5{
        combination_encoder_t<decltype(indexes_into_deck), 52, 5>::
        encode(indexes_into_deck)
                       };

   auto this_hands_rank{hand_rank_lookup_table[encoded_value_5]};

   if (this_hands_rank > highest_hand_seen)
      highest_hand_seen = this_hands_rank;
}

hand_rank_t dynamic_loop_functor_t::getResult() const
{
   return highest_hand_seen;
}
