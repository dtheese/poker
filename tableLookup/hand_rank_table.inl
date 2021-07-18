inline const hand_rank_table_s &hand_rank_table_s::getInstance()
{
   static hand_rank_table_s instance;

   return instance;
}

inline hand_rank_t hand_rank_table_s::operator[](unsigned long long int i) const
{
   return hand_ranks.at(i);
}
