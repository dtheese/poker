#include <chrono>
#include <iomanip>
#include <iostream>

#include "hand.h"
#include "iterations.h"
#include "parameters.h"
#include "trials.h"

using namespace std;

int main()
{
   system("date");

   auto start_time{chrono::steady_clock::now()};

   if (! MONTE_CARLO)
   {
      evaluate_all_possible_hands();
   }
   else
   {
      // The parameters in this function call are:
      //    * The target hand rank
      //    * The number of times the target hand rank must be achieved
      average_random_hands_until_target_hand_rank_hit(hand_rank_t::ROYAL_FLUSH, 20);
   }

   auto stop_time{chrono::steady_clock::now()};
   auto ticks_taken{stop_time - start_time};
   constexpr long double tick_interval{decltype(ticks_taken)::period::den};
   long double time_taken{static_cast<long double>(ticks_taken.count()) / tick_interval};

   cout << "Time taken by program is: " << fixed
        << setprecision(6) << time_taken << " seconds" << endl;

   cout << endl;
   system("date");
   cout << endl;
}
