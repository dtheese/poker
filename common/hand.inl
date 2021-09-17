inline hand_t::hand_t()
{
}

inline hand_t::hand_t(const card_t *cards_p)
{
   for (unsigned int i{0}; i <= 4; ++i)
   {
      cards[i] = cards_p[i];

#ifdef USE_LOOKUP_TABLE
      id *= cards[i].get_id();
#endif
   }

   // There is no need to sort here in non-Monte Carlo situations because
   // the cards come out of the deck in sorted order. This has proven to be
   // a nice optimization!
   if (MONTE_CARLO)
      sort(cards, cards + 5);
}

inline hand_rank_t hand_t::hand_rank() const
{
   if (is_a_full_house())
      return hand_rank_t::FULL_HOUSE;
   else if (is_four_of_a_kind())
      return hand_rank_t::FOUR_OF_A_KIND;
   else if (is_two_pair())
      return hand_rank_t::TWO_PAIR;
   else if (is_three_of_a_kind())
      return hand_rank_t::THREE_OF_A_KIND;
   else if (is_one_pair())
      return hand_rank_t::ONE_PAIR;

   bool is_a_flush{false};
   bool is_a_straight{false};

   if (
         cards[0].get_suit() == cards[1].get_suit() &&
         cards[0].get_suit() == cards[2].get_suit() &&
         cards[0].get_suit() == cards[3].get_suit() &&
         cards[0].get_suit() == cards[4].get_suit()
      )
   {
      is_a_flush = true;
   }

   if (
         (
            static_cast<typename underlying_type<rank_t>::type>(cards[4].get_rank()) -
            static_cast<typename underlying_type<rank_t>::type>(cards[0].get_rank())
         ) == 4 ||
         (
            cards[0].get_rank() == rank_t::Two &&
            cards[1].get_rank() == rank_t::Three &&
            cards[2].get_rank() == rank_t::Four &&
            cards[3].get_rank() == rank_t::Five &&
            cards[4].get_rank() == rank_t::Ace
         )
      )
   {
      is_a_straight = true;
   }

   if (is_a_straight)
   {
      if (is_a_flush)
      {
         if (cards[0].get_rank() != rank_t::Ten)
            return hand_rank_t::STRAIGHT_FLUSH;
         else
            return hand_rank_t::ROYAL_FLUSH;
      }

      return hand_rank_t::STRAIGHT;
   }

   if (is_a_flush)
      return hand_rank_t::FLUSH;

   return hand_rank_t::HIGH_CARD;
}

inline bool hand_t::is_four_of_a_kind() const
{
   if (
         cards[0].get_rank() == cards[3].get_rank() ||
         cards[1].get_rank() == cards[4].get_rank()
      )
   {
      return true;
   }

   return false;
}

inline bool hand_t::is_a_full_house() const
{
   if (
         (
            cards[0].get_rank() == cards[1].get_rank() &&
            cards[2].get_rank() == cards[4].get_rank()
         ) ||
         (
            cards[0].get_rank() == cards[2].get_rank() &&
            cards[3].get_rank() == cards[4].get_rank()
         )
      )
   {
      return true;
   }

   return false;
}

inline bool hand_t::is_three_of_a_kind() const
{
   if (
         cards[0].get_rank() == cards[2].get_rank() ||
         cards[1].get_rank() == cards[3].get_rank() ||
         cards[2].get_rank() == cards[4].get_rank()
      )
   {
      return true;
   }

   return false;
}

inline bool hand_t::is_two_pair() const
{
   if (
         (
            cards[0].get_rank() == cards[1].get_rank() &&
            cards[2].get_rank() == cards[3].get_rank()
         ) ||
         (
            cards[0].get_rank() == cards[1].get_rank() &&
            cards[3].get_rank() == cards[4].get_rank()
         ) ||
         (
            cards[1].get_rank() == cards[2].get_rank() &&
            cards[3].get_rank() == cards[4].get_rank()
         )
      )
   {
      return true;
   }

   return false;
}

inline bool hand_t::is_one_pair() const
{
   if (
         cards[0].get_rank() == cards[1].get_rank() ||
         cards[1].get_rank() == cards[2].get_rank() ||
         cards[2].get_rank() == cards[3].get_rank() ||
         cards[3].get_rank() == cards[4].get_rank()
      )
   {
      return true;
   }

   return false;
}

inline unsigned long long int hand_t::get_id() const
{
#ifdef USE_LOOKUP_TABLE
   return id;
#else
   return 0;
#endif
}

inline void hand_t::print() const
{
   for (const card_t &card : cards)
      card.print();
}

inline void print_hand_rank(hand_rank_t hand_rank)
{
   switch (hand_rank)
   {
      case hand_rank_t::HIGH_CARD:
         cout << "High card" << endl;
         break;
      case hand_rank_t::ONE_PAIR:
         cout << "One pair" << endl;
         break;
      case hand_rank_t::TWO_PAIR:
         cout << "Two pair" << endl;
         break;
      case hand_rank_t::THREE_OF_A_KIND:
         cout << "Three of a kind" << endl;
         break;
      case hand_rank_t::STRAIGHT:
         cout << "Straight" << endl;
         break;
      case hand_rank_t::FLUSH:
         cout << "Flush" << endl;
         break;
      case hand_rank_t::FULL_HOUSE:
         cout << "Full house" << endl;
         break;
      case hand_rank_t::FOUR_OF_A_KIND:
         cout << "Four of a kind" << endl;
         break;
      case hand_rank_t::STRAIGHT_FLUSH:
         cout << "Straight flush" << endl;
         break;
      case hand_rank_t::ROYAL_FLUSH:
         cout << "Royal flush" << endl;
         break;
      default:
         assert(0);
   }
}
