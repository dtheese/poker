#ifndef CARD_INCLUDED
#define CARD_INCLUDED

#include <cassert>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

#include "primes.h"

enum class rank_t: unsigned int {
                                   First = 2,
                                   Two   = 2,
                                   Three = 3,
                                   Four  = 4,
                                   Five  = 5,
                                   Six   = 6,
                                   Seven = 7,
                                   Eight = 8,
                                   Nine  = 9,
                                   Ten   = 10,
                                   Jack  = 11,
                                   Queen = 12,
                                   King  = 13,
                                   Ace   = 14,
                                   Last  = Ace,
                                   End   = Last + 1,
                                   None  = End + 1
                                };

enum class suit_t: unsigned int {
                                   First    = 0,
                                   CLUBS    = First,
                                   DIAMONDS = First + 1,
                                   HEARTS   = First + 2,
                                   SPADES   = First + 3,
                                   Last     = SPADES,
                                   End      = Last + 1,
                                   None     = End + 1
                                };

class card_t
{
   public:
      card_t();
      card_t(rank_t rank_p, suit_t suit_p);
      void print() const;

      rank_t get_rank() const;
      suit_t get_suit() const;
      unsigned long long int get_id() const;

      friend bool operator<(const card_t &lhs, const card_t &rhs);

   private:
      rank_t rank;
      suit_t suit;

      unsigned long long int id;
};

#include "card.inl"

#endif
