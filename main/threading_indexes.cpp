#include "threading_indexes.h"

using namespace std;

const start_card_indexes_by_num_threads_by_num_cards_t START_INDEXES
{
     make_pair(
                 5, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,6}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,4,10}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,3,6,12}
                               )
                 }
              ),
     make_pair(
                 6, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,5}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,3,8}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,2,5,10}
                               )
                 }
              ),
     make_pair(
                 7, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,5}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,3,7}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,2,5,9}
                               )
                 }
              ),
     make_pair(
                 8, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,4}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,2,6}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,2,4,8}
                               )
                 }
              ),
     make_pair(
                 9, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,4}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,2,6}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,2,4,7}
                               )
                 }
              ),
     make_pair(
                 10, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,3}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,2,5}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,3,6}
                               )
                 }
              ),
     make_pair(
                 11, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,3}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,2,4}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,3,6}
                               )
                 }
              ),
     make_pair(
                 12, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,3}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,4}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,3,5}
                               )
                 }
              ),
     make_pair(
                 13, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 14, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 15, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 16, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 17, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 18, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 19, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 20, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 21, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 22, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 23, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 24, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 25, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 26, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 27, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 28, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 29, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 30, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 31, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 32, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 33, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 34, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 35, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 36, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 37, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 38, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 39, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 40, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 41, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 42, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 43, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 44, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 45, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 46, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 47, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 48, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 49, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               ),
                      make_pair(
                                  4, // Number of threads
                                  start_card_indexes_t{0,1,2,3}
                               )
                 }
              ),
     make_pair(
                 50, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               ),
                      make_pair(
                                  3, // Number of threads
                                  start_card_indexes_t{0,1,2}
                               )
                 }
              ),
     make_pair(
                 51, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               ),
                      make_pair(
                                  2, // Number of threads
                                  start_card_indexes_t{0,1}
                               )
                 }
              ),
     make_pair(
                 52, // Number of cards
                 start_card_indexes_by_num_threads_t
                 {
                      make_pair(
                                  1, // Number of threads
                                  start_card_indexes_t{0}
                               )
                 }
              )
};
