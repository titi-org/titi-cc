/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test type qualifiers
    const int CONST_VAL = 100 ;


  int test_const ( ) {
 run_obj_t test_const_step ( run_obj_t self_void , run_obj_t test_const_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_const_step , 0 )) ;
}


  int test_volatile ( ) {
 run_obj_t test_volatile_step ( run_obj_t self_void , run_obj_t test_volatile_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_volatile_step , 0 )) ;
}


  int test_restrict ( ) {
 run_obj_t test_restrict_step ( run_obj_t self_void , run_obj_t test_restrict_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_restrict_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_const_step ( run_obj_t self_void , run_obj_t test_const_arg_void ) { 
  run_cc_start_test_const_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      const int a = 42 ; 
      const int * p1 = & a ; 
       int * const p2 = ( int * ) & a ; 
        const int * const p3 = & a ; 
   return ( run_obj_t ) ( * p1 ) ;

}
 run_obj_t test_volatile_step ( run_obj_t self_void , run_obj_t test_volatile_arg_void ) { 
  run_cc_start_test_volatile_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      volatile int v = 0 ; 
    v = 10 ; 
   return ( run_obj_t ) ( v ) ;

}
 run_obj_t test_restrict_step ( run_obj_t self_void , run_obj_t test_restrict_arg_void ) { 
  run_cc_start_test_restrict_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int arr [ 10 ] ; 
       int * restrict p = arr ; 
    * p = 42 ; 
   return ( run_obj_t ) ( * p ) ;

}

/* SPECIALIZED CODE END */
