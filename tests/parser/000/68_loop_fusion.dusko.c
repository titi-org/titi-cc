/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 19: Transformation library - loop fusion
   int fused_loops ( int n ) {
 run_obj_t fused_loops_step ( run_obj_t self_void , run_obj_t fused_loops_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)fused_loops_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t fused_loops_step ( run_obj_t self_void , run_obj_t fused_loops_arg_void ) { 
  run_cc_start_fused_loops_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = fused_loops_arg_void;

       int result = 0 ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( n ) )  )  
        {     result =  nat_add ( ( result ) , ( i ) )  ; 
            result =  nat_mult ( ( result ) , ( 1 ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( result ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( fused_loops ( 20 ) ) ;

}

/* SPECIALIZED CODE END */
