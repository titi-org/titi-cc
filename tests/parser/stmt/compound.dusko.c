/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test compound statements
  int test_compound ( ) {
 run_obj_t test_compound_step ( run_obj_t self_void , run_obj_t test_compound_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_compound_step , 0 )) ;
}


  int test_nested_compound ( ) {
 run_obj_t test_nested_compound_step ( run_obj_t self_void , run_obj_t test_nested_compound_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_compound_step , 0 )) ;
}


  int test_empty_compound ( ) {
 run_obj_t test_empty_compound_step ( run_obj_t self_void , run_obj_t test_empty_compound_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_empty_compound_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_compound_step ( run_obj_t self_void , run_obj_t test_compound_arg_void ) { 
  run_cc_start_test_compound_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  
    {    int a = 1 ; 
       int b = 2 ; 
       nat_add ( ( a ) , ( b ) )  ; 
   }
   return ( run_obj_t ) ( 0 ) ;

}
 run_obj_t test_nested_compound_step ( run_obj_t self_void , run_obj_t test_nested_compound_arg_void ) { 
  run_cc_start_test_nested_compound_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  
    {    int x = 1 ; 
    
      {    int y = 2 ; 
      
        {    int z = 3 ; 
             nat_add ( (  nat_add ( ( x ) , ( y ) )  ) , ( z ) )  ; 
       }
     }
   }
   return ( run_obj_t ) ( 0 ) ;

}
 run_obj_t test_empty_compound_step ( run_obj_t self_void , run_obj_t test_empty_compound_arg_void ) { 
  run_cc_start_test_empty_compound_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  { }
   return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
