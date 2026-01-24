/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
/* Regression against categorical emitter emitting extra identity/nat wrappers */

     int apply ( int a , int b ) {
 run_obj_t apply_step ( run_obj_t self_void , run_obj_t apply_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)apply_step , (run_obj_t)args )) ;
}


  int main ( void ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t apply_step ( run_obj_t self_void , run_obj_t apply_arg_void ) { 
  run_cc_start_apply_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)apply_arg_void)[0];
  __auto_type b = ((run_obj_t*)apply_arg_void)[1];

           return ( run_obj_t ) ( ( a + ( 1 ) ) * ( b - ( 2 ) ) ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int result = apply ( ( 3 ) , ( 5 ) ) ; 
           return ( run_obj_t ) ( (( result == ( 12 ) ) ? ( ( 0 ) ) : ( ( 1 ) )) ) ;

}

/* SPECIALIZED CODE END */
