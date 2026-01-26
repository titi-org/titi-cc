/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 8: Nested scopes and variable shadowing
   int x = 100 ;


   int foo ( int x ) {
 run_obj_t foo_step ( run_obj_t self_void , run_obj_t foo_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)foo_step , (run_obj_t)(x) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t foo_step ( run_obj_t self_void , run_obj_t foo_arg_void ) { 
  run_cc_start_foo_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = foo_arg_void;

       return ( run_obj_t ) (  nat_add ( ( x ) , ( 1 ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int x = 10 ; 
    
        {    int x = 20 ; 
            x =  nat_add ( ( x ) , ( 5 ) )  ; 
     }
       return ( run_obj_t ) (  nat_add ( ( x ) , ( foo ( x ) ) )  ) ;

}

/* SPECIALIZED CODE END */
