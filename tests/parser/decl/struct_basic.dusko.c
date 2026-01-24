/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test basic struct declarations
  
   
   
struct Point { int x ; int y ; } ;


  
    
   
   
struct Rectangle { struct Point origin ; int width ; int height ; } ;


  int test_struct_decl ( ) {
 run_obj_t test_struct_decl_step ( run_obj_t self_void , run_obj_t test_struct_decl_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_struct_decl_step , 0 )) ;
}


  int test_nested_struct ( ) {
 run_obj_t test_nested_struct_step ( run_obj_t self_void , run_obj_t test_nested_struct_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_struct_step , 0 )) ;
}


  
         
struct Anonymous { struct { int a ; int b ; } inner ; } ;


/* SPECIALIZED CODE START */
 run_obj_t test_struct_decl_step ( run_obj_t self_void , run_obj_t test_struct_decl_arg_void ) { 
  run_cc_start_test_struct_decl_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    struct Point p ; 
    p . x = 10 ; 
    p . y = 20 ; 
     return ( run_obj_t ) (  nat_add ( ( p . x ) , ( p . y ) )  ) ;

}
 run_obj_t test_nested_struct_step ( run_obj_t self_void , run_obj_t test_nested_struct_arg_void ) { 
  run_cc_start_test_nested_struct_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    struct Rectangle r ; 
    r . origin . x = 0 ; 
    r . origin . y = 0 ; 
    r . width = 100 ; 
    r . height = 50 ; 
     return ( run_obj_t ) (  nat_mult ( ( r . width ) , ( r . height ) )  ) ;

}

/* SPECIALIZED CODE END */
