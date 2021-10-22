#ifndef HAND_RANK_LOOKUP_TABLE_INCLUDED
#define HAND_RANK_LOOKUP_TABLE_INCLUDED

class hand_rank_lookup_table_s
{
   public:
      hand_rank_lookup_table_s(const hand_rank_lookup_table_s &) = delete;
      void operator=(const hand_rank_lookup_table_s &) = delete;

      hand_rank_lookup_table_s(hand_rank_lookup_table_s &&) = delete;
      void operator=(hand_rank_lookup_table_s &&) = delete;

      hand_rank_lookup_table_s *operator&() = delete;

      static const hand_rank_lookup_table_s &getInstance();

   private:
      hand_rank_lookup_table_s();
      ~hand_rank_lookup_table_s();
};

#include "hand_rank_lookup_table.inl"

#endif
