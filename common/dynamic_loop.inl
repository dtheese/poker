template<typename T1, typename T2>
dynamic_loop_t<T1, T2>::dynamic_loop_t(
                                         const T1 first_object_index_p,
                                         const T1 num_objects_total_p,
                                         const T1 num_objects_to_select_p,
                                         T2 &operation_to_perform_p
                                      ): first_object_index{first_object_index_p},
                                         num_objects_total{num_objects_total_p},
                                         num_objects_to_select{num_objects_to_select_p},
                                         operation_to_perform{operation_to_perform_p}
{
   indexes.reserve(num_objects_to_select);
}

template<typename T1, typename T2>
void dynamic_loop_t<T1, T2>::run()
{
   dynamic_loop_body(
                       first_object_index,
                       first_object_index + num_objects_total - num_objects_to_select,
                       0
                    );
}

template<typename T1, typename T2>
void dynamic_loop_t<T1, T2>::dynamic_loop_body(
                                                 const T1 first_index,
                                                 const T1 last_index,
                                                 const T1 current_depth
                                              )
{
   if (current_depth == num_objects_to_select)
   {
      operation_to_perform(indexes);

      return;
   }
   else
   {
      for (T1 i{first_index}; i <= last_index; ++i)
      {
         indexes.push_back(i);

         dynamic_loop_body(
                             i + 1,
                             last_index + 1,
                             current_depth + 1
                          );

         indexes.pop_back();
      }
   }
}
