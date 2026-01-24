/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test member access expressions
  
   
   
struct Point { int x ; int y ; } ;


  int test_dot_access ( ) {
 run_obj_t test_dot_access_step ( run_obj_t self_void , run_obj_t test_dot_access_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_dot_access_step , 0 )) ;
}


  int test_arrow_access ( ) {
 run_obj_t test_arrow_access_step ( run_obj_t self_void , run_obj_t test_arrow_access_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_arrow_access_step , 0 )) ;
}


  
    
   
struct Nested { struct Point p ; int z ; } ;


  int test_nested_member ( ) {
 run_obj_t test_nested_member_step ( run_obj_t self_void , run_obj_t test_nested_member_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_member_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_dot_access_step ( run_obj_t self_void , run_obj_t test_dot_access_arg_void ) { 
  run_cc_start_test_dot_access_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    struct Point p ; 
    p . x = 10 ; 
    p . y = 20 ; 
     return ( run_obj_t ) (  nat_add ( ( p . x ) , ( p . y ) )  ) ;

}
 run_obj_t test_arrow_access_step ( run_obj_t self_void , run_obj_t test_arrow_access_arg_void ) { 
  run_cc_start_test_arrow_access_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    struct Point p ; 
      struct Point * ptr = & p ; 
    ptr -> x = 30 ; 
    ptr -> y = 40 ; 
     return ( run_obj_t ) (  nat_add ( ( ptr -> x ) , ( ptr -> y ) )  ) ;

}
 run_obj_t test_nested_member_step ( run_obj_t self_void , run_obj_t test_nested_member_arg_void ) { 
  run_cc_start_test_nested_member_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    struct Nested n ; 
    n . p . x = 1 ; 
    n . p . y = 2 ; 
    n . z = 3 ; 
       return ( run_obj_t ) (  nat_add ( (  nat_add ( ( n . p . x ) , ( n . p . y ) )  ) , ( n . z ) )  ) ;

}

/* SPECIALIZED CODE END */
