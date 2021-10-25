#include <chrono>
#include <iomanip>
#include <iostream>

#include "hand.h"
#include "iterations.h"
#include "parameters.h"

using namespace std;

int main()
{
   system("date");

   auto start_time{chrono::steady_clock::now()};

   evaluate_all_possible_hands();

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
