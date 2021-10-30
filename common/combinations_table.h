#ifndef COMBINATIONS_TABLE_INCLUDED
#define COMBINATIONS_TABLE_INCLUDED

#include <array>

using namespace std;

#include "utilities.h"

template<typename T, T N1>
using combinations_table_t = array<array<T, N1+1>, N1+1>;

// This singleton is lazily initialized
template<typename T, T N1>
class combinations_table_s
{
   public:
      combinations_table_s(const combinations_table_s &) = delete;
      void operator=(const combinations_table_s &) = delete;

      combinations_table_s(combinations_table_s &&) = delete;
      void operator=(combinations_table_s &&) = delete;

      combinations_table_s *operator&() = delete;

      static const combinations_table_s &getInstance();

      const combinations_table_t<T, N1> &getTable() const;

   private:
      explicit combinations_table_s();
      ~combinations_table_s();

      // Zero initialize all elements with {}
      combinations_table_t<T, N1> combinations_table{};
};

#include "combinations_table.inl"

#endif
