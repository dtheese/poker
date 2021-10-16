#ifndef PRIMES_INCLUDED
#define PRIMES_INCLUDED

#include "fundamental_types.h"

// This singleton is lazily initialized.
class primes_s
{
   public:
      primes_s(const primes_s &) = delete;
      void operator=(const primes_s &) = delete;

      primes_s(primes_s &&) = delete;
      void operator=(primes_s &&) = delete;

      primes_s *operator&() = delete;

      static const primes_s &getInstance();

      const my_uint_t &operator[](my_uint_t i) const;

   private:
      primes_s();
      ~primes_s();

      my_uint_t primes[52];
};

#include "primes.inl"

#endif
