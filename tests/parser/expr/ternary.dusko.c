/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test ternary operator
  int test_ternary_simple ( ) {
 run_obj_t test_ternary_simple_step ( run_obj_t self_void , run_obj_t test_ternary_simple_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_ternary_simple_step , 0 )) ;
}


  int test_ternary_nested ( ) {
 run_obj_t test_ternary_nested_step ( run_obj_t self_void , run_obj_t test_ternary_nested_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_ternary_nested_step , 0 )) ;
}


  int test_ternary_chain ( ) {
 run_obj_t test_ternary_chain_step ( run_obj_t self_void , run_obj_t test_ternary_chain_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_ternary_chain_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_ternary_simple_step ( run_obj_t self_void , run_obj_t test_ternary_simple_arg_void ) { 
  run_cc_start_test_ternary_simple_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int a = 5 , b = 3 ; 
         return ( run_obj_t ) ( ((  run_cc_gt ( ( a ) , ( b ) )  ) ? ( a ) : ( b )) ) ;

}
 run_obj_t test_ternary_nested_step ( run_obj_t self_void , run_obj_t test_ternary_nested_arg_void ) { 
  run_cc_start_test_ternary_nested_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

           int a = 1 , b = 2 , c = 3 ; 
               return ( run_obj_t ) ( ((  run_cc_gt ( ( a ) , ( b ) )  ) ? ( a ) : ( ( ((  run_cc_gt ( ( b ) , ( c ) )  ) ? ( b ) : ( c )) ) )) ) ;

}
 run_obj_t test_ternary_chain_step ( run_obj_t self_void , run_obj_t test_ternary_chain_arg_void ) { 
  run_cc_start_test_ternary_chain_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int x = 2 ; 
               return ( run_obj_t ) ( ((  run_iseq ( ( x ) , ( 1 ) )  ) ? ( 10 ) : ( ((  run_iseq ( ( x ) , ( 2 ) )  ) ? ( 20 ) : ( 30 )) )) ) ;

}

/* SPECIALIZED CODE END */
