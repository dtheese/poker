#include <future>
#include <iostream>
#include <numeric>
#include <thread>

using namespace std;

#include "fundamental_types.h"

#include "deck.h"
#include "dynamic_loop.h"
#include "hand.h"
#include "parameters.h"
#include "utilities.h"

#include "iterations.h"

iteration_result_t::iteration_result_t(
                     const map<hand_rank_t, my_uint_t> hand_rank_count_p,
                     const my_uint_t hands_dealt_p
                                      ):
                     hand_rank_count{hand_rank_count_p},
                     hands_dealt{hands_dealt_p}
{
}

namespace
{
   const unsigned int NUM_THREADS{thread::hardware_concurrency()};

   iteration_result_t iterate_over_all_possible_hands();
}

// *****************************************************************************
void evaluate_all_possible_hands()
{
   cout << endl;
   cout << "evaluate_all_possible_hands() called" << endl;
   cout << "Number of cards in a hand: " << NUM_CARDS << endl;
   cout << "Number of threads: " << NUM_THREADS << endl;
   cout << endl;

   auto iteration_result{iterate_over_all_possible_hands()};
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

   cout << "Confirming hands dealt: "                        \
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
            my_uint_t j{0};

            for (auto i : indexes)
               cards_1[j++] = cards[i];

            hand_t hand{cards_1};
            auto this_hands_rank{hand.hand_rank()};

            if (this_hands_rank > highest_hand_seen)
               highest_hand_seen = this_hands_rank;
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
         dynamic_loop_functor_1_t(my_uint_t first_index_p): first_index{first_index_p}
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

         dynamic_loop_functor_1_t(dynamic_loop_functor_1_t &&) = delete;
         dynamic_loop_functor_1_t &operator=(dynamic_loop_functor_1_t &&) = delete;

         void operator()(const indexes_t &indexes)
         {
            cards.clear();
            cards.push_back(deck[first_index]);

            for (auto i : indexes)
               cards.push_back(deck[i]);

            dynamic_loop_functor_2_t dynamic_loop_functor_2{cards};

            dynamic_loop_t<dynamic_loop_functor_2_t> dynamic_loop{
                                                                    0,
                                                                    static_cast<my_uint_t>(cards.size()),
                                                                    5,
                                                                    dynamic_loop_functor_2
                                                                 };

            dynamic_loop.run();
            ++hand_rank_count[dynamic_loop_functor_2.getResult()];
            ++hands_dealt;
         }

         const map<hand_rank_t, my_uint_t> &getHandRankCount() const
         {
            return hand_rank_count;
         }

         my_uint_t getHandsDealt() const
         {
            return hands_dealt;
         }

      private:
         const vector<card_t> &deck{deck_s::getInstance().getDeck()};
         my_uint_t hands_dealt{0};
         map<hand_rank_t, my_uint_t> hand_rank_count;
         vector<card_t> cards;
         const my_uint_t first_index;
   };

   // *****************************************************************************
   iteration_result_t iterate_over_subset_of_hands(
                                                     const my_uint_t first_initial_index,
                                                     const my_uint_t last_initial_index
                                                  )
   {
      map<hand_rank_t, my_uint_t> hand_rank_count;
      my_uint_t hands_dealt{0};

      for (auto first_index{first_initial_index}; first_index <= last_initial_index; ++first_index)
      {
         dynamic_loop_functor_1_t dynamic_loop_functor_1{first_index};

         dynamic_loop_t<dynamic_loop_functor_1_t> dynamic_loop{
                                                                 first_index + 1,
                                                                 52 - first_index - 1,
                                                                 NUM_CARDS - 1,
                                                                 dynamic_loop_functor_1
                                                              };

         dynamic_loop.run();

         const auto &one_hand_rank_count{dynamic_loop_functor_1.getHandRankCount()};
         const auto one_hands_dealt{dynamic_loop_functor_1.getHandsDealt()};

         hand_rank_count[hand_rank_t::HIGH_CARD]       += one_hand_rank_count.at(hand_rank_t::HIGH_CARD);
         hand_rank_count[hand_rank_t::ONE_PAIR]        += one_hand_rank_count.at(hand_rank_t::ONE_PAIR);
         hand_rank_count[hand_rank_t::TWO_PAIR]        += one_hand_rank_count.at(hand_rank_t::TWO_PAIR);
         hand_rank_count[hand_rank_t::THREE_OF_A_KIND] += one_hand_rank_count.at(hand_rank_t::THREE_OF_A_KIND);
         hand_rank_count[hand_rank_t::STRAIGHT]        += one_hand_rank_count.at(hand_rank_t::STRAIGHT);
         hand_rank_count[hand_rank_t::FLUSH]           += one_hand_rank_count.at(hand_rank_t::FLUSH);
         hand_rank_count[hand_rank_t::FULL_HOUSE]      += one_hand_rank_count.at(hand_rank_t::FULL_HOUSE);
         hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  += one_hand_rank_count.at(hand_rank_t::FOUR_OF_A_KIND);
         hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  += one_hand_rank_count.at(hand_rank_t::STRAIGHT_FLUSH);
         hand_rank_count[hand_rank_t::ROYAL_FLUSH]     += one_hand_rank_count.at(hand_rank_t::ROYAL_FLUSH);

         hands_dealt += one_hands_dealt;
      }

      return iteration_result_t{hand_rank_count, hands_dealt};
   }

   // *****************************************************************************
   iteration_result_t iterate_over_all_possible_hands()
   {
      map<hand_rank_t, my_uint_t> hand_rank_count;
      my_uint_t hands_dealt{0};
      vector<future<iteration_result_t>> futures;
      const unsigned long long int encodings_per_thread{combinations(52ULL, NUM_CARDS) / NUM_THREADS};

      for (my_uint_t i{0}; i < NUM_THREADS; ++i)
      {
         // DCT: Handle cases where encoding_per_thread did not divide evenly!
         unsigned long long int first_encoding{i * encodings_per_thread};
         unsigned long long int last_encoding{(i + 1) * encodings_per_thread - 1};

         cout << "Starting a thread to evaluate the hands corresponding to these encodings:" << endl;
         cout << "   First encoding: " << first_encoding << endl;
         cout << "   Last encoding: " << last_encoding << endl;

         futures.push_back(
                             async(
                                     launch::async,
                                     iterate_over_subset_of_hands,
                                     first_encoding,
                                     last_encoding
                                  )
                          );
      }

      cout << endl;

      for (my_uint_t i{0}; i < NUM_THREADS; ++i)
      {
         auto results{futures[i].get()};

         hand_rank_count[hand_rank_t::HIGH_CARD]       += results.hand_rank_count.at(hand_rank_t::HIGH_CARD);
         hand_rank_count[hand_rank_t::ONE_PAIR]        += results.hand_rank_count.at(hand_rank_t::ONE_PAIR);
         hand_rank_count[hand_rank_t::TWO_PAIR]        += results.hand_rank_count.at(hand_rank_t::TWO_PAIR);
         hand_rank_count[hand_rank_t::THREE_OF_A_KIND] += results.hand_rank_count.at(hand_rank_t::THREE_OF_A_KIND);
         hand_rank_count[hand_rank_t::STRAIGHT]        += results.hand_rank_count.at(hand_rank_t::STRAIGHT);
         hand_rank_count[hand_rank_t::FLUSH]           += results.hand_rank_count.at(hand_rank_t::FLUSH);
         hand_rank_count[hand_rank_t::FULL_HOUSE]      += results.hand_rank_count.at(hand_rank_t::FULL_HOUSE);
         hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  += results.hand_rank_count.at(hand_rank_t::FOUR_OF_A_KIND);
         hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  += results.hand_rank_count.at(hand_rank_t::STRAIGHT_FLUSH);
         hand_rank_count[hand_rank_t::ROYAL_FLUSH]     += results.hand_rank_count.at(hand_rank_t::ROYAL_FLUSH);

         hands_dealt += results.hands_dealt;
      }

      return iteration_result_t{hand_rank_count, hands_dealt};
   }
}
