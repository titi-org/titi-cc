/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 16: Generalization - multiple parameters
       int combine ( int a , int b , int c ) {
 run_obj_t combine_step ( run_obj_t self_void , run_obj_t combine_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) , (run_obj_t)(c) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)combine_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t combine_step ( run_obj_t self_void , run_obj_t combine_arg_void ) { 
  run_cc_start_combine_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)combine_arg_void)[0];
  __auto_type b = ((run_obj_t*)combine_arg_void)[1];
  __auto_type c = ((run_obj_t*)combine_arg_void)[2];

         int x =  nat_add ( ( a ) , ( b ) )  ; 
         int y =  nat_add ( ( x ) , ( c ) )  ; 
     return ( run_obj_t ) ( y ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

         int r1 = combine ( 1 , 2 , 3 ) ; 
         int r2 = combine ( 4 , 5 , 6 ) ; 
       return ( run_obj_t ) (  nat_add ( ( r1 ) , ( r2 ) )  ) ;

}

/* SPECIALIZED CODE END */
