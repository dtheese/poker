#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

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
   const my_uint_t NUM_THREADS{thread::hardware_concurrency()};

   iteration_result_t iterate_over_all_possible_hands();
   void decode(const my_uint_t encoded_value, vector<my_uint_t> &indexes);
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
         dynamic_loop_functor_2_t(const dynamic_loop_functor_2_t &) = delete;
         dynamic_loop_functor_2_t &operator=(const dynamic_loop_functor_2_t &) = delete;

         dynamic_loop_functor_2_t(dynamic_loop_functor_2_t &&) = delete;
         dynamic_loop_functor_2_t &operator=(dynamic_loop_functor_2_t &&) = delete;
   };

   // *****************************************************************************
   class dynamic_loop_functor_1_t
   {
      public:
         dynamic_loop_functor_1_t(const dynamic_loop_functor_1_t &) = delete;
         dynamic_loop_functor_1_t &operator=(const dynamic_loop_functor_1_t &) = delete;

         dynamic_loop_functor_1_t(dynamic_loop_functor_1_t &&) = delete;
         dynamic_loop_functor_1_t &operator=(dynamic_loop_functor_1_t &&) = delete;
   };

   // *****************************************************************************
   iteration_result_t iterate_over_subset_of_hands(
                                                     const my_uint_t first_encoding,
                                                     const my_uint_t last_encoding
                                                  )
   {
      map<hand_rank_t, my_uint_t> hand_rank_count;
      my_uint_t hands_dealt{0};

      for (auto encoded_value{first_encoding}; encoded_value <= last_encoding; ++encoded_value)
      {
         // DCT: Resume work here!!!
         vector<my_uint_t> indexes;
         decode(encoded_value, indexes);

         // hand_rank_count[hand_rank_t::HIGH_CARD]       += one_hand_rank_count.at(hand_rank_t::HIGH_CARD);
         // hand_rank_count[hand_rank_t::ONE_PAIR]        += one_hand_rank_count.at(hand_rank_t::ONE_PAIR);
         // hand_rank_count[hand_rank_t::TWO_PAIR]        += one_hand_rank_count.at(hand_rank_t::TWO_PAIR);
         // hand_rank_count[hand_rank_t::THREE_OF_A_KIND] += one_hand_rank_count.at(hand_rank_t::THREE_OF_A_KIND);
         // hand_rank_count[hand_rank_t::STRAIGHT]        += one_hand_rank_count.at(hand_rank_t::STRAIGHT);
         // hand_rank_count[hand_rank_t::FLUSH]           += one_hand_rank_count.at(hand_rank_t::FLUSH);
         // hand_rank_count[hand_rank_t::FULL_HOUSE]      += one_hand_rank_count.at(hand_rank_t::FULL_HOUSE);
         // hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  += one_hand_rank_count.at(hand_rank_t::FOUR_OF_A_KIND);
         // hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  += one_hand_rank_count.at(hand_rank_t::STRAIGHT_FLUSH);
         // hand_rank_count[hand_rank_t::ROYAL_FLUSH]     += one_hand_rank_count.at(hand_rank_t::ROYAL_FLUSH);

         hands_dealt += (last_encoding - first_encoding + 1);
      }

      return iteration_result_t{hand_rank_count, hands_dealt};
   }

   // *****************************************************************************
   iteration_result_t iterate_over_all_possible_hands()
   {
      map<hand_rank_t, my_uint_t> hand_rank_count;
      my_uint_t hands_dealt{0};
      vector<future<iteration_result_t>> futures;
      const my_uint_t encoded_values_per_thread{combinations(52ULL, NUM_CARDS) / NUM_THREADS};

      for (my_uint_t i{0}; i < NUM_THREADS; ++i)
      {
         my_uint_t first_encoding{i * encoded_values_per_thread};
         my_uint_t last_encoding{(i + 1) * encoded_values_per_thread - 1};

         if (i == (NUM_THREADS - 1))
            last_encoding += combinations(52ULL, NUM_CARDS) % NUM_THREADS;

         cout << "Starting a thread to evaluate the hands corresponding to these encoded_values:" << endl;
         cout << "   First encoded_value: " << first_encoding << endl;
         cout << "   Last encoded_value: " << last_encoding << endl;

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

   void decode(const my_uint_t encoded_value, vector<my_uint_t> &indexes)
   {
      my_uint_t offset{0};
      my_uint_t previous_index_selection{0};

      for (my_uint_t index{0}; index < NUM_CARDS; ++index)
      {
         my_uint_t lowest_possible{index > 0 ? previous_index_selection + 1 : 0};
         my_uint_t highest_possible{52 - NUM_CARDS + index};

         // Find the *highest* ith index value whose offset increase gives a
         // total offset less than or equal to the value we're decoding.
         for (my_uint_t candidate{highest_possible}; candidate >= lowest_possible; --candidate)
         {
            my_uint_t offset_increase_due_to_candidate{
                           index > 0 ?
                              combinations(52ULL - (indexes[index-1] + 1), NUM_CARDS - index) -
                              combinations(52ULL - candidate, NUM_CARDS - index)
                                     :
                              combinations(52ULL, NUM_CARDS) -
                              combinations(52ULL - candidate, NUM_CARDS)
                                                      };

            if ((offset + offset_increase_due_to_candidate) <= encoded_value)
            {
               offset += offset_increase_due_to_candidate;
               indexes.push_back(candidate);
               previous_index_selection = candidate;
               break;
            }
         }
      }
   }
}
