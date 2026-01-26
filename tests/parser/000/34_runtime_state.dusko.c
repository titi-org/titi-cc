/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 12: Runtime evaluation - state management
  int counter ( ) {
 run_obj_t counter_step ( run_obj_t self_void , run_obj_t counter_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)counter_step , 0 )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t counter_step ( run_obj_t self_void , run_obj_t counter_arg_void ) { 
  run_cc_start_counter_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int count = 0 ; 
        count =  nat_add ( ( count ) , ( 1 ) )  ; 
     return ( run_obj_t ) ( count ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int c1 = counter ( ) ; 
       int c2 = counter ( ) ; 
       return ( run_obj_t ) (  nat_add ( ( c1 ) , ( c2 ) )  ) ;

}

/* SPECIALIZED CODE END */
