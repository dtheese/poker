#include <chrono>
#include <iomanip>
#include <iostream>

#include "hand.h"
#include "iterations.h"
#include "monte_carlo.h"
#include "parameters.h"

using namespace std;

int main()
{
#ifndef _WIN32
   system("date");
#endif

   auto start_time{chrono::steady_clock::now()};

   if constexpr (TRIALS == 0)
      evaluate_all_possible_hands();
   else
      monte_carlo_simulation();

   auto stop_time{chrono::steady_clock::now()};
   auto ticks_taken{stop_time - start_time};
   constexpr long double tick_interval{decltype(ticks_taken)::period::den};
   long double time_taken{static_cast<long double>(ticks_taken.count()) / tick_interval};

   cout << "Time taken by program is: " << fixed
        << setprecision(6) << time_taken << " seconds" << endl;

   cout << endl;

#ifndef _WIN32
   system("date");
#endif

   cout << endl;
}
