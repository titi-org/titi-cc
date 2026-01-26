/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 14: Partial evaluation - residual program
     int multiply ( int a , int b ) {
 run_obj_t multiply_step ( run_obj_t self_void , run_obj_t multiply_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
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
  __auto_type a = ((run_obj_t*)multiply_arg_void)[0];
  __auto_type b = ((run_obj_t*)multiply_arg_void)[1];

       int result = 0 ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( b ) )  )  
        {     result =  nat_add ( ( result ) , ( a ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( result ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) ( multiply ( 7 , 6 ) ) ;

}

/* SPECIALIZED CODE END */
