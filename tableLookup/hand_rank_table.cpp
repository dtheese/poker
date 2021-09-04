using namespace std;

#include "hand.h"

#include "dynamic_loop.h"
#include "hand_rank_table.h"

namespace
{
   class dynamic_loop_functor_t
   {
      public:
         dynamic_loop_functor_t(hand_rank_map_t &hand_ranks_p): hand_ranks(hand_ranks_p)
         {
         }

         dynamic_loop_functor_t(const dynamic_loop_functor_t &) = delete;
         dynamic_loop_functor_t &operator=(const dynamic_loop_functor_t &) = delete;

         dynamic_loop_functor_t(dynamic_loop_functor_t &&) = delete;
         dynamic_loop_functor_t &operator=(dynamic_loop_functor_t &&) = delete;

         void operator()(const indexes_t &indexes)
         {
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

            hand_ranks[id] = hand.hand_rank();
         }

      private:
         const vector<card_t> &deck{deck_s::getInstance().getDeck()};
         hand_rank_map_t &hand_ranks;
   };
}

hand_rank_table_s::hand_rank_table_s()
{
   dynamic_loop_functor_t dynamic_loop_functor(hand_ranks);

   hand_ranks.clear();
   dynamic_loop_t<dynamic_loop_functor_t> dynamic_loop(0, 52, 5, dynamic_loop_functor);
}

hand_rank_table_s::~hand_rank_table_s()
{
}
