#include <array>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

using namespace std;

#include "fundamental_types.h"

#include "combinations_table.h"
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
   const my_uint_t MAX_THREADS{thread::hardware_concurrency()};

   const my_uint_t NUM_THREADS{
                                 combinations(52ULL, NUM_CARDS) >= MAX_THREADS ?
                                 MAX_THREADS                                      :
                                 combinations(52ULL, NUM_CARDS)
                              };

   iteration_result_t iterate_over_all_possible_hands();

   template<typename T, T N, T K>
   void decode(const T encoded_value, array<T, K> &indexes);
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
         dynamic_loop_functor_t(const array<card_t, NUM_CARDS> &cards_p): cards{cards_p}
         {
         }

         dynamic_loop_functor_t(const dynamic_loop_functor_t &) = delete;
         dynamic_loop_functor_t &operator=(const dynamic_loop_functor_t &) = delete;

         dynamic_loop_functor_t(dynamic_loop_functor_t &&) = delete;
         dynamic_loop_functor_t &operator=(dynamic_loop_functor_t &&) = delete;

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
         const array<card_t, NUM_CARDS> &cards;
         hand_rank_t highest_hand_seen{hand_rank_t::HIGH_CARD};
   };

   // *****************************************************************************
   iteration_result_t iterate_over_subset_of_hands(
                                                     const my_uint_t first_encoded_value,
                                                     const my_uint_t last_encoded_value
                                                  )
   {
      const auto &deck{deck_s::getInstance().getDeck()};
      map<hand_rank_t, my_uint_t> hand_rank_count;
      array<my_uint_t, NUM_CARDS> indexes;

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

      for (auto encoded_value{first_encoded_value}; encoded_value <= last_encoded_value; ++encoded_value)
      {
         decode<my_uint_t, 52, NUM_CARDS>(encoded_value, indexes);

         array<card_t, NUM_CARDS> cards;
         my_uint_t j{0};

         for (auto i : indexes)
            cards[j++] = deck[i];

         dynamic_loop_functor_t dynamic_loop_functor{cards};

         dynamic_loop_t<dynamic_loop_functor_t> dynamic_loop{
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
      const auto &combinations_table{combinations_table_s<my_uint_t, 52, 52>::getInstance().getTable()};
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

         cout << "Starting thread " << i << " to evaluate the hands corresponding to these encoded_values:" << endl;
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

   template<typename T, T N, T K>
   void decode(const T encoded_value, array<T, K> &indexes)
   {
      static const auto &combinations_table{combinations_table_s<T, N, N>::getInstance().getTable()};

      T offset{0};
      T previous_index_selection{0};

      for (T index{0}; index < K; ++index)
      {
         T lowest_possible{index > 0 ? previous_index_selection + 1 : 0};
         T highest_possible{N - K + index};

         // Find the *highest* ith index value whose offset increase gives a
         // total offset less than or equal to the value we're decoding.
         while (true)
         {
            T candidate{(highest_possible + lowest_possible) / 2};

            T offset_increase_due_to_candidate{
                           index > 0 ?
                              combinations_table[N - (indexes[index-1] + 1)][K - index] -
                              combinations_table[N - candidate][K - index]
                                     :
                              combinations_table[N][K] -
                              combinations_table[N - candidate][K]
                                              };

            if ((offset + offset_increase_due_to_candidate) > encoded_value)
            {
               // candidate is *not* the solution
               highest_possible = candidate - 1;
               continue;
            }

            // candidate *could* be the solution. Check if it is by checking if candidate + 1
            // could be the solution. That would rule out candidate being the solution.
            T next_candidate{candidate + 1};

            T offset_increase_due_to_next_candidate{
                           index > 0 ?
                              combinations_table[N - (indexes[index-1] + 1)][K - index] -
                              combinations_table[N - next_candidate][K - index]
                                     :
                              combinations_table[N][K] -
                              combinations_table[N - next_candidate][K]
                                                   };

            if ((offset + offset_increase_due_to_next_candidate) <= encoded_value)
            {
               // candidate is *not* the solution
               lowest_possible = candidate + 1;
               continue;
            }

            // candidate *is* the solution
            offset += offset_increase_due_to_candidate;
            indexes[index] = candidate;
            previous_index_selection = candidate;
            break;
         }
      }
   }
}
