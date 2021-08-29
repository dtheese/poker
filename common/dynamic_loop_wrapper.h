#ifndef DYNAMIC_LOOP_WRAPPER_INCLUDED
#define DYNAMIC_LOOP_WRAPPER_INCLUDED

#include <vector>

using namespace std;

using indexes_t = vector<unsigned int>;

void dynamic_loop_wrapper(
                            unsigned int first_object_index,
                            unsigned int num_objects_total,
                            unsigned int num_objects_to_select,
                            void (*operation_to_perform)(const indexes_t &)
                         );

#endif
