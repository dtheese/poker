#ifndef DYNAMIC_LOOP_INCLUDED
#define DYNAMIC_LOOP_INCLUDED

#include <vector>

using namespace std;

template<typename T1>
using indexes_t = vector<T1>;

template<typename T1, typename T2>
class dynamic_loop_t
{
   public:
      dynamic_loop_t(
                       const T1 first_object_index_p,
                       const T1 num_objects_total_p,
                       const T1 num_objects_to_select_p,
                       T2 &operation_to_perform_p
                    );

      dynamic_loop_t(const dynamic_loop_t &) = delete;
      dynamic_loop_t &operator=(const dynamic_loop_t &) = delete;

      dynamic_loop_t(dynamic_loop_t &&) = delete;
      dynamic_loop_t &operator=(dynamic_loop_t &&) = delete;

      void run();

   private:
      void dynamic_loop_body(
                               const T1 first_index,
                               const T1 last_index,
                               const T1 current_depth
                            );

      const T1 first_object_index;
      const T1 num_objects_total;
      const T1 num_objects_to_select;
      T2 &operation_to_perform;

      indexes_t<T1> indexes;
};

#include "dynamic_loop.inl"

#endif
