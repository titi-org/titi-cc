/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 16: Specialization - lattice structure
   int generic ( int x ) {
 run_obj_t generic_step ( run_obj_t self_void , run_obj_t generic_arg_void );
  return ((int) run_step ( (run_obj_t)kleene_step , (run_obj_t)generic_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t generic_step ( run_obj_t self_void , run_obj_t generic_arg_void ) { 
  run_cc_start_generic_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = generic_arg_void;

       if (  run_iseq ( ( x ) , ( 0 ) )  )  
        {  return ( run_obj_t ) ( 0 ) ;

     }
         return ( run_obj_t ) (  nat_mult ( ( x ) , (  ( self ( (run_obj_t)self , (run_obj_t)( run_obj_t [ ] ) {  run_cc_sub ( ( x ) , ( 1 ) )  } ) )  ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( generic ( 5 ) ) ;

}

/* SPECIALIZED CODE END */
