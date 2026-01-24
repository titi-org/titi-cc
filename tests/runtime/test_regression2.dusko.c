/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Consolidated regression tests for grammar parsing
// This file combines all repro_*.c test cases




// Test 1: Simple variable declaration
   int global_int = 0 ;

   uintptr_t global_uintptr = 0 ;


// Test 2: Cast with primitive type (no typedef)
   int test_cast_int ( int x ) {
 run_obj_t test_cast_int_step ( run_obj_t self_void , run_obj_t test_cast_int_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_cast_int_step , (run_obj_t)(x) )) ;
}


// Test 3: Cast inside function body with typedef
  typedef int mytype ;

   int test_cast_typedef ( int x ) {
 run_obj_t test_cast_typedef_step ( run_obj_t self_void , run_obj_t test_cast_typedef_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_cast_typedef_step , (run_obj_t)(x) )) ;
}


// Test 4: Simple uintptr_t cast
   uintptr_t test_simple_cast ( uintptr_t x ) {
 run_obj_t test_simple_cast_step ( run_obj_t self_void , run_obj_t test_simple_cast_arg_void );
  return ((uintptr_t) run_step ( (run_obj_t)program_step , (run_obj_t)test_simple_cast_step , (run_obj_t)(x) )) ;
}


// Test 5: Return value with cast
   uintptr_t test_return_cast ( uintptr_t x ) {
 run_obj_t test_return_cast_step ( run_obj_t self_void , run_obj_t test_return_cast_arg_void );
  return ((uintptr_t) run_step ( (run_obj_t)program_step , (run_obj_t)test_return_cast_step , (run_obj_t)(x) )) ;
}


// Test 6: Function pointer cast
     typedef void * ( * step_fn ) ( void * , void * ) ;

     uintptr_t test_fnptr_cast ( void * a , void * b ) {
 run_obj_t test_fnptr_cast_step ( run_obj_t self_void , run_obj_t test_fnptr_cast_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((uintptr_t) run_step ( (run_obj_t)program_step , (run_obj_t)test_fnptr_cast_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_cast_int_step ( run_obj_t self_void , run_obj_t test_cast_int_arg_void ) { 
  run_cc_start_test_cast_int_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_cast_int_arg_void;
  return ( run_obj_t ) (  nat_to_int ( x )  ) ;
 }
 run_obj_t test_cast_typedef_step ( run_obj_t self_void , run_obj_t test_cast_typedef_arg_void ) { 
  run_cc_start_test_cast_typedef_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_cast_typedef_arg_void;
  return ( run_obj_t ) ( ( mytype ) x ) ;
 }
 run_obj_t test_simple_cast_step ( run_obj_t self_void , run_obj_t test_simple_cast_arg_void ) { 
  run_cc_start_test_simple_cast_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_simple_cast_arg_void;
  return ( run_obj_t ) ( ( uintptr_t ) x ) ;
 }
 run_obj_t test_return_cast_step ( run_obj_t self_void , run_obj_t test_return_cast_arg_void ) { 
  run_cc_start_test_return_cast_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_return_cast_arg_void;
  return ( run_obj_t ) ( ( uintptr_t ) x ) ;
 }
 run_obj_t test_fnptr_cast_step ( run_obj_t self_void , run_obj_t test_fnptr_cast_arg_void ) { 
  run_cc_start_test_fnptr_cast_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)test_fnptr_cast_arg_void)[0];
  __auto_type b = ((run_obj_t*)test_fnptr_cast_arg_void)[1];

     step_fn f = ( step_fn ) a ; 
      return ( run_obj_t ) ( ( uintptr_t ) f ( ( void * ) a , ( void * ) b ) ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  // Test all the functions
     int result = 0 ; 

    result += test_cast_int ( 42 ) ; 
    result += test_cast_typedef ( 10 ) ; 
    result +=  nat_to_int ( test_simple_cast ( 5 ) )  ; 
    result +=  nat_to_int ( test_return_cast ( 3 ) )  ; 

  printf ( "All regression tests passed\n" ) ; 
   return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
