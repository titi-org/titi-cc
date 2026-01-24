/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test various initializer forms
  int test_scalar_init ( ) {
 run_obj_t test_scalar_init_step ( run_obj_t self_void , run_obj_t test_scalar_init_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_scalar_init_step , 0 )) ;
}


  int test_array_init ( ) {
 run_obj_t test_array_init_step ( run_obj_t self_void , run_obj_t test_array_init_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_array_init_step , 0 )) ;
}


       struct Point { int x ; int y ; } ;


  int test_struct_init ( ) {
 run_obj_t test_struct_init_step ( run_obj_t self_void , run_obj_t test_struct_init_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_struct_init_step , 0 )) ;
}


  int test_nested_init ( ) {
 run_obj_t test_nested_init_step ( run_obj_t self_void , run_obj_t test_nested_init_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_init_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_scalar_init_step ( run_obj_t self_void , run_obj_t test_scalar_init_arg_void ) { 
  run_cc_start_test_scalar_init_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 42 ; 
       int b = (  nat_add ( ( 10 ) , ( 5 ) )  ) ; 
       int c =  nat_mult ( ( a ) , ( 2 ) )  ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( a ) , ( b ) )  ) , ( c ) )  ) ;

}
 run_obj_t test_array_init_step ( run_obj_t self_void , run_obj_t test_array_init_arg_void ) { 
  run_cc_start_test_array_init_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

         int arr1 [ 5 ] = { 1 , 2 , 3 , 4 , 5 } ; 
      int arr2 [ ] = { 10 , 20 } ; 
     int arr3 [ 10 ] = { 1 } ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( arr1 [ 0 ] ) , ( arr2 [ 0 ] ) )  ) , ( arr3 [ 0 ] ) )  ) ;

}
 run_obj_t test_struct_init_step ( run_obj_t self_void , run_obj_t test_struct_init_arg_void ) { 
  run_cc_start_test_struct_init_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       struct Point p1 = { 10 , 20 } ; 
       struct Point p2 = { 30 , 40 } ; 
     return ( run_obj_t ) (  nat_add ( ( p1 . x ) , ( p2 . y ) )  ) ;

}
 run_obj_t test_nested_init_step ( run_obj_t self_void , run_obj_t test_nested_init_arg_void ) { 
  run_cc_start_test_nested_init_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

          int mat [ 2 ] [ 3 ] = { { 1 , 2 , 3 } , { 4 , 5 , 6 } } ; 
     return ( run_obj_t ) (  nat_add ( ( mat [ 0 ] [ 0 ] ) , ( mat [ 1 ] [ 2 ] ) )  ) ;

}

/* SPECIALIZED CODE END */
