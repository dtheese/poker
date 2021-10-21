#ifndef DECK_INCLUDED
#define DECK_INCLUDED

#include <array>
#include <type_traits>

#include "card.h"
#include "utilities.h"

using namespace std;

// This singleton is lazily initialized.
class deck_s
{
   public:
      using deck_t = array<card_t, 52>;

      deck_s(const deck_s &) = delete;
      void operator=(const deck_s &) = delete;

      deck_s(deck_s &&) = delete;
      void operator=(deck_s &&) = delete;

      deck_s *operator&() = delete;

      static const deck_s &getInstance();

      const deck_t &getDeck() const;

   private:
      deck_s();
      ~deck_s();

      deck_t deck;
};

#include "deck.inl"

#endif
