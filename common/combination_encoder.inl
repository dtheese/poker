template<typename T, typename T::value_type N1, typename T::value_type K1>
const typename combinations_table_s<typename T::value_type, N1>::combinations_table_t
&combination_encoder_t<T, N1, K1>::combinations_table{
     combinations_table_s<typename T::value_type, N1>::getInstance().getTable()
                                                     };

template<typename T, typename T::value_type N1, typename T::value_type K1>
typename T::value_type combination_encoder_t<T, N1, K1>::encode(const T &indexes)
{
   auto offset{combinations_table[N1][K1] - combinations_table[N1 - indexes[0]][K1]};

   for (typename T::value_type index{1}; index < K1; ++index)
   {
      auto offset_due_to_current_index{
           combinations_table[N1 - (indexes[index-1] + 1)][K1 - index] -
           combinations_table[N1 - indexes[index]][K1 - index]
                                      };

      offset += offset_due_to_current_index;
   }

   return offset;
}

template<typename T, typename T::value_type N1, typename T::value_type K1>
void combination_encoder_t<T, N1, K1>::decode(const typename T::value_type encoded_value, T &indexes)
{
   auto n{N1};
   auto k{K1};
   auto x(encoded_value);
   typename T::value_type index{0};

   while (k != 0)
   {
      auto c{combinations_table[n-1][k-1]};

      if (x < c)
      {
         indexes[index++] = N1 - n;
         --k;
      }
      else
      {
         x -= c;
      }

      --n;
   }
}
