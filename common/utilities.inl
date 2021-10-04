template<typename T>
inline T &operator ++(T &e)
{
   if (e == T::End || e == T::None)
      assert(0);

    e = T(static_cast<typename underlying_type<T>::type>(e) + 1);

    return e;
}

template<typename T>
constexpr
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
