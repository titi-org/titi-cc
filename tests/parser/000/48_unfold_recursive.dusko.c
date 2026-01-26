/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 15: Supercompilation whistle - recursive unfold
   int countdown ( int n ) {
 run_obj_t countdown_step ( run_obj_t self_void , run_obj_t countdown_arg_void );
  return ((int) run_step ( (run_obj_t)kleene_step , (run_obj_t)countdown_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t countdown_step ( run_obj_t self_void , run_obj_t countdown_arg_void ) { 
  run_cc_start_countdown_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = countdown_arg_void;

       if (  run_iseq ( ( n ) , ( 0 ) )  )  
        {  return ( run_obj_t ) ( 0 ) ;

     }
         countdown_arg_void = (run_obj_t)(  run_cc_sub ( ( n ) , ( 1 ) )  );
  goto run_cc_start_countdown_step;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( countdown ( 100 ) ) ;

}

/* SPECIALIZED CODE END */
