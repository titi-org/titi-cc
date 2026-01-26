/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 13: Program representation - recursive fixpoint
     int ackermann ( int m , int n ) {
 run_obj_t ackermann_step ( run_obj_t self_void , run_obj_t ackermann_arg_void );
  run_obj_t args[] = { (run_obj_t)(m) , (run_obj_t)(n) };
  return ((int) run_step ( (run_obj_t)kleene_step , (run_obj_t)ackermann_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t ackermann_step ( run_obj_t self_void , run_obj_t ackermann_arg_void ) { 
  run_cc_start_ackermann_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type m = ((run_obj_t*)ackermann_arg_void)[0];
  __auto_type n = ((run_obj_t*)ackermann_arg_void)[1];

       if (  run_iseq ( ( m ) , ( 0 ) )  )  
        {    return ( run_obj_t ) (  nat_add ( ( n ) , ( 1 ) )  ) ;

     }
       if (  run_iseq ( ( n ) , ( 0 ) )  )  
        {       run_cc_tco_args[0] = (run_obj_t)(  run_cc_sub ( ( m ) , ( 1 ) )   );
  run_cc_tco_args[1] = (run_obj_t)(  1 );
  ackermann_arg_void = (run_obj_t)run_cc_tco_args;
  goto run_cc_start_ackermann_step;

     }
             run_cc_tco_args[0] = (run_obj_t)(  run_cc_sub ( ( m ) , ( 1 ) )   );
  run_cc_tco_args[1] = (run_obj_t)(   ( self ( (run_obj_t)self , (run_obj_t)( run_obj_t [ ] ) { m ,  run_cc_sub ( ( n ) , ( 1 ) )  } ) )  );
  ackermann_arg_void = (run_obj_t)run_cc_tco_args;
  goto run_cc_start_ackermann_step;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) ( ackermann ( 2 , 3 ) ) ;

}

/* SPECIALIZED CODE END */
