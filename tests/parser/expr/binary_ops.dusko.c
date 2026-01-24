/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test binary operators
  int test_arithmetic ( ) {
 run_obj_t test_arithmetic_step ( run_obj_t self_void , run_obj_t test_arithmetic_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_arithmetic_step , 0 )) ;
}


  int test_comparison ( ) {
 run_obj_t test_comparison_step ( run_obj_t self_void , run_obj_t test_comparison_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_comparison_step , 0 )) ;
}


  int test_bitwise ( ) {
 run_obj_t test_bitwise_step ( run_obj_t self_void , run_obj_t test_bitwise_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_bitwise_step , 0 )) ;
}


  int test_logical ( ) {
 run_obj_t test_logical_step ( run_obj_t self_void , run_obj_t test_logical_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_logical_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_arithmetic_step ( run_obj_t self_void , run_obj_t test_arithmetic_arg_void ) { 
  run_cc_start_test_arithmetic_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int a = 10 , b = 3 ; 
       int add =  nat_add ( ( a ) , ( b ) )  ; 
       int sub =  run_cc_sub ( ( a ) , ( b ) )  ; 
       int mul =  nat_mult ( ( a ) , ( b ) )  ; 
       int div =  run_cc_div ( ( a ) , ( b ) )  ; 
       int mod =  run_cc_mod ( ( a ) , ( b ) )  ; 
           return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( ( add ) , ( sub ) )  ) , ( mul ) )  ) , ( div ) )  ) , ( mod ) )  ) ;

}
 run_obj_t test_comparison_step ( run_obj_t self_void , run_obj_t test_comparison_arg_void ) { 
  run_cc_start_test_comparison_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int a = 5 , b = 3 ; 
       int lt =  run_cc_lt ( ( a ) , ( b ) )  ; 
       int gt =  run_cc_gt ( ( a ) , ( b ) )  ; 
       int le =  run_cc_le ( ( a ) , ( b ) )  ; 
       int ge =  run_cc_ge ( ( a ) , ( b ) )  ; 
       int eq =  run_iseq ( ( a ) , ( b ) )  ; 
       int ne =  run_bool_not (  run_iseq ( ( a ) , ( b ) )  )  ; 
             return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( ( lt ) , ( gt ) )  ) , ( le ) )  ) , ( ge ) )  ) , ( eq ) )  ) , ( ne ) )  ) ;

}
 run_obj_t test_bitwise_step ( run_obj_t self_void , run_obj_t test_bitwise_arg_void ) { 
  run_cc_start_test_bitwise_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int a = 0xF0 , b = 0x0F ; 
       int and_op = a & b ; 
       int or_op = a | b ; 
       int xor_op = a ^ b ; 
       int shl = a << 4 ; 
       int shr = a >> 4 ; 
           return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( ( and_op ) , ( or_op ) )  ) , ( xor_op ) )  ) , ( shl ) )  ) , ( shr ) )  ) ;

}
 run_obj_t test_logical_step ( run_obj_t self_void , run_obj_t test_logical_arg_void ) { 
  run_cc_start_test_logical_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int a = 1 , b = 0 ; 
       int and_op =  run_cc_and ( ( a ) , ( b ) )  ; 
       int or_op =  run_cc_or ( ( a ) , ( b ) )  ; 
     return ( run_obj_t ) (  nat_add ( ( and_op ) , ( or_op ) )  ) ;

}

/* SPECIALIZED CODE END */
