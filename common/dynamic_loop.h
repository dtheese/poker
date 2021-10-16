#ifndef DYNAMIC_LOOP_INCLUDED
#define DYNAMIC_LOOP_INCLUDED

#include <vector>

using namespace std;

#include "fundamental_types.h"

using indexes_t = vector<my_uint_t>;

template<typename T>
class dynamic_loop_t
{
   public:
      dynamic_loop_t(
                       const my_uint_t first_object_index_p,
                       const my_uint_t num_objects_total_p,
                       const my_uint_t num_objects_to_select_p,
                       T &operation_to_perform_p
                    );

      dynamic_loop_t(const dynamic_loop_t &) = delete;
      dynamic_loop_t &operator=(const dynamic_loop_t &) = delete;

      dynamic_loop_t(dynamic_loop_t &&) = delete;
      dynamic_loop_t &operator=(dynamic_loop_t &&) = delete;

      void run();

   private:
      void dynamic_loop_body(
                               const my_uint_t first_index,
                               const my_uint_t last_index,
                               const my_uint_t current_depth
                            );

      const my_uint_t first_object_index;
      const my_uint_t num_objects_total;
      const my_uint_t num_objects_to_select;
      T &operation_to_perform;

      indexes_t indexes;
};

#include "dynamic_loop.inl"

#endif
