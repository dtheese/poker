#ifndef DYNAMIC_LOOP_WRAPPER_INCLUDED
#define DYNAMIC_LOOP_WRAPPER_INCLUDED

#include <vector>

using namespace std;

using indexes_t = vector<unsigned int>;

template<typename T>
class dynamic_loop_t
{
   public:
      dynamic_loop_t(
                       const unsigned int first_object_index_p,
                       const unsigned int num_objects_total_p,
                       const unsigned int num_objects_to_select_p,
                       T &operation_to_perform_p
                    );

      dynamic_loop_t(const dynamic_loop_t &) = delete;
      dynamic_loop_t &operator=(const dynamic_loop_t &) = delete;

   private:
      void dynamic_loop_body(
                               const unsigned int first_index,
                               const unsigned int last_index,
                               const unsigned int current_depth
                            );

      const unsigned int first_object_index;
      const unsigned int num_objects_total;
      const unsigned int num_objects_to_select;
      T &operation_to_perform;

      indexes_t indexes;
};

#include "dynamic_loop.inl"

#endif
