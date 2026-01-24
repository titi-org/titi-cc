/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Test Pavlovic run and eval operators


     void * test_eval ( void * f , void * x ) {
 run_obj_t test_eval_step ( run_obj_t self_void , run_obj_t test_eval_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_eval_step , (run_obj_t)args )) ;
}


     void * test_run_program ( void * f , void * x ) {
 run_obj_t test_run_program_step ( run_obj_t self_void , run_obj_t test_run_program_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_run_program_step , (run_obj_t)args )) ;
}


     void * test_run_kleene ( void * f , void * x ) {
 run_obj_t test_run_kleene_step ( run_obj_t self_void , run_obj_t test_run_kleene_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_run_kleene_step , (run_obj_t)args )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_eval_step ( run_obj_t self_void , run_obj_t test_eval_arg_void ) { 
  run_cc_start_test_eval_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)test_eval_arg_void)[0];
  __auto_type x = ((run_obj_t*)test_eval_arg_void)[1];

    return ( run_obj_t ) ( eval ( f , x ) ) ;

}
 run_obj_t test_run_program_step ( run_obj_t self_void , run_obj_t test_run_program_arg_void ) { 
  run_cc_start_test_run_program_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)test_run_program_arg_void)[0];
  __auto_type x = ((run_obj_t*)test_run_program_arg_void)[1];

            return ( run_obj_t ) ( run ( program , f , x ) ) ;

}
 run_obj_t test_run_kleene_step ( run_obj_t self_void , run_obj_t test_run_kleene_arg_void ) { 
  run_cc_start_test_run_kleene_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)test_run_kleene_arg_void)[0];
  __auto_type x = ((run_obj_t*)test_run_kleene_arg_void)[1];

            return ( run_obj_t ) ( run ( kleene , f , x ) ) ;

}

/* SPECIALIZED CODE END */
