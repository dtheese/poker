#include "dynamic_loop_wrapper.h"

using namespace std;

void dynamic_loop(
                    unsigned int first_index,
                    unsigned int last_index,
                    unsigned int current_depth,
                    unsigned int desired_depth,
                    indexes_t &indexes,
                    void (&operation_to_perform)(const indexes_t &)
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

         dynamic_loop(
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

void dynamic_loop_wrapper(
                            unsigned int first_object_index,
                            unsigned int num_objects_total,
                            unsigned int num_objects_to_select,
                            void (&operation_to_perform)(const indexes_t &)
                         )
{
   indexes_t indexes;

   indexes.reserve(num_objects_to_select);

   dynamic_loop(
                  first_object_index,
                  first_object_index + num_objects_total - num_objects_to_select,
                  0,
                  num_objects_to_select,
                  indexes,
                  operation_to_perform
               );
}
