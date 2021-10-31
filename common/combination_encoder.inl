template<typename T, typename T::value_type N1, typename T::value_type K1>
const combinations_table_t<typename T::value_type, N1>
&combination_encoder_t<T, N1, K1>::combinations_table{
     combinations_table_s<typename T::value_type, N1>::getInstance().getTable()
                                                     };

template<typename T, typename T::value_type N1, typename T::value_type K1>
inline
typename T::value_type combination_encoder_t<T, N1, K1>::encode(const T &indexes)
{
   // constexpr is a C++17 feature
   if constexpr (N1 == 52 && K1 == 5)
   {
      T1 offset{0};

      auto a0{indexes[0]};
      auto a1{indexes[1]};
      auto a2{indexes[2]};
      auto a3{indexes[3]};
      auto a4{indexes[4]};

      offset += a0*a0*a0*a0*a0 + 5*4801*a0*a0*a0 + 6*4797999*a0;
      offset += 30*33*a1*a1*a1 + 30*80817*a1;
      offset += 20*a2*a2*a2 + 20*7499*a2;
      offset += 60*101*a3;
      offset += 120*a4;

      offset -= 5*49*a0*a0*a0*a0 + 5*235151*a0*a0;
      offset -= 5*a1*a1*a1*a1 + 5*14699*a1*a1;
      offset -= 120*25*a2*a2;
      offset -= 60*a3*a3;
      offset -= ((T1) 120)*22152;

      offset /= (T1) 120;

      return offset;
   }
   else
   {
      auto offset{combinations_table[N1][K1] - combinations_table[N1 - indexes[0]][K1]};

      for (T1 index{1}; index < K1; ++index)
      {
         auto offset_due_to_current_index{
              combinations_table[N1 - (indexes[index-1] + 1)][K1 - index] -
              combinations_table[N1 - indexes[index]][K1 - index]
                                         };

         offset += offset_due_to_current_index;
      }

      return offset;
   }
}

template<typename T, typename T::value_type N1, typename T::value_type K1>
inline
void combination_encoder_t<T, N1, K1>::decode(const typename T::value_type encoded_value, T &indexes)
{
   auto n{N1};
   auto k{K1};
   auto x(encoded_value);
   T1 index{0};

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
