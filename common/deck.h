#ifndef DECK_INCLUDED
#define DECK_INCLUDED

#include <type_traits>
#include <vector>

#include "card.h"
#include "utilities.h"

using namespace std;

// This singleton is lazily initialized.
class deck_s
{
   public:
      deck_s(const deck_s &) = delete;
      deck_s(deck_s &) = delete;

      deck_s(const deck_s &&) = delete;
      deck_s(deck_s &&) = delete;

      void operator=(const deck_s &) = delete;
      void operator=(deck_s &) = delete;

      void operator=(const deck_s &&) = delete;
      void operator=(deck_s &&) = delete;

      deck_s *operator&() = delete;

      static const deck_s &getInstance();

      const vector<card_t> &getDeck() const;

   private:
      deck_s();
      ~deck_s();

      vector<card_t> deck;
};

#include "deck.inl"

#endif
