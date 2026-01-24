/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test array declarations
  int test_arrays ( ) {
 run_obj_t test_arrays_step ( run_obj_t self_void , run_obj_t test_arrays_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_arrays_step , 0 )) ;
}


  int test_2d_array ( ) {
 run_obj_t test_2d_array_step ( run_obj_t self_void , run_obj_t test_2d_array_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_2d_array_step , 0 )) ;
}


  int test_array_of_pointers ( ) {
 run_obj_t test_array_of_pointers_step ( run_obj_t self_void , run_obj_t test_array_of_pointers_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_array_of_pointers_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_arrays_step ( run_obj_t self_void , run_obj_t test_arrays_arg_void ) { 
  run_cc_start_test_arrays_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int arr1 [ 10 ] ; 
         int arr2 [ 5 ] = { 1 , 2 , 3 , 4 , 5 } ; 
       int arr3 [ ] = { 10 , 20 , 30 } ; 

    arr1 [ 0 ] = 1 ; 
    arr1 [ 9 ] = 10 ; 

       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( arr1 [ 0 ] ) , ( arr2 [ 0 ] ) )  ) , ( arr3 [ 0 ] ) )  ) ;

}
 run_obj_t test_2d_array_step ( run_obj_t self_void , run_obj_t test_2d_array_arg_void ) { 
  run_cc_start_test_2d_array_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int mat [ 3 ] [ 4 ] ; 
    mat [ 0 ] [ 0 ] = 1 ; 
    mat [ 2 ] [ 3 ] = 12 ; 
     return ( run_obj_t ) (  nat_add ( ( mat [ 0 ] [ 0 ] ) , ( mat [ 2 ] [ 3 ] ) )  ) ;

}
 run_obj_t test_array_of_pointers_step ( run_obj_t self_void , run_obj_t test_array_of_pointers_arg_void ) { 
  run_cc_start_test_array_of_pointers_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

           int a = 1 , b = 2 , c = 3 ; 
       int * arr [ 3 ] = { & a , & b , & c } ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( * arr [ 0 ] ) , ( * arr [ 1 ] ) )  ) , ( * arr [ 2 ] ) )  ) ;

}

/* SPECIALIZED CODE END */
