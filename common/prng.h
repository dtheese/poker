#ifndef PRNG_INCLUDED
#define PRNG_INCLUDED

#include <random>

using namespace std;

template<typename T>
class prng_t
{
   public:
      prng_t(const prng_t &) = delete;
      void operator=(const prng_t &) = delete;

      prng_t(prng_t &&) = delete;
      void operator=(prng_t &&) = delete;

      prng_t *operator&() = delete;

      prng_t(T min_value, T max_value);
      ~prng_t();

      T rand();

   private:
      // Default construct mt19937_64 so that a standard-defined test can be
      // conducted to test its correctness. (See constructor of this class.)
      mt19937_64 rand_eng;

      // Prepare a uniform random number generator. This should be used in
      // conjunction with the engine as follows:
      // T prn{di(rand_eng)};
      uniform_int_distribution<T> di;
};

#include "prng.inl"

#endif
