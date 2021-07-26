inline card_t::card_t(): rank(rank_t::None), suit(suit_t::None)
{
}

inline card_t::card_t(rank_t rank_p, suit_t suit_p):rank(rank_p), suit(suit_p)
{
}

inline rank_t card_t::get_rank() const
{
   return rank;
}

inline suit_t card_t::get_suit() const
{
   return suit;
}

inline unsigned long long int card_t::get_id() const
{
   return id;
}

inline bool operator<(const card_t &lhs, const card_t &rhs)
{
   if (lhs.rank < rhs.rank)
      return true;

   // Since suit doesn't matter in poker, skip this check.
   // if ((lhs.rank == rhs.rank) && (lhs.suit < rhs.suit))
   //    return true;

   return false;
}

inline void card_t::print() const
{
   if (rank >= rank_t::Two && rank <= rank_t::Ten)
      cout << static_cast<underlying_type<rank_t>::type>(rank);
   else if (rank == rank_t::Jack)
      cout << "Jack";
   else if (rank == rank_t::Queen)
      cout << "Queen";
   else if (rank == rank_t::King)
      cout << "King";
   else if (rank == rank_t::Ace)
      cout << "Ace";
   else
      assert(0);

   cout << " of ";

   switch(suit)
   {
      case suit_t::CLUBS:
         cout << "Clubs";
         break;
      case suit_t::DIAMONDS:
         cout << "Diamonds";
         break;
      case suit_t::HEARTS:
         cout << "Hearts";
         break;
      case suit_t::SPADES:
         cout << "Spades";
         break;
      default:
         assert(0);
   }

   cout << endl;
}
