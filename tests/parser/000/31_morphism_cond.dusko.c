/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 11: Morphism mapping - conditional as branching
   int abs_value ( int x ) {
 run_obj_t abs_value_step ( run_obj_t self_void , run_obj_t abs_value_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)abs_value_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t abs_value_step ( run_obj_t self_void , run_obj_t abs_value_arg_void ) { 
  run_cc_start_abs_value_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = abs_value_arg_void;

       if (  run_cc_lt ( ( x ) , ( 0 ) )  )  
        {    return ( run_obj_t ) (  run_cc_sub ( ( 0 ) , ( x ) )  ) ;

     }
     return ( run_obj_t ) ( x ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( abs_value (  - 42  ) ) ;

}

/* SPECIALIZED CODE END */
