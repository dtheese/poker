#ifndef DYNAMIC_LOOP_FUNCTOR_INCLUDED
#define DYNAMIC_LOOP_FUNCTOR_INCLUDED

#include <array>

using namespace std;

#include "dynamic_loop.h"
#include "fundamental_types.h"
#include "hand.h"
#include "hand_rank_lookup_table.h"
#include "parameters.h"

class dynamic_loop_functor_t
{
   public:
      dynamic_loop_functor_t(const array<my_uint_t, NUM_CARDS> &indexes_all_p);

      dynamic_loop_functor_t(const dynamic_loop_functor_t &) = delete;
      dynamic_loop_functor_t &operator=(const dynamic_loop_functor_t &) = delete;

      dynamic_loop_functor_t(dynamic_loop_functor_t &&) = delete;
      dynamic_loop_functor_t &operator=(dynamic_loop_functor_t &&) = delete;

      void operator()(const indexes_t<my_uint_t> &indexes_5);

      hand_rank_t getResult() const;

   private:
      const
      hand_rank_lookup_table_t
      &hand_rank_lookup_table{hand_rank_lookup_table_s::getInstance().getLookupTable()};

      const array<my_uint_t, NUM_CARDS> &indexes_all;
      hand_rank_t highest_hand_seen{hand_rank_t::HIGH_CARD};
};

#endif
