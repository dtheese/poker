#ifndef HAND_RANK_TABLE_INCLUDED
#define HAND_RANK_TABLE_INCLUDED

#include <unordered_map>
#include <vector>

using namespace std;

#include "fundamental_types.h"

#include "card.h"
#include "deck.h"
#include "hand.h"

using hand_rank_map_t = unordered_map<my_uint_t, hand_rank_t>;

// This singleton is lazily initialized.
class hand_rank_table_s
{
   public:
      hand_rank_table_s(const hand_rank_table_s &) = delete;
      void operator=(const hand_rank_table_s &) = delete;

      hand_rank_table_s(hand_rank_table_s &&) = delete;
      void operator=(hand_rank_table_s &&) = delete;

      hand_rank_table_s *operator&() = delete;

      static const hand_rank_table_s &getInstance();

      hand_rank_t operator[](my_uint_t i) const;

   private:
      hand_rank_table_s();
      ~hand_rank_table_s();

      hand_rank_map_t hand_ranks;
};

#include "hand_rank_table.inl"

#endif
