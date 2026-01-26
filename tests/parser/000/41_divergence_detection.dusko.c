/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 13: Program representation - divergence detection
   int is_even ( int n ) {
 run_obj_t is_even_step ( run_obj_t self_void , run_obj_t is_even_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)is_even_step , (run_obj_t)(n) )) ;
}


   int is_odd ( int n ) {
 run_obj_t is_odd_step ( run_obj_t self_void , run_obj_t is_odd_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)is_odd_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t is_even_step ( run_obj_t self_void , run_obj_t is_even_arg_void ) { 
  run_cc_start_is_even_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = is_even_arg_void;

       if (  run_iseq ( ( n ) , ( 0 ) )  )  
        {  return ( run_obj_t ) ( 1 ) ;

     }
       if (  run_iseq ( ( n ) , ( 1 ) )  )  
        {  return ( run_obj_t ) ( 0 ) ;

     }
       return ( run_obj_t ) ( is_odd (  run_cc_sub ( ( n ) , ( 1 ) )  ) ) ;

}
 run_obj_t is_odd_step ( run_obj_t self_void , run_obj_t is_odd_arg_void ) { 
  run_cc_start_is_odd_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = is_odd_arg_void;

       if (  run_iseq ( ( n ) , ( 0 ) )  )  
        {  return ( run_obj_t ) ( 0 ) ;

     }
       if (  run_iseq ( ( n ) , ( 1 ) )  )  
        {  return ( run_obj_t ) ( 1 ) ;

     }
       return ( run_obj_t ) ( is_even (  run_cc_sub ( ( n ) , ( 1 ) )  ) ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( is_even ( 4 ) ) ;

}

/* SPECIALIZED CODE END */
