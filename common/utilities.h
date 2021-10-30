#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

#include <type_traits>

using namespace std;

template<typename T>
constexpr
T &operator ++(T &e);

template<typename T>
constexpr
T combinations(const T n, const T r);

template<typename T>
constexpr
T power(T n, T r);

#include "utilities.inl"

#endif
