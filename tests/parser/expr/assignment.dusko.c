/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test assignment operators
  int test_assignment ( ) {
 run_obj_t test_assignment_step ( run_obj_t self_void , run_obj_t test_assignment_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_assignment_step , 0 )) ;
}


  int test_bitwise_assignment ( ) {
 run_obj_t test_bitwise_assignment_step ( run_obj_t self_void , run_obj_t test_bitwise_assignment_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_bitwise_assignment_step , 0 )) ;
}


  int test_chain_assignment ( ) {
 run_obj_t test_chain_assignment_step ( run_obj_t self_void , run_obj_t test_chain_assignment_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_chain_assignment_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_assignment_step ( run_obj_t self_void , run_obj_t test_assignment_arg_void ) { 
  run_cc_start_test_assignment_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 10 ; 
    a += 5 ; 
    a -= 3 ; 
    a *= 2 ; 
    a /= 4 ; 
    a %= 3 ; 
   return ( run_obj_t ) ( a ) ;

}
 run_obj_t test_bitwise_assignment_step ( run_obj_t self_void , run_obj_t test_bitwise_assignment_arg_void ) { 
  run_cc_start_test_bitwise_assignment_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 0xFF ; 
    a &= 0x0F ; 
    a |= 0xF0 ; 
    a ^= 0x55 ; 
    a <<= 2 ; 
    a >>= 1 ; 
   return ( run_obj_t ) ( a ) ;

}
 run_obj_t test_chain_assignment_step ( run_obj_t self_void , run_obj_t test_chain_assignment_arg_void ) { 
  run_cc_start_test_chain_assignment_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a , b , c ; 
        a = b = c = 42 ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( a ) , ( b ) )  ) , ( c ) )  ) ;

}

/* SPECIALIZED CODE END */
