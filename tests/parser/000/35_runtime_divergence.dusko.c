/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 12: Runtime evaluation - detecting divergence pattern
   int diverge ( int n ) {
 run_obj_t diverge_step ( run_obj_t self_void , run_obj_t diverge_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)diverge_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t diverge_step ( run_obj_t self_void , run_obj_t diverge_arg_void ) { 
  run_cc_start_diverge_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = diverge_arg_void;

     while ( 1 )  
        {     n =  nat_add ( ( n ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( n ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
