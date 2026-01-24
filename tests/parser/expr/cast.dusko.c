/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test cast expressions
  int test_basic_cast ( ) {
 run_obj_t test_basic_cast_step ( run_obj_t self_void , run_obj_t test_basic_cast_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_basic_cast_step , 0 )) ;
}


  long test_pointer_cast ( ) {
 run_obj_t test_pointer_cast_step ( run_obj_t self_void , run_obj_t test_pointer_cast_arg_void );
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)test_pointer_cast_step , 0 )) ;
}


  int test_nested_cast ( ) {
 run_obj_t test_nested_cast_step ( run_obj_t self_void , run_obj_t test_nested_cast_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_cast_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_basic_cast_step ( run_obj_t self_void , run_obj_t test_basic_cast_arg_void ) { 
  run_cc_start_test_basic_cast_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     double d = 3.14 ; 
     int i =  nat_to_int ( d )  ; 
   return ( run_obj_t ) ( i ) ;

}
 run_obj_t test_pointer_cast_step ( run_obj_t self_void , run_obj_t test_pointer_cast_arg_void ) { 
  run_cc_start_test_pointer_cast_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 42 ; 
     long ptr =  nat_to_int ( & a )  ; 
      int * p = ( int * ) ptr ; 
   return ( run_obj_t ) ( * p ) ;

}
 run_obj_t test_nested_cast_step ( run_obj_t self_void , run_obj_t test_nested_cast_arg_void ) { 
  run_cc_start_test_nested_cast_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     char c = 'A' ; 
      int i =  nat_to_int ( ( unsigned char ) c )  ; 
   return ( run_obj_t ) ( i ) ;

}

/* SPECIALIZED CODE END */
