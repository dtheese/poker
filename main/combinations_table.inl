template<typename T, T M, T N>
inline combinations_table_s<T, M, N>::combinations_table_s()
{
   for (T i {0}; i <= M; ++i)
   {
      for (T j {0}; j <= N; ++j)
         combinations_table[i][j] = combinations(i, j);
   }
}

template<typename T, T M, T N>
inline combinations_table_s<T, M, N>::~combinations_table_s()
{
}

template<typename T, T M, T N>
inline const combinations_table_s<T, M, N> &combinations_table_s<T, M, N>::getInstance()
{
   static combinations_table_s<T, M, N> instance;

   return instance;
}

template<typename T, T M, T N>
inline const typename combinations_table_s<T, M, N>::combinations_table_t &combinations_table_s<T, M, N>::getTable() const
{
   return combinations_table;
}
