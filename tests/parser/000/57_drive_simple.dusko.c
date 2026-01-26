/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 17: Driving - simple transformation
   int double_it ( int x ) {
 run_obj_t double_it_step ( run_obj_t self_void , run_obj_t double_it_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)double_it_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t double_it_step ( run_obj_t self_void , run_obj_t double_it_arg_void ) { 
  run_cc_start_double_it_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = double_it_arg_void;

       return ( run_obj_t ) (  nat_add ( ( x ) , ( x ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int x = 5 ; 
       int y = double_it ( x ) ; 
     return ( run_obj_t ) ( y ) ;

}

/* SPECIALIZED CODE END */
