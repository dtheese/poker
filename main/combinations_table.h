#ifndef COMBINATIONS_TABLE_INCLUDED
#define COMBINATIONS_TABLE_INCLUDED

#include "fundamental_types.h"
#include "utilities.h"

// This singleton is lazily initialized
class combinations_table_s
{
   public:
      combinations_table_s(const combinations_table_s &) = delete;
      void operator=(const combinations_table_s &) = delete;

      combinations_table_s(combinations_table_s &&) = delete;
      void operator=(combinations_table_s &&) = delete;

      combinations_table_s *operator&() = delete;

      static const combinations_table_s &getInstance();

      my_uint_t operator()(my_uint_t i, my_uint_t j);

   private:
      combinations_table_s();
      ~combinations_table_s();

      my_uint_t combinations_table[52][52];
};

#include "combinations_table.inl"

#endif
