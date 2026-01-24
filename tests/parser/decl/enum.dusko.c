/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test enum declarations
      enum Color { ... } ;


  
    
    
    
enum Status { ... } ;


  int test_enum ( ) {
 run_obj_t test_enum_step ( run_obj_t self_void , run_obj_t test_enum_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_enum_step , 0 )) ;
}


  int test_enum_values ( ) {
 run_obj_t test_enum_values_step ( run_obj_t self_void , run_obj_t test_enum_values_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_enum_values_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_enum_step ( run_obj_t self_void , run_obj_t test_enum_arg_void ) { 
  run_cc_start_test_enum_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      enum Color c = RED ; 
      enum Status s = OK ; 
     return ( run_obj_t ) (  nat_add ( ( c ) , ( s ) )  ) ;

}
 run_obj_t test_enum_values_step ( run_obj_t self_void , run_obj_t test_enum_values_arg_void ) { 
  run_cc_start_test_enum_values_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

             return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( ( RED ) , ( GREEN ) )  ) , ( BLUE ) )  ) , ( OK ) )  ) , ( ERROR ) )  ) , ( PENDING ) )  ) ;

}

/* SPECIALIZED CODE END */
