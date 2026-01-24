/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test function call expressions
     extern int printf ( const char * fmt , ... ) ;


  int no_args ( ) {
 run_obj_t no_args_step ( run_obj_t self_void , run_obj_t no_args_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)no_args_step , 0 )) ;
}


   int one_arg ( int x ) {
 run_obj_t one_arg_step ( run_obj_t self_void , run_obj_t one_arg_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)one_arg_step , (run_obj_t)(x) )) ;
}


       int three_args ( int a , int b , int c ) {
 run_obj_t three_args_step ( run_obj_t self_void , run_obj_t three_args_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) , (run_obj_t)(c) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)three_args_step , (run_obj_t)args )) ;
}


  int test_calls ( ) {
 run_obj_t test_calls_step ( run_obj_t self_void , run_obj_t test_calls_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_calls_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t no_args_step ( run_obj_t self_void , run_obj_t no_args_arg_void ) { 
  run_cc_start_no_args_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   return ( run_obj_t ) ( 42 ) ;

}
 run_obj_t one_arg_step ( run_obj_t self_void , run_obj_t one_arg_arg_void ) { 
  run_cc_start_one_arg_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = one_arg_arg_void;

     return ( run_obj_t ) (  nat_mult ( ( x ) , ( 2 ) )  ) ;

}
 run_obj_t three_args_step ( run_obj_t self_void , run_obj_t three_args_arg_void ) { 
  run_cc_start_three_args_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)three_args_arg_void)[0];
  __auto_type b = ((run_obj_t*)three_args_arg_void)[1];
  __auto_type c = ((run_obj_t*)three_args_arg_void)[2];

       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( a ) , ( b ) )  ) , ( c ) )  ) ;

}
 run_obj_t test_calls_step ( run_obj_t self_void , run_obj_t test_calls_arg_void ) { 
  run_cc_start_test_calls_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int r1 = no_args ( ) ; 
     int r2 = one_arg ( 5 ) ; 
       int r3 = three_args ( 1 , 2 , 3 ) ; 
     int r4 = one_arg ( no_args ( ) ) ; 
         return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( ( r1 ) , ( r2 ) )  ) , ( r3 ) )  ) , ( r4 ) )  ) ;

}

/* SPECIALIZED CODE END */
