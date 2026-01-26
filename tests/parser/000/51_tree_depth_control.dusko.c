/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 15: Supercompilation whistle - tree depth control
     int append ( int a , int b ) {
 run_obj_t append_step ( run_obj_t self_void , run_obj_t append_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)append_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t append_step ( run_obj_t self_void , run_obj_t append_arg_void ) { 
  run_cc_start_append_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)append_arg_void)[0];
  __auto_type b = ((run_obj_t*)append_arg_void)[1];

       return ( run_obj_t ) (  nat_add ( ( a ) , ( b ) )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int x = append ( 1 , 2 ) ; 
        int y = append ( x , 3 ) ; 
        int z = append ( y , 4 ) ; 
     return ( run_obj_t ) ( z ) ;

}

/* SPECIALIZED CODE END */
