/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Test Pavlovic structure operators


     void * test_swap ( void * x , void * y ) {
 run_obj_t test_swap_step ( run_obj_t self_void , run_obj_t test_swap_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_swap_step , (run_obj_t)args )) ;
}


   void * test_copy ( void * x ) {
 run_obj_t test_copy_step ( run_obj_t self_void , run_obj_t test_copy_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_copy_step , (run_obj_t)(x) )) ;
}


   void * test_delete ( void * x ) {
 run_obj_t test_delete_step ( run_obj_t self_void , run_obj_t test_delete_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_delete_step , (run_obj_t)(x) )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_swap_step ( run_obj_t self_void , run_obj_t test_swap_arg_void ) { 
  run_cc_start_test_swap_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)test_swap_arg_void)[0];
  __auto_type y = ((run_obj_t*)test_swap_arg_void)[1];

         return ( run_obj_t ) ( run_data_va ( 2 , y , x ) ) ;

}
 run_obj_t test_copy_step ( run_obj_t self_void , run_obj_t test_copy_arg_void ) { 
  run_cc_start_test_copy_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_copy_arg_void;

      return ( run_obj_t ) ( run_data_va ( 2 , x , x ) ) ;

}
 run_obj_t test_delete_step ( run_obj_t self_void , run_obj_t test_delete_arg_void ) { 
  run_cc_start_test_delete_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_delete_arg_void;

      return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
