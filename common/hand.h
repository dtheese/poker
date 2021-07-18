#ifndef HAND_INCLUDED
#define HAND_INCLUDED

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "card.h"
#include "deck.h"

using namespace std;

enum class hand_rank_t {
                          HIGH_CARD,
                          ONE_PAIR,
                          TWO_PAIR,
                          THREE_OF_A_KIND,
                          STRAIGHT,
                          FLUSH,
                          FULL_HOUSE,
                          FOUR_OF_A_KIND,
                          STRAIGHT_FLUSH,
                          ROYAL_FLUSH
                       };

void print_hand_rank(hand_rank_t hand_rank);

class hand_t
{
   public:
      hand_t();
      explicit hand_t(const card_t *cards_p);

      void print() const;
      hand_rank_t hand_rank() const;
      unsigned long long int get_id() const;

   private:
      card_t cards[5];
      unsigned long long int id;

      bool is_four_of_a_kind() const;
      bool is_a_full_house() const;
      bool is_three_of_a_kind() const;
      bool is_two_pair() const;
      bool is_one_pair() const;
};

#include "hand.inl"

#endif
