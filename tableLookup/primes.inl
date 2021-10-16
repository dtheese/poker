inline primes_s::primes_s(): primes{
   2,
   3,
   5,
   7,
   11,
   13,
   17,
   19,
   23,
   29,
   31,
   37,
   41,
   43,
   47,
   53,
   59,
   61,
   67,
   71,
   73,
   79,
   83,
   89,
   97,
   101,
   103,
   107,
   109,
   113,
   127,
   131,
   137,
   139,
   149,
   151,
   157,
   163,
   167,
   173,
   179,
   181,
   191,
   193,
   197,
   199,
   211,
   223,
   227,
   229,
   233,
   239
                                   }
{
}

inline primes_s::~primes_s()
{
}

inline const primes_s &primes_s::getInstance()
{
   static primes_s instance;

   return instance;
}

inline const my_uint_t &primes_s::operator[](my_uint_t i) const
{
   return primes[i];
}
