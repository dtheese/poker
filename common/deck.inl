inline deck_s::deck_s()
{
   my_uint_t j{0};

   for (rank_t rank{rank_t::First}; rank <= rank_t::Last; ++rank)
   {
      for (suit_t suit{suit_t::First}; suit <= suit_t::Last; ++suit)
         deck[j++] = card_t(rank, suit);
   }
}

inline deck_s::~deck_s()
{
}

inline const deck_s &deck_s::getInstance()
{
   static deck_s instance;

   return instance;
}

inline const deck_t &deck_s::getDeck() const
{
   return deck;
}
