template<typename T>
dynamic_loop_t<T>::dynamic_loop_t(
                                    const unsigned long long int first_object_index_p,
                                    const unsigned long long int num_objects_total_p,
                                    const unsigned long long int num_objects_to_select_p,
                                    T &operation_to_perform_p
                                 ): first_object_index{first_object_index_p},
                                    num_objects_total{num_objects_total_p},
                                    num_objects_to_select{num_objects_to_select_p},
                                    operation_to_perform{operation_to_perform_p}
{
   indexes.reserve(num_objects_to_select);
}

template<typename T>
void dynamic_loop_t<T>::run()
{
   dynamic_loop_body(
                       first_object_index,
                       first_object_index + num_objects_total - num_objects_to_select,
                       0
                    );
}

template<typename T>
void dynamic_loop_t<T>::dynamic_loop_body(
                                            const unsigned long long int first_index,
                                            const unsigned long long int last_index,
                                            const unsigned long long int current_depth
                                         )
{
   if (current_depth == num_objects_to_select)
   {
      operation_to_perform(indexes);

      return;
   }
   else
   {
      for (unsigned long long int i{first_index}; i <= last_index; ++i)
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
