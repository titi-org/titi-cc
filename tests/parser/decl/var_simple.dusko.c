/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test simple variable declarations
 int global_int ;

   int global_init = 42 ;


  int test_local_vars ( ) {
 run_obj_t test_local_vars_step ( run_obj_t self_void , run_obj_t test_local_vars_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_local_vars_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_local_vars_step ( run_obj_t self_void , run_obj_t test_local_vars_arg_void ) { 
  run_cc_start_test_local_vars_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int a ; 
     int b = 10 ; 
     int c , d , e ; 
           int f = 1 , g = 2 , h = 3 ; 
                 return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( ( a ) , ( b ) )  ) , ( c ) )  ) , ( d ) )  ) , ( e ) )  ) , ( f ) )  ) , ( g ) )  ) , ( h ) )  ) ;

}

/* SPECIALIZED CODE END */
