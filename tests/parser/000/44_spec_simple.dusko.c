/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 14: Partial evaluation - simple specialization
   int add_five ( int x ) {
 run_obj_t add_five_step ( run_obj_t self_void , run_obj_t add_five_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)add_five_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t add_five_step ( run_obj_t self_void , run_obj_t add_five_arg_void ) { 
  run_cc_start_add_five_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = add_five_arg_void;

       return ( run_obj_t ) (  nat_add ( ( x ) , ( 5 ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( add_five ( 10 ) ) ;

}

/* SPECIALIZED CODE END */
