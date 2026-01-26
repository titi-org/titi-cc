/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 9: Array basic declaration and access
  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int arr [ 5 ] ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( 5 ) )  )  
        {     arr [ i ] =  nat_add ( ( i ) , ( 1 ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( arr [ 2 ] ) ;

}

/* SPECIALIZED CODE END */
