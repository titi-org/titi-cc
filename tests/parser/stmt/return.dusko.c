/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test return statements
  void test_return_void ( ) {
 run_obj_t test_return_void_step ( run_obj_t self_void , run_obj_t test_return_void_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)test_return_void_step , 0 );
}


  int test_return_value ( ) {
 run_obj_t test_return_value_step ( run_obj_t self_void , run_obj_t test_return_value_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_return_value_step , 0 )) ;
}


   int test_return_expr ( int x ) {
 run_obj_t test_return_expr_step ( run_obj_t self_void , run_obj_t test_return_expr_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_return_expr_step , (run_obj_t)(x) )) ;
}


   int test_multiple_returns ( int x ) {
 run_obj_t test_multiple_returns_step ( run_obj_t self_void , run_obj_t test_multiple_returns_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_multiple_returns_step , (run_obj_t)(x) )) ;
}


  int test_return_in_loop ( ) {
 run_obj_t test_return_in_loop_step ( run_obj_t self_void , run_obj_t test_return_in_loop_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_return_in_loop_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_return_void_step ( run_obj_t self_void , run_obj_t test_return_void_arg_void ) { 
  run_cc_start_test_return_void_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  return;

  return (run_obj_t)0;
}
 run_obj_t test_return_value_step ( run_obj_t self_void , run_obj_t test_return_value_arg_void ) { 
  run_cc_start_test_return_value_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   return ( run_obj_t ) ( 42 ) ;

}
 run_obj_t test_return_expr_step ( run_obj_t self_void , run_obj_t test_return_expr_arg_void ) { 
  run_cc_start_test_return_expr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_return_expr_arg_void;

       return ( run_obj_t ) (  nat_add ( (  nat_mult ( ( x ) , ( 2 ) )  ) , ( 1 ) )  ) ;

}
 run_obj_t test_multiple_returns_step ( run_obj_t self_void , run_obj_t test_multiple_returns_arg_void ) { 
  run_cc_start_test_multiple_returns_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_multiple_returns_arg_void;

     if (  run_cc_lt ( ( x ) , ( 0 ) )  ) 
     return ( run_obj_t ) (  - 1  ) ;

     if (  run_iseq ( ( x ) , ( 0 ) )  ) 
     return ( run_obj_t ) ( 0 ) ;

   return ( run_obj_t ) ( 1 ) ;

}
 run_obj_t test_return_in_loop_step ( run_obj_t self_void , run_obj_t test_return_in_loop_arg_void ) { 
  run_cc_start_test_return_in_loop_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  for (     int i = 0;     run_cc_lt ( ( i ) , ( 100 ) )  ;  i ++  )  
    {    if (  run_iseq ( ( i ) , ( 42 ) )  ) 
       return ( run_obj_t ) ( i ) ;

   }
   return ( run_obj_t ) (  - 1  ) ;

}

/* SPECIALIZED CODE END */
