/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 18: End-to-end compilation - perf metrics
   int collatz ( int n ) {
 run_obj_t collatz_step ( run_obj_t self_void , run_obj_t collatz_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)collatz_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t collatz_step ( run_obj_t self_void , run_obj_t collatz_arg_void ) { 
  run_cc_start_collatz_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = collatz_arg_void;

       int count = 0 ; 
       while (  run_bool_not (  run_iseq ( ( n ) , ( 1 ) )  )  )  
        {      if (  run_iseq ( (  run_cc_mod ( ( n ) , ( 2 ) )  ) , ( 0 ) )  )  
            {     n =  run_cc_div ( ( n ) , ( 2 ) )  ; 
         }  else  
            {       n =  nat_add ( (  nat_mult ( ( n ) , ( 3 ) )  ) , ( 1 ) )  ; 
         }
            count =  nat_add ( ( count ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( count ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( collatz ( 27 ) ) ;

}

/* SPECIALIZED CODE END */
