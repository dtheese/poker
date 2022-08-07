#include <array>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

using namespace std;

#include "fundamental_types.h"

#include "combination_encoder.h"
#include "combinations_table.h"
#include "deck.h"
#include "dynamic_loop.h"
#include "dynamic_loop_functor.h"
#include "hand.h"
#include "hand_rank_lookup_table.h"
#include "parameters.h"
#include "print_mutex.h"
#include "utilities.h"

#include "iterations.h"

iteration_result_t::iteration_result_t()
{
}

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
   const my_uint_t MAX_HW_THREADS{thread::hardware_concurrency()};

   const auto NUM_THREADS{
                            min(
                                  {
                                     THREADS_LIMIT,
                                     combinations(52ULL, NUM_CARDS),
                                     MAX_HW_THREADS > 0 ? MAX_HW_THREADS : 1
                                  }
                               )
                         };

   iteration_result_t iterate_over_subset_of_hands(
                                                     const my_uint_t first_encoded_value,
                                                     const my_uint_t last_encoded_value
                                                  );

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

   cout << "Royal flush       "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::ROYAL_FLUSH]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::ROYAL_FLUSH]
        << endl;

   cout << "Straight flush    "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::STRAIGHT_FLUSH]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::STRAIGHT_FLUSH]
        << endl;

   cout << "Four of a kind    "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::FOUR_OF_A_KIND]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::FOUR_OF_A_KIND]
        << endl;

   cout << "Full house        "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::FULL_HOUSE]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::FULL_HOUSE]
        << endl;

   cout << "Flush             "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::FLUSH]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::FLUSH]
        << endl;

   cout << "Straight          "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::STRAIGHT]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::STRAIGHT]
        << endl;

   cout << "Three of a kind   "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::THREE_OF_A_KIND]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::THREE_OF_A_KIND]
        << endl;

   cout << "Two pair          "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::TWO_PAIR]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::TWO_PAIR]
        << endl;

   cout << "One pair          "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::ONE_PAIR]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::ONE_PAIR]
        << endl;

   cout << "High card         "
        << setw(15)
        << fixed
        << hand_rank_count_l[hand_rank_t::HIGH_CARD]
        << "     1 in "
        << setprecision(6)
        << static_cast<long double>(hands_dealt_l) /
           hand_rank_count_l[hand_rank_t::HIGH_CARD]
        << endl;

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

      {
         lock_guard<mutex> lg{print_mutex};

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
      }

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
