#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

#include <cassert>
#include <type_traits>

using namespace std;

template<typename T>
T &operator ++(T &e);

#include "utilities.inl"

#endif
