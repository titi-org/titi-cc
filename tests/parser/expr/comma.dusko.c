/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test comma expressions
  int test_comma_simple ( ) {
 run_obj_t test_comma_simple_step ( run_obj_t self_void , run_obj_t test_comma_simple_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_comma_simple_step , 0 )) ;
}


  int test_comma_side_effect ( ) {
 run_obj_t test_comma_side_effect_step ( run_obj_t self_void , run_obj_t test_comma_side_effect_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_comma_side_effect_step , 0 )) ;
}


  int test_comma_in_for ( ) {
 run_obj_t test_comma_in_for_step ( run_obj_t self_void , run_obj_t test_comma_in_for_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_comma_in_for_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_comma_simple_step ( run_obj_t self_void , run_obj_t test_comma_simple_arg_void ) { 
  run_cc_start_test_comma_simple_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int a ; 
      a = ( 1 , 2 , 3 ) ; 
   return ( run_obj_t ) ( a ) ;

}
 run_obj_t test_comma_side_effect_step ( run_obj_t self_void , run_obj_t test_comma_side_effect_arg_void ) { 
  run_cc_start_test_comma_side_effect_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int a = 0 , b = 0 ; 
             int c = ( a = 10 , b = 20 ,  nat_add ( ( a ) , ( b ) )  ) ; 
   return ( run_obj_t ) ( c ) ;

}
 run_obj_t test_comma_in_for_step ( run_obj_t self_void , run_obj_t test_comma_in_for_arg_void ) { 
  run_cc_start_test_comma_in_for_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
  for (        int i = 0 , j = 10;     run_cc_lt ( ( i ) , ( j ) )  ;   i ++ , j --  )  
    {     sum +=  nat_add ( ( i ) , ( j ) )  ; 
   }
   return ( run_obj_t ) ( sum ) ;

}

/* SPECIALIZED CODE END */
