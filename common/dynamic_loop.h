#ifndef DYNAMIC_LOOP_WRAPPER_INCLUDED
#define DYNAMIC_LOOP_WRAPPER_INCLUDED

#include <vector>

using namespace std;

using indexes_t = vector<unsigned int>;

class dynamic_loop_t
{
   public:
      dynamic_loop_t(
                       unsigned int first_object_index_p,
                       unsigned int num_objects_total_p,
                       unsigned int num_objects_to_select_p,
                       void (*operation_to_perform_p)(const indexes_t &)
                    );

   private:
      void dynamic_loop_body(
                               unsigned int first_index,
                               unsigned int last_index,
                               unsigned int current_depth,
                               unsigned int desired_depth
                            );

      unsigned int first_object_index;
      unsigned int num_objects_total;
      unsigned int num_objects_to_select;
      void (*operation_to_perform)(const indexes_t &);

      indexes_t indexes;
};

#endif
