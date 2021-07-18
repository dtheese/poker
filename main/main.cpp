#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <time.h>

#include "hand.h"
#include "iterations.h"
#include "trials.h"

using namespace std;

int main()
{
   system("date");

   clock_t start, end;

   start = clock();

#if 1
   evaluate_all_possible_hands(5);
#else
   average_random_hands_until_target_hand_rank_hit(hand_rank_t::ROYAL_FLUSH, 300, 5);
#endif

   end = clock();
   double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

   cout << "Time taken by program is : " << fixed 
        << time_taken << setprecision(5);

   cout << " sec " << endl;
   cout << endl;
}
