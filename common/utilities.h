#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

#include <type_traits>

using namespace std;

template<typename T>
T &operator ++(T &e);

template<typename T>
constexpr
T combinations(const T n, const T r);

#include "utilities.inl"

#endif
