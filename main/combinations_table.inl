template<typename T, T N1>
inline combinations_table_s<T, N1>::combinations_table_s()
{
   for (T n {0}; n <= N1; ++n)
   {
      for (T k {0}; k <= n; ++k)
         combinations_table[n][k] = combinations(n, k);
   }
}

template<typename T, T N1>
inline combinations_table_s<T, N1>::~combinations_table_s()
{
}

template<typename T, T N1>
inline const combinations_table_s<T, N1> &combinations_table_s<T, N1>::getInstance()
{
   static combinations_table_s<T, N1> instance;

   return instance;
}

template<typename T, T N1>
inline const typename combinations_table_s<T, N1>::combinations_table_t
       &combinations_table_s<T, N1>::getTable() const
{
   return combinations_table;
}
