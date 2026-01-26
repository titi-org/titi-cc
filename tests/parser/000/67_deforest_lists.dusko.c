/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 19: Transformation library - deforestation
   int sum_twice ( int n ) {
 run_obj_t sum_twice_step ( run_obj_t self_void , run_obj_t sum_twice_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)sum_twice_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t sum_twice_step ( run_obj_t self_void , run_obj_t sum_twice_arg_void ) { 
  run_cc_start_sum_twice_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = sum_twice_arg_void;

       int sum1 = 0 ; 
       int sum2 = 0 ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( n ) )  )  
        {     sum1 =  nat_add ( ( sum1 ) , ( i ) )  ; 
            sum2 =  nat_add ( ( sum2 ) , ( i ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
       return ( run_obj_t ) (  nat_add ( ( sum1 ) , ( sum2 ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( sum_twice ( 10 ) ) ;

}

/* SPECIALIZED CODE END */
