using namespace std;

#include "hand.h"

#include "hand_rank_table.h"

static unordered_map<unsigned long long int, hand_rank_t> hand_ranks_s;

static void operation_to_perform_2(const indexes_t &indexes)
{
   static const auto &deck{deck_s::getInstance().getDeck()};

   card_t cards[5];
   unsigned int j{0};

   for (
          auto i{indexes.cbegin()};
          i != indexes.cend();
          ++i
       )
   {
   for (unsigned int i : indexes)
      cards[j++] = deck[i];
   }

   hand_t hand{cards};
   auto id{hand.get_id()};

   hand_ranks_s[id] = hand.hand_rank();
}

hand_rank_table_s::hand_rank_table_s(): hand_ranks(hand_ranks_s)
{
   hand_ranks.clear();
   dynamic_loop_wrapper(0, 52, 5, operation_to_perform_2);
}
