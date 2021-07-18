template<typename T>
inline T &operator ++(T &e)
{
   if (e == T::End || e == T::None)
      assert(0);

    e = T(static_cast<typename underlying_type<T>::type>(e) + 1);

    return e;
}
