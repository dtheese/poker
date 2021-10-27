#ifndef COMBINATION_ENCODER
#define COMBINATION_ENCODER

#include "combinations_table.h"
#include "utilities.h"

template<typename T, typename T::value_type N1, typename T::value_type K1>
class combination_encoder_t
{
   public:
      static
      typename T::value_type encode(const T &indexes);

      static
      void decode(const typename T::value_type encoded_value, T &indexes);

   private:
      using T1 = typename T::value_type;

      static
      const combinations_table_t<typename T::value_type, N1> &combinations_table;
};

#include "combination_encoder.inl"

#endif
