#include <future>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

using namespace std;

#include "combination_encoder.h"
#include "dynamic_loop_functor.h"
#include "fundamental_types.h"
#include "parameters.h"
#include "print_mutex.h"
#include "utilities.h"

#include "monte_carlo.h"

namespace
{
   constexpr my_uint_t NUM_HANDS{combinations(52ULL, NUM_CARDS)};

   const my_uint_t MAX_HW_THREADS{thread::hardware_concurrency()};

   const auto NUM_THREADS{
                            min(
                                  {
                                     THREADS_LIMIT,
                                     MAX_HW_THREADS > 0 ? MAX_HW_THREADS : 1,
                                     TRIALS
                                  }
                               )
                         };

   // Seed a deterministic random number generator with a true random number.
   // Prepare a uniform random number generator.
   random_device rd;
   default_random_engine dre{rd()};
   uniform_int_distribution<my_uint_t> di{0, NUM_HANDS - 1};

   map<hand_rank_t, my_uint_t> iterate_over_subset_of_trials(const my_uint_t trials);
}

void monte_carlo_simulation()
{
   my_uint_t trials_per_thread{TRIALS / NUM_THREADS};

   cout << endl;
   cout << "monte_carlo_simulation() called" << endl;
   cout << "Number of trials: " << TRIALS << endl;
   cout << "Number of threads: " << NUM_THREADS << endl;
   cout << "Trials per thread: " << trials_per_thread << endl;
   cout << "Extra trials for last thread: " << TRIALS % NUM_THREADS << endl;
   cout << "Number of cards in a hand: " << NUM_CARDS << endl;
   cout << endl;

   map<hand_rank_t, my_uint_t> hand_rank_count;

   vector<future<map<hand_rank_t, my_uint_t>>> futures;

   {
      lock_guard<mutex> lg{print_mutex};

      for (my_uint_t i{0}; i < NUM_THREADS; ++i)
      {
         if (i == (NUM_THREADS - 1))
            trials_per_thread += TRIALS % NUM_THREADS;

         cout << "Starting thread " << i
              << " to run " << trials_per_thread << " trials"
              << endl;

         futures.push_back(
                             async(
                                     launch::async,
                                     iterate_over_subset_of_trials,
                                     trials_per_thread
                                  )
                          );
      }

      cout << endl;
   }

   for (my_uint_t i{0}; i < NUM_THREADS; ++i)
   {
      auto results{futures[i].get()};

      hand_rank_count[hand_rank_t::HIGH_CARD]       += results.at(hand_rank_t::HIGH_CARD);
      hand_rank_count[hand_rank_t::ONE_PAIR]        += results.at(hand_rank_t::ONE_PAIR);
      hand_rank_count[hand_rank_t::TWO_PAIR]        += results.at(hand_rank_t::TWO_PAIR);
      hand_rank_count[hand_rank_t::THREE_OF_A_KIND] += results.at(hand_rank_t::THREE_OF_A_KIND);
      hand_rank_count[hand_rank_t::STRAIGHT]        += results.at(hand_rank_t::STRAIGHT);
      hand_rank_count[hand_rank_t::FLUSH]           += results.at(hand_rank_t::FLUSH);
      hand_rank_count[hand_rank_t::FULL_HOUSE]      += results.at(hand_rank_t::FULL_HOUSE);
      hand_rank_count[hand_rank_t::FOUR_OF_A_KIND]  += results.at(hand_rank_t::FOUR_OF_A_KIND);
      hand_rank_count[hand_rank_t::STRAIGHT_FLUSH]  += results.at(hand_rank_t::STRAIGHT_FLUSH);
      hand_rank_count[hand_rank_t::ROYAL_FLUSH]     += results.at(hand_rank_t::ROYAL_FLUSH);
   }

   my_uint_t count{};
   long double frequency{};

   count = hand_rank_count[hand_rank_t::ROYAL_FLUSH];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Royal flush       "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::STRAIGHT_FLUSH];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Straight flush    "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::FOUR_OF_A_KIND];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Four of a kind    "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::FULL_HOUSE];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Full house        "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::FLUSH];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Flush             "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::STRAIGHT];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Straight          "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::THREE_OF_A_KIND];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Three of a kind   "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::TWO_PAIR];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "Two pair          "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::ONE_PAIR];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "One pair          "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

   count = hand_rank_count[hand_rank_t::HIGH_CARD];
   frequency = static_cast<long double>(TRIALS) / count;
   cout << "High card         "  << setw(15) << fixed << count     << "     1 in " << setprecision(6) << frequency << endl;

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
}

namespace
{
   map<hand_rank_t, my_uint_t> iterate_over_subset_of_trials(const my_uint_t trials)
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

      // Count down instead of up to suppress this warning:
      // comparison of unsigned expression < 0 is always false
      // for (my_uint_t i{0}; i < trials; ++i)

      for (my_uint_t i{trials}; i != 0; --i)
      {
         auto encoded_value{di(dre)};

         array<my_uint_t, NUM_CARDS> indexes{};

         combination_encoder_t<decltype(indexes), 52, NUM_CARDS>::
              decode(encoded_value, indexes);

         dynamic_loop_functor_t dynamic_loop_functor{indexes};

         dynamic_loop_t<my_uint_t, dynamic_loop_functor_t> dynamic_loop{
                                                                 0,
                                                                 NUM_CARDS,
                                                                 5,
                                                                 dynamic_loop_functor
                                                                       };

         dynamic_loop.run();
         ++hand_rank_count[dynamic_loop_functor.getResult()];
      }

      return hand_rank_count;
   }
}
