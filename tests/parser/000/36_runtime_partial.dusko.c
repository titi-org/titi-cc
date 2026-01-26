/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 12: Runtime evaluation - partial evaluation
     int multiply ( int x , int y ) {
 run_obj_t multiply_step ( run_obj_t self_void , run_obj_t multiply_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)multiply_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t multiply_step ( run_obj_t self_void , run_obj_t multiply_arg_void ) { 
  run_cc_start_multiply_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)multiply_arg_void)[0];
  __auto_type y = ((run_obj_t*)multiply_arg_void)[1];

       return ( run_obj_t ) (  nat_mult ( ( x ) , ( y ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int c = multiply ( 2 , 3 ) ; 
     return ( run_obj_t ) ( c ) ;

}

/* SPECIALIZED CODE END */
