#include <iostream>
#include <numeric>

#include "deck.h"
#include "dynamic_loop.h"
#include "hand.h"

#include "iterations.h"

using namespace std;

iteration_result_t::iteration_result_t(
                     const map<hand_rank_t, unsigned long long int> hand_rank_count_p,
                     const unsigned long long int hands_dealt_p
                                      ):
   hand_rank_count{hand_rank_count_p},
   hands_dealt{hands_dealt_p}
{
}

// Support functions
namespace
{
   iteration_result_t iterate_over_all_possible_hands(unsigned long long int num_cards);
}

// *****************************************************************************
void evaluate_all_possible_hands(unsigned long long int num_cards)
{
   cout << endl;
   cout << "evaluate_all_possible_hands() called" << endl;
   cout << "num_cards = " << num_cards << endl;
   cout << endl;

   auto iteration_result(iterate_over_all_possible_hands(num_cards));
   auto hands_dealt_l(iteration_result.hands_dealt);
   auto hand_rank_count_l(iteration_result.hand_rank_count);

   cout << "Hands dealt: " << hands_dealt_l << endl;
   cout << endl;

   cout << "Royal flush       "  << hand_rank_count_l[hand_rank_t::ROYAL_FLUSH]     << endl;
   cout << "Straight flush    "  << hand_rank_count_l[hand_rank_t::STRAIGHT_FLUSH]  << endl;
   cout << "Four of a kind    "  << hand_rank_count_l[hand_rank_t::FOUR_OF_A_KIND]  << endl;
   cout << "Full house        "  << hand_rank_count_l[hand_rank_t::FULL_HOUSE]      << endl;
   cout << "Flush             "  << hand_rank_count_l[hand_rank_t::FLUSH]           << endl;
   cout << "Straight          "  << hand_rank_count_l[hand_rank_t::STRAIGHT]        << endl;
   cout << "Three of a kind   "  << hand_rank_count_l[hand_rank_t::THREE_OF_A_KIND] << endl;
   cout << "Two pair          "  << hand_rank_count_l[hand_rank_t::TWO_PAIR]        << endl;
   cout << "One pair          "  << hand_rank_count_l[hand_rank_t::ONE_PAIR]        << endl;
   cout << "High card         "  << hand_rank_count_l[hand_rank_t::HIGH_CARD]       << endl;
   cout << endl;

   cout << "Confirming hands dealt: "         \
        << hand_rank_count_l[hand_rank_t::HIGH_CARD]       + \
           hand_rank_count_l[hand_rank_t::ONE_PAIR]        + \
           hand_rank_count_l[hand_rank_t::TWO_PAIR]        + \
           hand_rank_count_l[hand_rank_t::THREE_OF_A_KIND] + \
           hand_rank_count_l[hand_rank_t::STRAIGHT]        + \
           hand_rank_count_l[hand_rank_t::FLUSH]           + \
           hand_rank_count_l[hand_rank_t::FULL_HOUSE]      + \
           hand_rank_count_l[hand_rank_t::FOUR_OF_A_KIND]  + \
           hand_rank_count_l[hand_rank_t::STRAIGHT_FLUSH]  + \
           hand_rank_count_l[hand_rank_t::ROYAL_FLUSH]       \
        << endl;

   cout << endl;
}

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

namespace
{
   // *****************************************************************************
   class dynamic_loop_functor_2_t
   {
      public:
         dynamic_loop_functor_2_t(const vector<card_t> &cards_p): cards(cards_p)
         {
         }

         dynamic_loop_functor_2_t(const dynamic_loop_functor_2_t &) = delete;
         dynamic_loop_functor_2_t &operator=(const dynamic_loop_functor_2_t &) = delete;

         dynamic_loop_functor_2_t(dynamic_loop_functor_2_t &&) = delete;
         dynamic_loop_functor_2_t &operator=(dynamic_loop_functor_2_t &&) = delete;

         void operator()(const indexes_t &indexes)
         {
            card_t cards_1[5];
            unsigned int j{0};

            for (unsigned int i : indexes)
               cards_1[j++] = cards[i];

            hand_t hand{cards_1};

            if (hand.hand_rank() > highest_hand_seen)
               highest_hand_seen = hand.hand_rank();
         }

         hand_rank_t getResult() const
         {
            return highest_hand_seen;
         }

      private:
         const vector<card_t> &cards;
         hand_rank_t highest_hand_seen{hand_rank_t::HIGH_CARD};
   };

   // *****************************************************************************
   class dynamic_loop_functor_1_t
   {
      public:
         dynamic_loop_functor_1_t()
         {
         }

         dynamic_loop_functor_1_t(const dynamic_loop_functor_1_t &) = delete;
         dynamic_loop_functor_1_t &operator=(const dynamic_loop_functor_1_t &) = delete;

         dynamic_loop_functor_1_t(dynamic_loop_functor_1_t &&) = delete;
         dynamic_loop_functor_1_t &operator=(dynamic_loop_functor_1_t &&) = delete;

         void operator()(const indexes_t &indexes)
         {
            cards.clear();

            for (unsigned int i : indexes)
               cards.push_back(deck[i]);

            dynamic_loop_functor_2_t dynamic_loop_functor_2(cards);

            dynamic_loop_t<dynamic_loop_functor_2_t> dynamic_loop(0, cards.size(), 5, dynamic_loop_functor_2);

            ++hand_rank_count[dynamic_loop_functor_2.getResult()];
            ++hands_dealt;
         }

         iteration_result_t getResult() const
         {
            return iteration_result_t(hand_rank_count, hands_dealt);
         }

      private:
         const vector<card_t> &deck{deck_s::getInstance().getDeck()};
         unsigned long long int hands_dealt{0};
         map<hand_rank_t, unsigned long long int> hand_rank_count;
         vector<card_t> cards;
   };

   // *****************************************************************************
   iteration_result_t iterate_over_all_possible_hands(unsigned long long int num_cards)
   {
      dynamic_loop_functor_1_t dynamic_loop_functor_1;

      dynamic_loop_t<dynamic_loop_functor_1_t> dynamic_loop(0, 52, num_cards, dynamic_loop_functor_1);

      return dynamic_loop_functor_1.getResult();
   }
}
