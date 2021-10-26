inline hand_rank_lookup_table_s::hand_rank_lookup_table_s()
{
   const auto &deck{deck_s::getInstance().getDeck()};
   array<my_uint_t, 5> indexes;

   for (my_uint_t encoded_value{0}; encoded_value < combinations(52, 5); ++encoded_value)
   {
      combination_encoder_t<decltype(indexes), 52, 5>::decode(encoded_value, indexes);

      array<card_t, 5> cards;
      my_uint_t j{0};

      for (auto i : indexes)
         cards[j++] = deck[i];

      hand_t hand{cards};
      hand_rank_lookup_table[encoded_value] = hand.hand_rank();
   }
}

inline hand_rank_lookup_table_s::~hand_rank_lookup_table_s()
{
}

inline const hand_rank_lookup_table_s &hand_rank_lookup_table_s::getInstance()
{
   static hand_rank_lookup_table_s instance;

   return instance;
}

inline
const hand_rank_lookup_table_t
&hand_rank_lookup_table_s::getLookupTable() const
{
   return hand_rank_lookup_table;
}
