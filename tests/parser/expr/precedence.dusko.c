/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test operator precedence
  int test_arith_precedence ( ) {
 run_obj_t test_arith_precedence_step ( run_obj_t self_void , run_obj_t test_arith_precedence_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_arith_precedence_step , 0 )) ;
}


  int test_compare_precedence ( ) {
 run_obj_t test_compare_precedence_step ( run_obj_t self_void , run_obj_t test_compare_precedence_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_compare_precedence_step , 0 )) ;
}


  int test_bitwise_precedence ( ) {
 run_obj_t test_bitwise_precedence_step ( run_obj_t self_void , run_obj_t test_bitwise_precedence_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_bitwise_precedence_step , 0 )) ;
}


  int test_mixed_precedence ( ) {
 run_obj_t test_mixed_precedence_step ( run_obj_t self_void , run_obj_t test_mixed_precedence_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_mixed_precedence_step , 0 )) ;
}


  int test_parentheses ( ) {
 run_obj_t test_parentheses_step ( run_obj_t self_void , run_obj_t test_parentheses_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_parentheses_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_arith_precedence_step ( run_obj_t self_void , run_obj_t test_arith_precedence_arg_void ) { 
  run_cc_start_test_arith_precedence_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  // * and / before + and -
           return ( run_obj_t ) (  run_cc_sub ( (  nat_add ( ( 2 ) , (  nat_mult ( ( 3 ) , ( 4 ) )  ) )  ) , (  run_cc_div ( ( 6 ) , ( 2 ) )  ) )  ) ;

}
 run_obj_t test_compare_precedence_step ( run_obj_t self_void , run_obj_t test_compare_precedence_arg_void ) { 
  run_cc_start_test_compare_precedence_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  // comparison before logical
         return ( run_obj_t ) (  run_cc_and ( (  run_cc_lt ( ( 1 ) , ( 2 ) )  ) , (  run_cc_gt ( ( 3 ) , ( 2 ) )  ) )  ) ;

}
 run_obj_t test_bitwise_precedence_step ( run_obj_t self_void , run_obj_t test_bitwise_precedence_arg_void ) { 
  run_cc_start_test_bitwise_precedence_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  // & before | before ^
         return ( run_obj_t ) ( 0xFF & 0x0F | 0xF0 ^ 0x55 ) ;

}
 run_obj_t test_mixed_precedence_step ( run_obj_t self_void , run_obj_t test_mixed_precedence_arg_void ) { 
  run_cc_start_test_mixed_precedence_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

           int a = 2 , b = 3 , c = 4 ; 
  // unary before binary, * before +, comparison before &&
           return ( run_obj_t ) (  run_cc_and ( (  run_cc_gt ( (  nat_add ( (  - a  ) , (  nat_mult ( ( b ) , ( c ) )  ) )  ) , ( 5 ) )  ) , (  run_bool_not ( 0 )  ) )  ) ;

}
 run_obj_t test_parentheses_step ( run_obj_t self_void , run_obj_t test_parentheses_arg_void ) { 
  run_cc_start_test_parentheses_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  // parentheses override precedence
         return ( run_obj_t ) (  nat_mult ( ( (  nat_add ( ( 2 ) , ( 3 ) )  ) ) , ( (  run_cc_sub ( ( 4 ) , ( 1 ) )  ) ) )  ) ;

}

/* SPECIALIZED CODE END */
