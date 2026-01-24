/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Test Pavlovic process operators


   void * test_function ( void * x ) {
 run_obj_t test_function_step ( run_obj_t self_void , run_obj_t test_function_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_function_step , (run_obj_t)(x) )) ;
}


     void * test_process ( void * x , void * y ) {
 run_obj_t test_process_step ( run_obj_t self_void , run_obj_t test_process_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_process_step , (run_obj_t)args )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_function_step ( run_obj_t self_void , run_obj_t test_function_arg_void ) { 
  run_cc_start_test_function_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_function_arg_void;

   return ( run_obj_t ) ( function ( x ) ) ;

}
 run_obj_t test_process_step ( run_obj_t self_void , run_obj_t test_process_arg_void ) { 
  run_cc_start_test_process_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)test_process_arg_void)[0];
  __auto_type y = ((run_obj_t*)test_process_arg_void)[1];

    return ( run_obj_t ) ( process ( x , y ) ) ;

}

/* SPECIALIZED CODE END */
