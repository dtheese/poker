#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <time.h>
#include <vector>

#include "deck.h"
#include "dynamic_loop.h"
#include "hand.h"
#include "hand_rank_table.h"

using namespace std;

namespace
{
   class dynamic_loop_functor_t
   {
      public:
         dynamic_loop_functor_t()
         {
         }

         dynamic_loop_functor_t(const dynamic_loop_functor_t &) = delete;
         dynamic_loop_functor_t &operator=(const dynamic_loop_functor_t &) = delete;

         dynamic_loop_functor_t(dynamic_loop_functor_t &&) = delete;
         dynamic_loop_functor_t &operator=(dynamic_loop_functor_t &&) = delete;

         void operator()(const indexes_t &indexes)
         {
            unsigned long long int hand_id(1);

            for (
                   auto i{indexes.begin()};
                   i != indexes.end();
                   ++i
                )
            {
               hand_id *= deck[*i].get_id();
            }

            ++hand_rank_count[hrt[hand_id]];
            ++hands_dealt;
         }

         const map<hand_rank_t, unsigned long long int> &getHandRankCount() const
         {
            return hand_rank_count;
         }

         unsigned long long int getHandsDealt() const
         {
            return hands_dealt;
         }

      private:
         const vector<card_t> &deck{deck_s::getInstance().getDeck()};
         map<hand_rank_t, unsigned long long int> hand_rank_count;
         unsigned long long int hands_dealt{0};
         const hand_rank_table_s &hrt{hand_rank_table_s::getInstance()};
   };
}

int main()
{
   // This version of the program works only for 5-card hands.
   constexpr unsigned int NUM_CARDS{5};

   system("date");
   cout << endl;

   clock_t start, end;

   start = clock();

   dynamic_loop_functor_t dynamic_loop_functor;
   dynamic_loop_t<dynamic_loop_functor_t> dynamic_loop(0, 52, NUM_CARDS, dynamic_loop_functor);

   dynamic_loop.run();

   end = clock();

   const map<hand_rank_t, unsigned long long int> &hand_rank_count{dynamic_loop_functor.getHandRankCount()};

   cout << "Hands dealt: " << dynamic_loop_functor.getHandsDealt() << endl;
   cout << endl;

   cout << "Royal flush       "  << hand_rank_count.at(hand_rank_t::ROYAL_FLUSH)     << endl;
   cout << "Straight flush    "  << hand_rank_count.at(hand_rank_t::STRAIGHT_FLUSH)  << endl;
   cout << "Four of a kind    "  << hand_rank_count.at(hand_rank_t::FOUR_OF_A_KIND)  << endl;
   cout << "Full house        "  << hand_rank_count.at(hand_rank_t::FULL_HOUSE)      << endl;
   cout << "Flush             "  << hand_rank_count.at(hand_rank_t::FLUSH)           << endl;
   cout << "Straight          "  << hand_rank_count.at(hand_rank_t::STRAIGHT)        << endl;
   cout << "Three of a kind   "  << hand_rank_count.at(hand_rank_t::THREE_OF_A_KIND) << endl;
   cout << "Two pair          "  << hand_rank_count.at(hand_rank_t::TWO_PAIR)        << endl;
   cout << "One pair          "  << hand_rank_count.at(hand_rank_t::ONE_PAIR)        << endl;
   cout << "High card         "  << hand_rank_count.at(hand_rank_t::HIGH_CARD)       << endl;
   cout << endl;

   cout << "Confirming hands dealt: "                         \
        << hand_rank_count.at(hand_rank_t::HIGH_CARD)       + \
           hand_rank_count.at(hand_rank_t::ONE_PAIR)        + \
           hand_rank_count.at(hand_rank_t::TWO_PAIR)        + \
           hand_rank_count.at(hand_rank_t::THREE_OF_A_KIND) + \
           hand_rank_count.at(hand_rank_t::STRAIGHT)        + \
           hand_rank_count.at(hand_rank_t::FLUSH)           + \
           hand_rank_count.at(hand_rank_t::FULL_HOUSE)      + \
           hand_rank_count.at(hand_rank_t::FOUR_OF_A_KIND)  + \
           hand_rank_count.at(hand_rank_t::STRAIGHT_FLUSH)  + \
           hand_rank_count.at(hand_rank_t::ROYAL_FLUSH)       \
        << endl;

   cout << endl;

   double time_taken = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);

   cout << "Time taken by program is : " << fixed 
        << time_taken << setprecision(5);

   cout << " sec " << endl;
   cout << endl;
}
