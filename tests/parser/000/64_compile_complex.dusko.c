/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 18: End-to-end compilation - complex
     int gcd ( int a , int b ) {
 run_obj_t gcd_step ( run_obj_t self_void , run_obj_t gcd_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)gcd_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t gcd_step ( run_obj_t self_void , run_obj_t gcd_arg_void ) { 
  run_cc_start_gcd_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)gcd_arg_void)[0];
  __auto_type b = ((run_obj_t*)gcd_arg_void)[1];

       while (  run_bool_not (  run_iseq ( ( b ) , ( 0 ) )  )  )  
        {    int temp = b ; 
                b =  run_cc_sub ( ( a ) , (  nat_mult ( ( (  run_cc_div ( ( a ) , ( b ) )  ) ) , ( b ) )  ) )  ; 
          a = temp ; 
     }
     return ( run_obj_t ) ( a ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) ( gcd ( 48 , 18 ) ) ;

}

/* SPECIALIZED CODE END */
