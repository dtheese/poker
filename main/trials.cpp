#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "deck.h"
#include "dynamic_loop_wrapper.h"
#include "hand.h"

#include "trials.h"

using namespace std;

trial_result_t::trial_result_t(const hand_t &hand_p, unsigned long long int hands_dealt_p):
   hand{hand_p},
   hands_dealt{hands_dealt_p}
{
}

// Support functions
static trial_result_t random_hands_until_target_hand_rank_hit(
                           hand_rank_t target_hand_rank,
                           unsigned long long int num_cards
                                                             );

// *****************************************************************************
void average_random_hands_until_target_hand_rank_hit(
                                                       hand_rank_t target_hand_rank,
                                                       unsigned long long int target_hand_count,
                                                       unsigned long long int num_cards
                                                    )
{
   cout << endl;
   cout << "average_random_hands_until_target_hand_rank_hit() called" << endl;
   cout << endl;

   vector<unsigned long long int> hands_dealt_v;

   hands_dealt_v.reserve(target_hand_count);

   for (unsigned long long int i = 0; i != target_hand_count; ++i)
   {
      auto trial_result(
         random_hands_until_target_hand_rank_hit(target_hand_rank, num_cards)
                       );

      auto hand_l(trial_result.hand);
      auto hands_dealt(trial_result.hands_dealt);

      hand_l.print();
      cout << endl;
      hands_dealt_v.push_back(hands_dealt);

      cout << "Hands dealt: " << hands_dealt << endl;
      cout << endl;
   }

   cout << endl;

   cout << "Average hands dealt: "
        << 1.0 * accumulate(
                              hands_dealt_v.begin(),
                              hands_dealt_v.end(),
                              0
                           ) / hands_dealt_v.size()
        << endl;

   cout << endl;
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// Support functions and variables

static vector<card_t> cards;
static hand_t hand;
static hand_rank_t highest_hand_seen{hand_rank_t::HIGH_CARD};

// *****************************************************************************
static void operation_to_perform_1(const indexes_t &indexes)
{
   card_t cards_1[5];
   unsigned int j{0};

   for (unsigned int i : indexes)
      cards_1[j++] = cards[i];

   hand_t hand_1{cards_1};

   if (hand_1.hand_rank() >= highest_hand_seen)
   {
      highest_hand_seen = hand_1.hand_rank();
      hand = hand_1;
   }
}

// Even though these are used only inside of random_hands_until_target_hand_rank_hit,
// define them outside of the function for the sake of speed. We don't want to be
// checking if they're initialized every time we enter the function.
//
// Seed a deterministic random number generator with a true random number.
static random_device rd;
static default_random_engine dre{rd()};

// *****************************************************************************
static trial_result_t random_hands_until_target_hand_rank_hit(
   hand_rank_t target_hand_rank,
   unsigned long long int num_cards
                                                             )
{
   unsigned long long int hands_dealt{0};

   while (true)
   {
      auto deck{deck_s::getInstance().getDeck()};

      cards.clear();
      cards.reserve(num_cards);

      highest_hand_seen = hand_rank_t::HIGH_CARD;

      for (unsigned int i{52}; i > 52 - num_cards; --i)
      {
         uniform_int_distribution<unsigned int> di{0, i - 1};
         unsigned int rand_num{di(dre)};

         cards.push_back(deck[rand_num]);
         deck.erase(deck.begin() + rand_num);
      }

      ++hands_dealt;
      dynamic_loop_wrapper(0, num_cards, 5, operation_to_perform_1);

      if (highest_hand_seen == target_hand_rank)
         return trial_result_t{hand, hands_dealt};
   }
}
