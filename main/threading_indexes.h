#ifndef THREADING_INDEXES_INCLUDED
#define THREADING_INDEXES_INCLUDED

#include <map>
#include <vector>

using namespace std;

#include "fundamental_types.h"

using num_cards_t        = my_uint_t;
using num_threads_t      = my_uint_t;
using start_card_index_t = my_uint_t;

using start_card_indexes_t = vector<start_card_index_t>;

using start_card_indexes_by_num_threads_t =
     map<num_threads_t, start_card_indexes_t>;

using start_card_indexes_by_num_threads_by_num_cards_t =
     map<num_cards_t, start_card_indexes_by_num_threads_t>;

extern const start_card_indexes_by_num_threads_by_num_cards_t START_INDEXES;

#endif
