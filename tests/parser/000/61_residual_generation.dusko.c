/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 17: Driving - residual generation
     int eval_expr ( int x , int y ) {
 run_obj_t eval_expr_step ( run_obj_t self_void , run_obj_t eval_expr_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)eval_expr_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t eval_expr_step ( run_obj_t self_void , run_obj_t eval_expr_arg_void ) { 
  run_cc_start_eval_expr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)eval_expr_arg_void)[0];
  __auto_type y = ((run_obj_t*)eval_expr_arg_void)[1];

         int a =  nat_add ( ( x ) , ( y ) )  ; 
         int b =  nat_mult ( ( a ) , ( 2 ) )  ; 
     return ( run_obj_t ) ( b ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) ( eval_expr ( 3 , 4 ) ) ;

}

/* SPECIALIZED CODE END */
