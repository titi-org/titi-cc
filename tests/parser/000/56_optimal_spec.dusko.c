/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 16: Specialization - optimal partitioning
     int loop_sum ( int n , int k ) {
 run_obj_t loop_sum_step ( run_obj_t self_void , run_obj_t loop_sum_arg_void );
  run_obj_t args[] = { (run_obj_t)(n) , (run_obj_t)(k) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)loop_sum_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t loop_sum_step ( run_obj_t self_void , run_obj_t loop_sum_arg_void ) { 
  run_cc_start_loop_sum_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type n = ((run_obj_t*)loop_sum_arg_void)[0];
  __auto_type k = ((run_obj_t*)loop_sum_arg_void)[1];

       int sum = 0 ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( n ) )  )  
        {     sum =  nat_add ( ( sum ) , ( k ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( sum ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) ( loop_sum ( 100 , 5 ) ) ;

}

/* SPECIALIZED CODE END */
