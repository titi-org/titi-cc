/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test integer literals
  int test_int_literals ( ) {
 run_obj_t test_int_literals_step ( run_obj_t self_void , run_obj_t test_int_literals_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_int_literals_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_int_literals_step ( run_obj_t self_void , run_obj_t test_int_literals_arg_void ) { 
  run_cc_start_test_int_literals_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 42 ; 
     int b = 0 ; 
     int c = 0x1F ; 
     int d = 077 ; 
         return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( ( a ) , ( b ) )  ) , ( c ) )  ) , ( d ) )  ) ;

}

/* SPECIALIZED CODE END */
