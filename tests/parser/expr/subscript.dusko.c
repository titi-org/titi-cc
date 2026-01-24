/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test array subscript expressions
  int test_subscript ( ) {
 run_obj_t test_subscript_step ( run_obj_t self_void , run_obj_t test_subscript_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_subscript_step , 0 )) ;
}


  int test_pointer_subscript ( ) {
 run_obj_t test_pointer_subscript_step ( run_obj_t self_void , run_obj_t test_pointer_subscript_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_pointer_subscript_step , 0 )) ;
}


  int test_2d_subscript ( ) {
 run_obj_t test_2d_subscript_step ( run_obj_t self_void , run_obj_t test_2d_subscript_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_2d_subscript_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_subscript_step ( run_obj_t self_void , run_obj_t test_subscript_arg_void ) { 
  run_cc_start_test_subscript_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int arr [ 5 ] ; 
    arr [ 0 ] = 10 ; 
    arr [ 1 ] = 20 ; 
    arr [ 2 ] = 30 ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( arr [ 0 ] ) , ( arr [ 1 ] ) )  ) , ( arr [ 2 ] ) )  ) ;

}
 run_obj_t test_pointer_subscript_step ( run_obj_t self_void , run_obj_t test_pointer_subscript_arg_void ) { 
  run_cc_start_test_pointer_subscript_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int arr [ 3 ] ; 
    arr [ 0 ] = 1 ; 
    arr [ 1 ] = 2 ; 
    arr [ 2 ] = 3 ; 
     int * p = arr ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( p [ 0 ] ) , ( p [ 1 ] ) )  ) , ( p [ 2 ] ) )  ) ;

}
 run_obj_t test_2d_subscript_step ( run_obj_t self_void , run_obj_t test_2d_subscript_arg_void ) { 
  run_cc_start_test_2d_subscript_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int arr [ 2 ] [ 3 ] ; 
    arr [ 0 ] [ 0 ] = 1 ; 
    arr [ 0 ] [ 1 ] = 2 ; 
    arr [ 1 ] [ 0 ] = 3 ; 
    arr [ 1 ] [ 1 ] = 4 ; 
     return ( run_obj_t ) (  nat_add ( ( arr [ 0 ] [ 0 ] ) , ( arr [ 1 ] [ 1 ] ) )  ) ;

}

/* SPECIALIZED CODE END */
