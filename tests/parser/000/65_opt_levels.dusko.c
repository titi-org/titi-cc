/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 18: End-to-end compilation - opt levels
   int opt_test ( int n ) {
 run_obj_t opt_test_step ( run_obj_t self_void , run_obj_t opt_test_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)opt_test_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t opt_test_step ( run_obj_t self_void , run_obj_t opt_test_arg_void ) { 
  run_cc_start_opt_test_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = opt_test_arg_void;

         int x =  nat_add ( ( 1 ) , ( 1 ) )  ; 
         int y =  nat_mult ( ( x ) , ( 2 ) )  ; 
         int z =  nat_add ( ( y ) , ( 0 ) )  ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( n ) )  )  
        {     z =  nat_add ( ( z ) , ( 1 ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( z ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( opt_test ( 100 ) ) ;

}

/* SPECIALIZED CODE END */
