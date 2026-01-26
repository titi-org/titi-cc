/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 15: Supercompilation whistle - simple unfold
   int twice ( int x ) {
 run_obj_t twice_step ( run_obj_t self_void , run_obj_t twice_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)twice_step , (run_obj_t)(x) )) ;
}


   int double_twice ( int x ) {
 run_obj_t double_twice_step ( run_obj_t self_void , run_obj_t double_twice_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)double_twice_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t twice_step ( run_obj_t self_void , run_obj_t twice_arg_void ) { 
  run_cc_start_twice_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = twice_arg_void;

       return ( run_obj_t ) (  nat_add ( ( x ) , ( x ) )  ) ;

}
 run_obj_t double_twice_step ( run_obj_t self_void , run_obj_t double_twice_arg_void ) { 
  run_cc_start_double_twice_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = double_twice_arg_void;

     return ( run_obj_t ) ( twice ( twice ( x ) ) ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( double_twice ( 5 ) ) ;

}

/* SPECIALIZED CODE END */
