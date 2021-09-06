#include <future>
#include <iostream>
#include <numeric>
#include <thread>

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
   iteration_result_t iterate_over_all_possible_hands(unsigned int num_cards);
}

// *****************************************************************************
void evaluate_all_possible_hands(unsigned int num_cards)
{
   cout << endl;
   cout << "evaluate_all_possible_hands() called" << endl;
   cout << "num_cards = " << num_cards << endl;
   cout << endl;

   auto iteration_result{iterate_over_all_possible_hands(num_cards)};
   auto hands_dealt_l{iteration_result.hands_dealt};
   auto hand_rank_count_l{iteration_result.hand_rank_count};

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
         dynamic_loop_functor_2_t(const vector<card_t> &cards_p): cards{cards_p}
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
         dynamic_loop_functor_1_t(unsigned int first_index_p): first_index{first_index_p}
         {
            hand_rank_count[hand_rank_t::HIGH_CARD]       = 0;
            hand_rank_count[hand_rank_t::ONE_PAIR]        = 0;
            hand_rank_count[hand_rank_t::TWO_PAIR]        = 0;
            hand_rank_count[hand_rank_t::THREE_OF_A_KIND] = 0;
            hand_rank_count[hand_rank_t::STRAIGHT]        = 0;
            hand_rank_count[hand_rank_t::FLUSH]           = 0;
            hand_rank_count[hand_rank_t::FULL_HOUSE]      = 0;
            hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  = 0;
            hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  = 0;
            hand_rank_count[hand_rank_t::ROYAL_FLUSH]     = 0;
         }

         dynamic_loop_functor_1_t(const dynamic_loop_functor_1_t &) = delete;
         dynamic_loop_functor_1_t &operator=(const dynamic_loop_functor_1_t &) = delete;

         // The move constructor is needed when constructing an arry of dynamic_loop_functor_1_t
         // dynamic_loop_functor_1_t(dynamic_loop_functor_1_t &&) = delete;
         dynamic_loop_functor_1_t &operator=(dynamic_loop_functor_1_t &&) = delete;

         void operator()(const indexes_t &indexes)
         {
            cards.clear();
            cards.push_back(deck[first_index]);

            for (unsigned int i : indexes)
               cards.push_back(deck[i]);

            dynamic_loop_functor_2_t dynamic_loop_functor_2{cards};

            dynamic_loop_t<dynamic_loop_functor_2_t> dynamic_loop{
                                                                    0,
                                                                    static_cast<unsigned int>(cards.size()),
                                                                    5,
                                                                    dynamic_loop_functor_2
                                                                 };

            dynamic_loop.run();
            ++hand_rank_count[dynamic_loop_functor_2.getResult()];
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
         unsigned long long int hands_dealt{0};
         map<hand_rank_t, unsigned long long int> hand_rank_count;
         vector<card_t> cards;
         unsigned int first_index;
   };

   // *****************************************************************************
   iteration_result_t iterate_over_all_possible_hands(unsigned int num_cards)
   {
      map<hand_rank_t, unsigned long long int> hand_rank_count;
      unsigned long long int hands_dealt{0};

      for (unsigned int first_index{0}; first_index <= 47; first_index += 2)
      {
         dynamic_loop_functor_1_t dynamic_loop_functor_1[]{{first_index}, {first_index + 1}};

         dynamic_loop_t<dynamic_loop_functor_1_t> dynamic_loop[]{
                                                                   {
                                                                      first_index + 1,
                                                                      52 - first_index - 1,
                                                                      num_cards - 1,
                                                                      dynamic_loop_functor_1[0]
                                                                   },
                                                                   {
                                                                      (first_index + 1) + 1,
                                                                      52 - (first_index + 1) - 1,
                                                                      num_cards - 1,
                                                                      dynamic_loop_functor_1[1]
                                                                   }
                                                                };

         future<void> f[]{
                            async(
                                    launch::async,
                                    &dynamic_loop_t<dynamic_loop_functor_1_t>::run,
                                    &dynamic_loop[0]
                                 ),
                            async(
                                    launch::async,
                                    &dynamic_loop_t<dynamic_loop_functor_1_t>::run,
                                    &dynamic_loop[1]
                                 )
                         };

         f[0].get();
         f[1].get();

         const map<hand_rank_t, unsigned long long int> one_hand_rank_count[]{
                                                                                ref(dynamic_loop_functor_1[0].getHandRankCount()),
                                                                                ref(dynamic_loop_functor_1[1].getHandRankCount())
                                                                             };

         unsigned long long int one_hands_dealt[]{
                                                    dynamic_loop_functor_1[0].getHandsDealt(),
                                                    dynamic_loop_functor_1[1].getHandsDealt()
                                                 };
         for (unsigned int i{0}; i <= 1; ++i)
         {
            hand_rank_count[hand_rank_t::HIGH_CARD]       += one_hand_rank_count[i].at(hand_rank_t::HIGH_CARD);
            hand_rank_count[hand_rank_t::ONE_PAIR]        += one_hand_rank_count[i].at(hand_rank_t::ONE_PAIR);
            hand_rank_count[hand_rank_t::TWO_PAIR]        += one_hand_rank_count[i].at(hand_rank_t::TWO_PAIR);
            hand_rank_count[hand_rank_t::THREE_OF_A_KIND] += one_hand_rank_count[i].at(hand_rank_t::THREE_OF_A_KIND);
            hand_rank_count[hand_rank_t::STRAIGHT]        += one_hand_rank_count[i].at(hand_rank_t::STRAIGHT);
            hand_rank_count[hand_rank_t::FLUSH]           += one_hand_rank_count[i].at(hand_rank_t::FLUSH);
            hand_rank_count[hand_rank_t::FULL_HOUSE]      += one_hand_rank_count[i].at(hand_rank_t::FULL_HOUSE);
            hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  += one_hand_rank_count[i].at(hand_rank_t::FOUR_OF_A_KIND);
            hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  += one_hand_rank_count[i].at(hand_rank_t::STRAIGHT_FLUSH);
            hand_rank_count[hand_rank_t::ROYAL_FLUSH]     += one_hand_rank_count[i].at(hand_rank_t::ROYAL_FLUSH);

            hands_dealt += one_hands_dealt[i];
         }
      }

      return iteration_result_t{hand_rank_count, hands_dealt};
   }
}
