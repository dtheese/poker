#include <array>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

using namespace std;

#include "fundamental_types.h"

#include "combination_encoder.h"
#include "combinations_table.h"
#include "deck.h"
#include "dynamic_loop.h"
#include "hand.h"
#include "hand_rank_lookup_table.h"
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
   const my_uint_t MAX_THREADS{thread::hardware_concurrency()};

   const my_uint_t NUM_THREADS{
                                 combinations(52ULL, NUM_CARDS) >= MAX_THREADS ?
                                 MAX_THREADS                                   :
                                 combinations(52ULL, NUM_CARDS)
                              };

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
   class dynamic_loop_functor_t
   {
      public:
         dynamic_loop_functor_t(const array<my_uint_t, NUM_CARDS> &indexes_all_p):
         indexes_all{indexes_all_p}
         {
         }

         dynamic_loop_functor_t(const dynamic_loop_functor_t &) = delete;
         dynamic_loop_functor_t &operator=(const dynamic_loop_functor_t &) = delete;

         dynamic_loop_functor_t(dynamic_loop_functor_t &&) = delete;
         dynamic_loop_functor_t &operator=(dynamic_loop_functor_t &&) = delete;

         void operator()(const indexes_t<my_uint_t> &indexes_5)
         {
            array<my_uint_t, 5> indexes_into_deck{};
            my_uint_t j{0};

            for (auto i : indexes_5)
               indexes_into_deck[j++] = indexes_all[i];

            auto encoded_value_5{
                 combination_encoder_t<decltype(indexes_into_deck), 52, 5>::
                 encode(indexes_into_deck)
                                };

            auto this_hands_rank{hand_rank_lookup_table[encoded_value_5]};

            if (this_hands_rank > highest_hand_seen)
               highest_hand_seen = this_hands_rank;
         }

         hand_rank_t getResult() const
         {
            return highest_hand_seen;
         }

      private:
         const
         hand_rank_lookup_table_t
         &hand_rank_lookup_table{hand_rank_lookup_table_s::getInstance().getLookupTable()};

         const array<my_uint_t, NUM_CARDS> &indexes_all;
         hand_rank_t highest_hand_seen{hand_rank_t::HIGH_CARD};
   };

   // *****************************************************************************
   iteration_result_t iterate_over_subset_of_hands(
                                                     const my_uint_t first_encoded_value,
                                                     const my_uint_t last_encoded_value
                                                  )
   {
      map<hand_rank_t, my_uint_t> hand_rank_count;

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

      for (
             auto encoded_value{first_encoded_value};
             encoded_value <= last_encoded_value;
             ++encoded_value
          )
      {
         array<my_uint_t, NUM_CARDS> indexes_all{};

         combination_encoder_t<decltype(indexes_all), 52, NUM_CARDS>::
              decode(encoded_value, indexes_all);

         dynamic_loop_functor_t dynamic_loop_functor{indexes_all};

         dynamic_loop_t<my_uint_t, dynamic_loop_functor_t> dynamic_loop{
                                                                 0,
                                                                 NUM_CARDS,
                                                                 5,
                                                                 dynamic_loop_functor
                                                                       };

         dynamic_loop.run();
         ++hand_rank_count[dynamic_loop_functor.getResult()];
      }

      return iteration_result_t{hand_rank_count, last_encoded_value - first_encoded_value + 1};
   }

   // *****************************************************************************
   iteration_result_t iterate_over_all_possible_hands()
   {
      const auto &combinations_table{combinations_table_s<my_uint_t, 52>::
           getInstance().getTable()};

      map<hand_rank_t, my_uint_t> hand_rank_count;
      my_uint_t hands_dealt{0};
      vector<future<iteration_result_t>> futures;
      const my_uint_t encoded_values_per_thread{combinations_table[52][NUM_CARDS] / NUM_THREADS};

      for (my_uint_t i{0}; i < NUM_THREADS; ++i)
      {
         my_uint_t first_encoded_value{i * encoded_values_per_thread};
         my_uint_t last_encoded_value{(i + 1) * encoded_values_per_thread - 1};

         if (i == (NUM_THREADS - 1))
            last_encoded_value += combinations_table[52][NUM_CARDS] % NUM_THREADS;

         cout << "Starting thread " << i
              << " to evaluate the hands corresponding to these encoded values:"
              << endl;

         cout << "   First encoded value: " << first_encoded_value << endl;
         cout << "   Last encoded value: " << last_encoded_value << endl;

         futures.push_back(
                             async(
                                     launch::async,
                                     iterate_over_subset_of_hands,
                                     first_encoded_value,
                                     last_encoded_value
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
