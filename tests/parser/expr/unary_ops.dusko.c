/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test unary operators
  int test_unary ( ) {
 run_obj_t test_unary_step ( run_obj_t self_void , run_obj_t test_unary_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_unary_step , 0 )) ;
}


  int test_increment ( ) {
 run_obj_t test_increment_step ( run_obj_t self_void , run_obj_t test_increment_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_increment_step , 0 )) ;
}


  int test_address_deref ( ) {
 run_obj_t test_address_deref_step ( run_obj_t self_void , run_obj_t test_address_deref_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_address_deref_step , 0 )) ;
}


  int test_sizeof_expr ( ) {
 run_obj_t test_sizeof_expr_step ( run_obj_t self_void , run_obj_t test_sizeof_expr_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_sizeof_expr_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_unary_step ( run_obj_t self_void , run_obj_t test_unary_arg_void ) { 
  run_cc_start_test_unary_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 5 ; 
     int neg =  - a  ; 
     int pos = + a ; 
     int not_op =  run_bool_not ( a )  ; 
     int bitnot = ~ a ; 
         return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( ( neg ) , ( pos ) )  ) , ( not_op ) )  ) , ( bitnot ) )  ) ;

}
 run_obj_t test_increment_step ( run_obj_t self_void , run_obj_t test_increment_arg_void ) { 
  run_cc_start_test_increment_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 5 ; 
     int pre_inc = ++ a ; 
     int pre_dec = -- a ; 
     int post_inc = a ++ ; 
     int post_dec = a -- ; 
         return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( ( pre_inc ) , ( pre_dec ) )  ) , ( post_inc ) )  ) , ( post_dec ) )  ) ;

}
 run_obj_t test_address_deref_step ( run_obj_t self_void , run_obj_t test_address_deref_arg_void ) { 
  run_cc_start_test_address_deref_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 42 ; 
     int * p = & a ; 
     int val = * p ; 
   return ( run_obj_t ) ( val ) ;

}
 run_obj_t test_sizeof_expr_step ( run_obj_t self_void , run_obj_t test_sizeof_expr_arg_void ) { 
  run_cc_start_test_sizeof_expr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 0 ; 
     int s1 = sizeof ( ( a ) ) ; 
     int s2 = sizeof ( int ) ; 
      int s3 = sizeof ( int * ) ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( s1 ) , ( s2 ) )  ) , ( s3 ) )  ) ;

}

/* SPECIALIZED CODE END */
