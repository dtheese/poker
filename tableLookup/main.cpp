#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <time.h>
#include <vector>

#include "deck.h"
#include "hand.h"
#include "hand_rank_table.h"

using namespace std;

static map<hand_rank_t, unsigned long long int> hand_rank_count;
static unsigned long long int hands_dealt(0);

static void operation_to_perform_1(const indexes_t &indexes);

int main()
{
   system("date");
   cout << endl;

   clock_t start, end;

   start = clock();
   dynamic_loop_wrapper(52, 5, operation_to_perform_1);
   end = clock();

   cout << "Hands dealt: " << hands_dealt << endl;
   cout << endl;

   cout << "Royal flush       "  << hand_rank_count[hand_rank_t::ROYAL_FLUSH]     << endl;
   cout << "Straight flush    "  << hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  << endl;
   cout << "Four of a kind    "  << hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  << endl;
   cout << "Full house        "  << hand_rank_count[hand_rank_t::FULL_HOUSE]      << endl;
   cout << "Flush             "  << hand_rank_count[hand_rank_t::FLUSH]           << endl;
   cout << "Straight          "  << hand_rank_count[hand_rank_t::STRAIGHT]        << endl;
   cout << "Three of a kind   "  << hand_rank_count[hand_rank_t::THREE_OF_A_KIND] << endl;
   cout << "Two pair          "  << hand_rank_count[hand_rank_t::TWO_PAIR]        << endl;
   cout << "One pair          "  << hand_rank_count[hand_rank_t::ONE_PAIR]        << endl;
   cout << "High card         "  << hand_rank_count[hand_rank_t::HIGH_CARD]       << endl;
   cout << endl;

   cout << "Confirming hands dealt: "                      \
        << hand_rank_count[hand_rank_t::HIGH_CARD]       + \
           hand_rank_count[hand_rank_t::ONE_PAIR]        + \
           hand_rank_count[hand_rank_t::TWO_PAIR]        + \
           hand_rank_count[hand_rank_t::THREE_OF_A_KIND] + \
           hand_rank_count[hand_rank_t::STRAIGHT]        + \
           hand_rank_count[hand_rank_t::FLUSH]           + \
           hand_rank_count[hand_rank_t::FULL_HOUSE]      + \
           hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  + \
           hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  + \
           hand_rank_count[hand_rank_t::ROYAL_FLUSH]       \
        << endl;

   cout << endl;

   double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

   cout << "Time taken by program is : " << fixed 
        << time_taken << setprecision(5);

   cout << " sec " << endl;
   cout << endl;
}

static const vector<card_t> &deck = deck_s::getInstance().getDeck();
static const hand_rank_table_s &hrt = hand_rank_table_s::getInstance();

static void operation_to_perform_1(const indexes_t &indexes)
{
   unsigned long long int hand_id(1);

   for (
          indexes_t::const_iterator i = indexes.begin();
          i != indexes.end();
          ++i
       )
   {
      hand_id *= deck[*i].get_id();
   }

   ++hand_rank_count[hrt[hand_id]];
   ++hands_dealt;
}
