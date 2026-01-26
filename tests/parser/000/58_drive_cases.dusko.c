/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 17: Driving - case splitting
   int classify ( int x ) {
 run_obj_t classify_step ( run_obj_t self_void , run_obj_t classify_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)classify_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t classify_step ( run_obj_t self_void , run_obj_t classify_arg_void ) { 
  run_cc_start_classify_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = classify_arg_void;

       if (  run_cc_lt ( ( x ) , ( 0 ) )  )  
        {    return ( run_obj_t ) (  run_cc_sub ( ( 0 ) , ( x ) )  ) ;

     }
       if (  run_iseq ( ( x ) , ( 0 ) )  )  
        {  return ( run_obj_t ) ( 0 ) ;

     }
     return ( run_obj_t ) ( x ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

         return ( run_obj_t ) (  nat_add ( (  nat_add ( ( classify ( 42 ) ) , ( classify (  - 42  ) ) )  ) , ( classify ( 0 ) ) )  ) ;

}

/* SPECIALIZED CODE END */
