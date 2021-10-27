template<typename T>
inline
T &operator ++(T &e)
{
    e = T(static_cast<typename underlying_type<T>::type>(e) + 1);

    return e;
}

template<typename T>
constexpr
inline
T combinations(const T n, const T r)
{
   T k{r > n - r ? n - r : r};

   T rval{1};

   for (T i{1}; i <= k; ++i)
   {
      rval *= n - k + i;
      rval /= i;
   }

   return rval;
}

template<typename T>
constexpr
T power(T n, T r)
{
   T rval{1};

   while (true)
   {
      if (r & 1)
         rval *= n;

      r >>= 1;

      if (!r)
         break;

      n *= n;
   }

   return rval;
}

