#ifndef HAND_INCLUDED
#define HAND_INCLUDED

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "fundamental_types.h"

#include "card.h"
#include "deck.h"
#include "parameters.h"

enum class hand_rank_t {
                          First = 0,
                          HIGH_CARD = First,
                          ONE_PAIR = 1,
                          TWO_PAIR = 2,
                          THREE_OF_A_KIND = 3,
                          STRAIGHT = 4,
                          FLUSH = 5,
                          FULL_HOUSE = 6,
                          FOUR_OF_A_KIND = 7,
                          STRAIGHT_FLUSH = 8,
                          ROYAL_FLUSH = 9,
                          Last = ROYAL_FLUSH,
                          End = Last + 1,
                          None = End + 1
                       };

void print_hand_rank(hand_rank_t hand_rank);

class hand_t
{
   public:
      hand_t() = delete;

      explicit hand_t(const array<card_t, 5> &cards_p);

      void print() const;
      hand_rank_t hand_rank() const;

   private:
      array<card_t, 5> cards;

      bool is_four_of_a_kind() const;
      bool is_a_full_house() const;
      bool is_three_of_a_kind() const;
      bool is_two_pair() const;
      bool is_one_pair() const;
};

#include "hand.inl"

#endif
