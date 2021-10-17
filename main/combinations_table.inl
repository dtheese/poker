template<typename T, T N>
inline combinations_table_s<T, N>::combinations_table_s()
{
   for (T i {0}; i <= N; ++i)
   {
      for (T j {0}; j <= N; ++j)
         combinations_table[i][j] = combinations(i, j);
   }
}

template<typename T, T N>
inline combinations_table_s<T, N>::~combinations_table_s()
{
}

template<typename T, T N>
inline const combinations_table_s<T, N> &combinations_table_s<T, N>::getInstance()
{
   static combinations_table_s<T, N> instance;

   return instance;
}

template<typename T, T N>
const typename combinations_table_s<T, N>::combinations_table_t &combinations_table_s<T, N>::getTable() const
{
   return combinations_table;
}
