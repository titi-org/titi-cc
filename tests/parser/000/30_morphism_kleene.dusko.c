/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 11: Morphism mapping - loop as fixpoint
   int sum_to_n ( int n ) {
 run_obj_t sum_to_n_step ( run_obj_t self_void , run_obj_t sum_to_n_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)sum_to_n_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t sum_to_n_step ( run_obj_t self_void , run_obj_t sum_to_n_arg_void ) { 
  run_cc_start_sum_to_n_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = sum_to_n_arg_void;

       int sum = 0 ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( n ) )  )  
        {     sum =  nat_add ( ( sum ) , ( i ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( sum ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( sum_to_n ( 10 ) ) ;

}

/* SPECIALIZED CODE END */
