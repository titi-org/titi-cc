/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Test Pavlovic recursion operators


     void * test_partial ( void * f , void * x ) {
 run_obj_t test_partial_step ( run_obj_t self_void , run_obj_t test_partial_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_partial_step , (run_obj_t)args )) ;
}


   void * test_fixpoint ( void * f ) {
 run_obj_t test_fixpoint_step ( run_obj_t self_void , run_obj_t test_fixpoint_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_fixpoint_step , (run_obj_t)(f) )) ;
}


     void * test_kleene ( void * f , void * x ) {
 run_obj_t test_kleene_step ( run_obj_t self_void , run_obj_t test_kleene_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_kleene_step , (run_obj_t)args )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_partial_step ( run_obj_t self_void , run_obj_t test_partial_arg_void ) { 
  run_cc_start_test_partial_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)test_partial_arg_void)[0];
  __auto_type x = ((run_obj_t*)test_partial_arg_void)[1];

    return ( run_obj_t ) ( partial ( f , x ) ) ;

}
 run_obj_t test_fixpoint_step ( run_obj_t self_void , run_obj_t test_fixpoint_arg_void ) { 
  run_cc_start_test_fixpoint_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type f = test_fixpoint_arg_void;

   return ( run_obj_t ) ( fixpoint ( f ) ) ;

}
 run_obj_t test_kleene_step ( run_obj_t self_void , run_obj_t test_kleene_arg_void ) { 
  run_cc_start_test_kleene_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)test_kleene_arg_void)[0];
  __auto_type x = ((run_obj_t*)test_kleene_arg_void)[1];

    return ( run_obj_t ) ( kleene ( f , x ) ) ;

}

/* SPECIALIZED CODE END */
