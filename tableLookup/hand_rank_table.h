#ifndef HAND_RANK_TABLE_INCLUDED
#define HAND_RANK_TABLE_INCLUDED

#include <unordered_map>
#include <vector>

#include "card.h"
#include "deck.h"
#include "dynamic_loop_wrapper.h"
#include "hand.h"

using namespace std;

// This singleton is lazily initialized.
class hand_rank_table_s
{
   public:
      hand_rank_table_s(const hand_rank_table_s &) = delete;
      hand_rank_table_s(hand_rank_table_s &) = delete;

      hand_rank_table_s(const hand_rank_table_s &&) = delete;
      hand_rank_table_s(hand_rank_table_s &&) = delete;

      void operator=(const hand_rank_table_s &) = delete;
      void operator=(hand_rank_table_s &) = delete;

      void operator=(const hand_rank_table_s &&) = delete;
      void operator=(hand_rank_table_s &&) = delete;

      static const hand_rank_table_s &getInstance();

      hand_rank_t operator[](unsigned long long int i) const;

   private:
      hand_rank_table_s();

      unordered_map<unsigned long long int, hand_rank_t> &hand_ranks;
};

#include "hand_rank_table.inl"

#endif
