#ifndef HAND_RANK_LOOKUP_TABLE_INCLUDED
#define HAND_RANK_LOOKUP_TABLE_INCLUDED

#include <array>

using namespace std;

#include "combination_encoder.h"
#include "deck.h"
#include "fundamental_types.h"
#include "hand.h"
#include "parameters.h"
#include "utilities.h"

class hand_rank_lookup_table_s
{
   public:
      using hand_rank_lookup_table_t = array<hand_rank_t, combinations(52, 5)>;

      hand_rank_lookup_table_s(const hand_rank_lookup_table_s &) = delete;
      void operator=(const hand_rank_lookup_table_s &) = delete;

      hand_rank_lookup_table_s(hand_rank_lookup_table_s &&) = delete;
      void operator=(hand_rank_lookup_table_s &&) = delete;

      hand_rank_lookup_table_s *operator&() = delete;

      static const hand_rank_lookup_table_s &getInstance();
      const hand_rank_lookup_table_t &getLookupTable() const;

   private:
      hand_rank_lookup_table_s();
      ~hand_rank_lookup_table_s();

      hand_rank_lookup_table_t hand_rank_lookup_table;
};

#include "hand_rank_lookup_table.inl"

#endif
