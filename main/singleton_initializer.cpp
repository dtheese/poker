#include "combinations_table.h"
#include "deck.h"
#include "hand_rank_lookup_table.h"

#include "singleton_initializer.h"

singleton_initializer_s singleton_initializer_s::instance;

singleton_initializer_s::singleton_initializer_s()
{
   // Explicitly initialize this program's lazily-initialized singletons.
   combinations_table_s<my_uint_t, 52>::getInstance();
   deck_s::getInstance();
   hand_rank_lookup_table_s::getInstance();
}

singleton_initializer_s::~singleton_initializer_s()
{
}
