/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Test basic Pavlovic axiom operators


   void * test_compute ( void * x ) {
 run_obj_t test_compute_step ( run_obj_t self_void , run_obj_t test_compute_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_compute_step , (run_obj_t)(x) )) ;
}


   void * test_data ( void * x ) {
 run_obj_t test_data_step ( run_obj_t self_void , run_obj_t test_data_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_data_step , (run_obj_t)(x) )) ;
}


   void * test_identity ( void * x ) {
 run_obj_t test_identity_step ( run_obj_t self_void , run_obj_t test_identity_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_identity_step , (run_obj_t)(x) )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_compute_step ( run_obj_t self_void , run_obj_t test_compute_arg_void ) { 
  run_cc_start_test_compute_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_compute_arg_void;

   return ( run_obj_t ) ( compute ( x ) ) ;

}
 run_obj_t test_data_step ( run_obj_t self_void , run_obj_t test_data_arg_void ) { 
  run_cc_start_test_data_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_data_arg_void;

   return ( run_obj_t ) ( data ( x ) ) ;

}
 run_obj_t test_identity_step ( run_obj_t self_void , run_obj_t test_identity_arg_void ) { 
  run_cc_start_test_identity_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_identity_arg_void;

      return ( run_obj_t ) ( x ) ;

}

/* SPECIALIZED CODE END */
