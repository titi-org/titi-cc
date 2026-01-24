/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test floating point literals
  double test_float_literals ( ) {
 run_obj_t test_float_literals_step ( run_obj_t self_void , run_obj_t test_float_literals_arg_void );
  return ((double) run_step ( (run_obj_t)program_step , (run_obj_t)test_float_literals_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_float_literals_step ( run_obj_t self_void , run_obj_t test_float_literals_arg_void ) { 
  run_cc_start_test_float_literals_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     double a = 3.14 ; 
     double b = 2.71828 ; 
     float c = 1.5f ; 
     double d = 1e10 ; 
     double e = 1.5e-3 ; 
           return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( ( a ) , ( b ) )  ) , ( c ) )  ) , ( d ) )  ) , ( e ) )  ) ;

}

/* SPECIALIZED CODE END */
