/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 11: Morphism mapping - function call as evaluation
   int eval_simple ( int x ) {
 run_obj_t eval_simple_step ( run_obj_t self_void , run_obj_t eval_simple_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)eval_simple_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t eval_simple_step ( run_obj_t self_void , run_obj_t eval_simple_arg_void ) { 
  run_cc_start_eval_simple_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = eval_simple_arg_void;

       return ( run_obj_t ) (  nat_add ( ( x ) , ( 1 ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int result = eval_simple ( 5 ) ; 
     return ( run_obj_t ) ( result ) ;

}

/* SPECIALIZED CODE END */
