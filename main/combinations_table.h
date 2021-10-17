#ifndef COMBINATIONS_TABLE_INCLUDED
#define COMBINATIONS_TABLE_INCLUDED

#include <array>

using namespace std;

#include "utilities.h"

// This singleton is lazily initialized
template<typename T, T N>
class combinations_table_s
{
   public:
      using combinations_table_t = array<array<T, N+1>, N+1>;

      combinations_table_s(const combinations_table_s &) = delete;
      void operator=(const combinations_table_s &) = delete;

      combinations_table_s(combinations_table_s &&) = delete;
      void operator=(combinations_table_s &&) = delete;

      combinations_table_s *operator&() = delete;

      static const combinations_table_s &getInstance();

      const combinations_table_t &getTable() const;
      T operator()(T i, T j) const;

   private:
      combinations_table_s();
      ~combinations_table_s();

      combinations_table_t combinations_table;
};

#include "combinations_table.inl"

#endif
