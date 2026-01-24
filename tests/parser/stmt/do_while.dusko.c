/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test do-while loops
  int test_do_while_simple ( ) {
 run_obj_t test_do_while_simple_step ( run_obj_t self_void , run_obj_t test_do_while_simple_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_do_while_simple_step , 0 )) ;
}


  int test_do_while_once ( ) {
 run_obj_t test_do_while_once_step ( run_obj_t self_void , run_obj_t test_do_while_once_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_do_while_once_step , 0 )) ;
}


  int test_nested_do_while ( ) {
 run_obj_t test_nested_do_while_step ( run_obj_t self_void , run_obj_t test_nested_do_while_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_do_while_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_do_while_simple_step ( run_obj_t self_void , run_obj_t test_do_while_simple_arg_void ) { 
  run_cc_start_test_do_while_simple_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
     int sum = 0 ; 
  do  
    {   sum += i ; 
    i ++ ; 
   }     while (  run_cc_lt ( ( i ) , ( 10 ) )  ) ; 
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_do_while_once_step ( run_obj_t self_void , run_obj_t test_do_while_once_arg_void ) { 
  run_cc_start_test_do_while_once_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int count = 0 ; 
  do  
    { count ++ ; 
   }   while ( 0 ) ; 
   return ( run_obj_t ) ( count ) ;

}
 run_obj_t test_nested_do_while_step ( run_obj_t self_void , run_obj_t test_nested_do_while_arg_void ) { 
  run_cc_start_test_nested_do_while_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
     int total = 0 ; 
  do  
    {    int j = 0 ; 
    do  
      { total ++ ; 
      j ++ ; 
     }     while (  run_cc_lt ( ( j ) , ( 2 ) )  ) ; 
    i ++ ; 
   }     while (  run_cc_lt ( ( i ) , ( 3 ) )  ) ; 
   return ( run_obj_t ) ( total ) ;

}

/* SPECIALIZED CODE END */
