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
              )
};
