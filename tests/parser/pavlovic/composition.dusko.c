/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Test Pavlovic composition operators


       void * test_sequential ( void * f , void * g , void * x ) {
 run_obj_t test_sequential_step ( run_obj_t self_void , run_obj_t test_sequential_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(g) , (run_obj_t)(x) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_sequential_step , (run_obj_t)args )) ;
}


         void * test_parallel ( void * f , void * g , void * pair , void * n ) {
 run_obj_t test_parallel_step ( run_obj_t self_void , run_obj_t test_parallel_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(g) , (run_obj_t)(pair) , (run_obj_t)(n) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_parallel_step , (run_obj_t)args )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_sequential_step ( run_obj_t self_void , run_obj_t test_sequential_arg_void ) { 
  run_cc_start_test_sequential_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)test_sequential_arg_void)[0];
  __auto_type g = ((run_obj_t*)test_sequential_arg_void)[1];
  __auto_type x = ((run_obj_t*)test_sequential_arg_void)[2];

            return ( run_obj_t ) ( eval ( g , eval ( f , x ) ) ) ;

}
 run_obj_t test_parallel_step ( run_obj_t self_void , run_obj_t test_parallel_arg_void ) { 
  run_cc_start_test_parallel_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)test_parallel_arg_void)[0];
  __auto_type g = ((run_obj_t*)test_parallel_arg_void)[1];
  __auto_type pair = ((run_obj_t*)test_parallel_arg_void)[2];
  __auto_type n = ((run_obj_t*)test_parallel_arg_void)[3];

               return ( run_obj_t ) ( parallel ( f , g , pair , n ) ) ;

}

/* SPECIALIZED CODE END */
