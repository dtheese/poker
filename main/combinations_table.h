#ifndef COMBINATIONS_TABLE_INCLUDED
#define COMBINATIONS_TABLE_INCLUDED

// #include <array>

// using namespace std;

#include "fundamental_types.h"

#include "utilities.h"

// This singleton is lazily initialized
template<typename T, T N>
class combinations_table_s
{
   public:
      combinations_table_s(const combinations_table_s &) = delete;
      void operator=(const combinations_table_s &) = delete;

      combinations_table_s(combinations_table_s &&) = delete;
      void operator=(combinations_table_s &&) = delete;

      combinations_table_s *operator&() = delete;

      static const combinations_table_s &getInstance();

      T operator()(T i, T j) const;

   private:
      combinations_table_s();
      ~combinations_table_s();

      // array<array<T, N>, N> combinations_table;
      T combinations_table[N+1][N+1];
};

#include "combinations_table.inl"

#endif
