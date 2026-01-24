/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test while loops
  int test_while_simple ( ) {
 run_obj_t test_while_simple_step ( run_obj_t self_void , run_obj_t test_while_simple_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_while_simple_step , 0 )) ;
}


  int test_while_empty_body ( ) {
 run_obj_t test_while_empty_body_step ( run_obj_t self_void , run_obj_t test_while_empty_body_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_while_empty_body_step , 0 )) ;
}


  int test_nested_while ( ) {
 run_obj_t test_nested_while_step ( run_obj_t self_void , run_obj_t test_nested_while_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_while_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_while_simple_step ( run_obj_t self_void , run_obj_t test_while_simple_arg_void ) { 
  run_cc_start_test_while_simple_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
     int sum = 0 ; 
     while (  run_cc_lt ( ( i ) , ( 10 ) )  )  
    {   sum += i ; 
    i ++ ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_while_empty_body_step ( run_obj_t self_void , run_obj_t test_while_empty_body_arg_void ) { 
  run_cc_start_test_while_empty_body_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
     while (  run_cc_lt ( ( i ++ ) , ( 5 ) )  ) 
    ; 
   return ( run_obj_t ) ( i ) ;

}
 run_obj_t test_nested_while_step ( run_obj_t self_void , run_obj_t test_nested_while_arg_void ) { 
  run_cc_start_test_nested_while_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
     int count = 0 ; 
     while (  run_cc_lt ( ( i ) , ( 3 ) )  )  
    {    int j = 0 ; 
       while (  run_cc_lt ( ( j ) , ( 3 ) )  )  
      { count ++ ; 
      j ++ ; 
     }
    i ++ ; 
   }
   return ( run_obj_t ) ( count ) ;

}

/* SPECIALIZED CODE END */
