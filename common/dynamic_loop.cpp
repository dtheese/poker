#include "dynamic_loop.h"

using namespace std;

dynamic_loop_t::dynamic_loop_t(
                                 unsigned int first_object_index_p,
                                 unsigned int num_objects_total_p,
                                 unsigned int num_objects_to_select_p,
                                 void (*operation_to_perform_p)(const indexes_t &)
                              ): first_object_index{first_object_index_p},
                                 num_objects_total{num_objects_total_p},
                                 num_objects_to_select{num_objects_to_select_p},
                                 operation_to_perform{operation_to_perform_p}
{
   indexes.reserve(num_objects_to_select);

   dynamic_loop_body(
                       first_object_index,
                       first_object_index + num_objects_total - num_objects_to_select,
                       0,
                       num_objects_to_select,
                       indexes,
                       operation_to_perform
                    );
}

void dynamic_loop_t::dynamic_loop_body(
                         unsigned int first_index,
                         unsigned int last_index,
                         unsigned int current_depth,
                         unsigned int desired_depth,
                         indexes_t &indexes,
                         void (*operation_to_perform)(const indexes_t &)
                                      )
{
   if (current_depth == desired_depth)
   {
      operation_to_perform(indexes);

      return;
   }
   else
   {
      for (unsigned int i = first_index; i <= last_index; ++i)
      {
         indexes.push_back(i);

         dynamic_loop_body(
                             i + 1,
                             last_index + 1,
                             current_depth + 1,
                             desired_depth,
                             indexes,
                             operation_to_perform
                          );

         indexes.pop_back();
      }
   }
}
