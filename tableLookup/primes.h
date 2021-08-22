#ifndef PRIMES_INCLUDED
#define PRIMES_INCLUDED

using namespace std;

// This singleton is lazily initialized.
class primes_s
{
   public:
      primes_s(const primes_s &) = delete;
      primes_s(primes_s &) = delete;

      primes_s(const primes_s &&) = delete;
      primes_s(primes_s &&) = delete;

      void operator=(const primes_s &) = delete;
      void operator=(primes_s &) = delete;

      void operator=(const primes_s &&) = delete;
      void operator=(primes_s &&) = delete;

      primes_s *operator&() = delete;

      static const primes_s &getInstance();

      const unsigned long long int &operator[](unsigned int i) const;

   private:
      primes_s();
      ~primes_s();

      unsigned long long int primes[52];
};

#include "primes.inl"

#endif
