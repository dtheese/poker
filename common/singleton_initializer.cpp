#include "deck.h"

#ifdef USE_TABLE
#include "hand_rank_table.h"
#include "primes.h"
#endif

#include "singleton_initializer.h"

singleton_initializer_s singleton_initializer_s::instance;

singleton_initializer_s::singleton_initializer_s()
{
   // Explicitly initialize this program's lazily-initialized singletons.
#ifdef USE_TABLE
   deck_s::getInstance();
   hand_rank_table_s::getInstance();
   primes_s::getInstance();
#else
   deck_s::getInstance();
#endif
}