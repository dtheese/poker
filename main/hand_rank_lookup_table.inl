inline hand_rank_lookup_table_s::hand_rank_lookup_table_s()
{
}

inline hand_rank_lookup_table_s::~hand_rank_lookup_table_s()
{
}

inline const hand_rank_lookup_table_s &hand_rank_lookup_table_s::getInstance()
{
   static hand_rank_lookup_table_s instance;

   return instance;
}
