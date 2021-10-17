inline combinations_table_s::combinations_table_s()
{
   for (my_uint_t i {0}; i < 52; ++i)
   {
      for (my_uint_t j {0}; j < 52; ++j)
         combinations_table[i][j] = combinations(i, j);
   }
}

inline combinations_table_s::~combinations_table_s()
{
}

inline const combinations_table_s &combinations_table_s::getInstance()
{
   static combinations_table_s instance;

   return instance;
}

my_uint_t combinations_table_s::operator()(my_uint_t i, my_uint_t j)
{
   return combinations_table[i][j];
}
