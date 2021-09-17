inline deck_s::deck_s()
{
   deck.reserve(52);

   for (rank_t rank{rank_t::First}; rank <= rank_t::Last; ++rank)
   {
      for (suit_t suit{suit_t::First}; suit <= suit_t::Last; ++suit)
         deck.push_back(card_t(rank, suit));
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

inline const vector<card_t> &deck_s::getDeck() const
{
   return deck;
}
