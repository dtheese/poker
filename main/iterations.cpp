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

   template<my_uint_t N, my_uint_t K>
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
   iteration_result_t iterate_over_subset_of_hands(
                                                     const my_uint_t first_encoding,
                                                     const my_uint_t last_encoding
                                                  )
   {
      const vector<card_t> &deck{deck_s::getInstance().getDeck()};
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

      for (auto encoded_value{first_encoding}; encoded_value <= last_encoding; ++encoded_value)
      {
         indexes_t indexes;
         decode<52ULL, NUM_CARDS>(encoded_value, indexes);

         vector<card_t> cards;

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
      }

      return iteration_result_t{hand_rank_count, last_encoding - first_encoding + 1};
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

   template<my_uint_t N, my_uint_t K>
   void decode(const my_uint_t encoded_value, vector<my_uint_t> &indexes)
   {
      my_uint_t offset{0};
      my_uint_t previous_index_selection{0};

      for (my_uint_t index{0}; index < K; ++index)
      {
         my_uint_t lowest_possible{index > 0 ? previous_index_selection + 1 : 0};
         my_uint_t highest_possible{N - K + index};

         // Find the *highest* ith index value whose offset increase gives a
         // total offset less than or equal to the value we're decoding.
         while (true)
         {
            my_uint_t candidate{(highest_possible + lowest_possible) / 2};

            my_uint_t offset_increase_due_to_candidate{
                           index > 0 ?
                              combinations(N - (indexes[index-1] + 1), K - index) -
                              combinations(N - candidate, K - index)
                                     :
                              combinations(N, K) -
                              combinations(N - candidate, K)
                                                      };

            if ((offset + offset_increase_due_to_candidate) > encoded_value)
            {
               // candidate is *not* the solution
               highest_possible = candidate - 1;
               continue;
            }

            // candidate *could* be the solution. Check if it is by checking if candidate + 1
            // could be the solution. That would rule out candidate being the solution.
            my_uint_t next_candidate{candidate + 1};

            my_uint_t offset_increase_due_to_next_candidate{
                           index > 0 ?
                              combinations(N - (indexes[index-1] + 1), K - index) -
                              combinations(N - next_candidate, K - index)
                                     :
                              combinations(N, K) -
                              combinations(N - next_candidate, K)
                                                      };

            if ((offset + offset_increase_due_to_next_candidate) <= encoded_value)
            {
               // candidate is *not* the solution
               lowest_possible = candidate + 1;
               continue;
            }

            // candidate *is* the solution
            offset += offset_increase_due_to_candidate;
            indexes.push_back(candidate);
            previous_index_selection = candidate;
            break;
         }
      }
   }
}
