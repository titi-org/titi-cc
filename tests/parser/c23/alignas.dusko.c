/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test C23 alignas specifier

// alignas with constant expression
  alignas ( 16 ) int aligned_global ;


// alignas with type
  alignas ( double ) int aligned_to_double ;


// alignas in local variable
  int test_alignas_local ( ) {
 run_obj_t test_alignas_local_step ( run_obj_t self_void , run_obj_t test_alignas_local_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_alignas_local_step , 0 )) ;
}


// struct (alignas in struct members needs separate grammar fix)
  
   
   
struct AlignedStruct { int x ; double y ; } ;


// multiple alignas specifiers
   alignas ( 64 ) static int heavily_aligned ;


  int test_alignas_struct ( ) {
 run_obj_t test_alignas_struct_step ( run_obj_t self_void , run_obj_t test_alignas_struct_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_alignas_struct_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_alignas_local_step ( run_obj_t self_void , run_obj_t test_alignas_local_arg_void ) { 
  run_cc_start_test_alignas_local_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      alignas ( 8 ) int aligned_local = 42 ; 
   return ( run_obj_t ) ( aligned_local ) ;

}
 run_obj_t test_alignas_struct_step ( run_obj_t self_void , run_obj_t test_alignas_struct_arg_void ) { 
  run_cc_start_test_alignas_struct_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    struct AlignedStruct s ; 
    s . x = 10 ; 
    s . y = 20.0 ; 
   return ( run_obj_t ) ( s . x ) ;

}

/* SPECIALIZED CODE END */
