/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 14: Partial evaluation - recursive specialization
     int power ( int x , int n ) {
 run_obj_t power_step ( run_obj_t self_void , run_obj_t power_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(n) };
  return ((int) run_step ( (run_obj_t)kleene_step , (run_obj_t)power_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t power_step ( run_obj_t self_void , run_obj_t power_arg_void ) { 
  run_cc_start_power_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)power_arg_void)[0];
  __auto_type n = ((run_obj_t*)power_arg_void)[1];

       if (  run_iseq ( ( n ) , ( 0 ) )  )  
        {  return ( run_obj_t ) ( 1 ) ;

     }
          return ( run_obj_t ) (  nat_mult ( ( x ) , (  ( self ( (run_obj_t)self , (run_obj_t)( run_obj_t [ ] ) { x ,  run_cc_sub ( ( n ) , ( 1 ) )  } ) )  ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) ( power ( 2 , 8 ) ) ;

}

/* SPECIALIZED CODE END */
