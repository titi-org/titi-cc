/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test if/else statements
   int test_if_simple ( int x ) {
 run_obj_t test_if_simple_step ( run_obj_t self_void , run_obj_t test_if_simple_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_if_simple_step , (run_obj_t)(x) )) ;
}


   int test_if_else ( int x ) {
 run_obj_t test_if_else_step ( run_obj_t self_void , run_obj_t test_if_else_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_if_else_step , (run_obj_t)(x) )) ;
}


   int test_if_block ( int x ) {
 run_obj_t test_if_block_step ( run_obj_t self_void , run_obj_t test_if_block_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_if_block_step , (run_obj_t)(x) )) ;
}


   int test_if_else_if ( int x ) {
 run_obj_t test_if_else_if_step ( run_obj_t self_void , run_obj_t test_if_else_if_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_if_else_if_step , (run_obj_t)(x) )) ;
}


     int test_nested_if ( int x , int y ) {
 run_obj_t test_nested_if_step ( run_obj_t self_void , run_obj_t test_nested_if_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_if_step , (run_obj_t)args )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_if_simple_step ( run_obj_t self_void , run_obj_t test_if_simple_arg_void ) { 
  run_cc_start_test_if_simple_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_if_simple_arg_void;

     if (  run_cc_gt ( ( x ) , ( 0 ) )  ) 
     return ( run_obj_t ) ( 1 ) ;

   return ( run_obj_t ) ( 0 ) ;

}
 run_obj_t test_if_else_step ( run_obj_t self_void , run_obj_t test_if_else_arg_void ) { 
  run_cc_start_test_if_else_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_if_else_arg_void;

     if (  run_cc_gt ( ( x ) , ( 0 ) )  ) 
     return ( run_obj_t ) ( 1 ) ;

   else 
     return ( run_obj_t ) (  - 1  ) ;

}
 run_obj_t test_if_block_step ( run_obj_t self_void , run_obj_t test_if_block_arg_void ) { 
  run_cc_start_test_if_block_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_if_block_arg_void;

     if (  run_cc_gt ( ( x ) , ( 0 ) )  )  
    {      int y =  nat_mult ( ( x ) , ( 2 ) )  ; 
     return ( run_obj_t ) ( y ) ;

   }
   return ( run_obj_t ) ( 0 ) ;

}
 run_obj_t test_if_else_if_step ( run_obj_t self_void , run_obj_t test_if_else_if_arg_void ) { 
  run_cc_start_test_if_else_if_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = test_if_else_if_arg_void;

     if (  run_cc_gt ( ( x ) , ( 0 ) )  ) 
     return ( run_obj_t ) ( 1 ) ;

   else     if (  run_cc_lt ( ( x ) , ( 0 ) )  ) 
     return ( run_obj_t ) (  - 1  ) ;

   else 
     return ( run_obj_t ) ( 0 ) ;

}
 run_obj_t test_nested_if_step ( run_obj_t self_void , run_obj_t test_nested_if_arg_void ) { 
  run_cc_start_test_nested_if_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)test_nested_if_arg_void)[0];
  __auto_type y = ((run_obj_t*)test_nested_if_arg_void)[1];

     if (  run_cc_gt ( ( x ) , ( 0 ) )  )  
    {    if (  run_cc_gt ( ( y ) , ( 0 ) )  ) 
       return ( run_obj_t ) ( 1 ) ;

     else 
       return ( run_obj_t ) ( 2 ) ;

   }
   return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
