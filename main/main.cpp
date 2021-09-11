#include <chrono>
#include <iomanip>
#include <iostream>

#include "hand.h"
#include "iterations.h"
#include "trials.h"

using namespace std;

int main()
{
   system("date");

   auto start_time{chrono::steady_clock::now()};

#if 1
   // The parameter in this function call is the hand size (5 - 52).
   evaluate_all_possible_hands(5);
#else
   // The parameters in this function call are:
   //    * The target hand rank
   //    * The number of times the target hand rank must be achieved
   //    * The hand size (5 - 52)
   average_random_hands_until_target_hand_rank_hit(hand_rank_t::ROYAL_FLUSH, 100, 5);
#endif

   auto stop_time{chrono::steady_clock::now()};
   auto ticks_taken{stop_time - start_time};
   constexpr long double tick_interval{decltype(ticks_taken)::period::den};
   long double time_taken{static_cast<long double>(ticks_taken.count()) / tick_interval};

   cout << "Time taken by program is: " << fixed
        << setprecision(6) << time_taken << " seconds" << endl;

   cout << endl;
}
