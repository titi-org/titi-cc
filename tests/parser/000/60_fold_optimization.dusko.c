/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 17: Driving - fold optimization
     int step ( int x , int n ) {
 run_obj_t step_step ( run_obj_t self_void , run_obj_t step_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(n) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)step_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t step_step ( run_obj_t self_void , run_obj_t step_arg_void ) { 
  run_cc_start_step_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)step_arg_void)[0];
  __auto_type n = ((run_obj_t*)step_arg_void)[1];

       int result = x ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( n ) )  )  
        {     result =  nat_add ( ( result ) , ( 1 ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( result ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) ( step ( 0 , 10 ) ) ;

}

/* SPECIALIZED CODE END */
