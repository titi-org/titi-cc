/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test for loops
  int test_for_simple ( ) {
 run_obj_t test_for_simple_step ( run_obj_t self_void , run_obj_t test_for_simple_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_simple_step , 0 )) ;
}


  int test_for_empty_init ( ) {
 run_obj_t test_for_empty_init_step ( run_obj_t self_void , run_obj_t test_for_empty_init_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_empty_init_step , 0 )) ;
}


  int test_for_empty_cond ( ) {
 run_obj_t test_for_empty_cond_step ( run_obj_t self_void , run_obj_t test_for_empty_cond_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_empty_cond_step , 0 )) ;
}


  int test_for_empty_incr ( ) {
 run_obj_t test_for_empty_incr_step ( run_obj_t self_void , run_obj_t test_for_empty_incr_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_empty_incr_step , 0 )) ;
}


  int test_for_all_empty ( ) {
 run_obj_t test_for_all_empty_step ( run_obj_t self_void , run_obj_t test_for_all_empty_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_all_empty_step , 0 )) ;
}


  int test_for_empty_body ( ) {
 run_obj_t test_for_empty_body_step ( run_obj_t self_void , run_obj_t test_for_empty_body_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_empty_body_step , 0 )) ;
}


  int test_nested_for ( ) {
 run_obj_t test_nested_for_step ( run_obj_t self_void , run_obj_t test_nested_for_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_for_step , 0 )) ;
}


  int test_for_with_continue ( ) {
 run_obj_t test_for_with_continue_step ( run_obj_t self_void , run_obj_t test_for_with_continue_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_with_continue_step , 0 )) ;
}


  int test_for_decl_outside ( ) {
 run_obj_t test_for_decl_outside_step ( run_obj_t self_void , run_obj_t test_for_decl_outside_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_for_decl_outside_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_for_simple_step ( run_obj_t self_void , run_obj_t test_for_simple_arg_void ) { 
  run_cc_start_test_for_simple_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
  for (     int i = 0;     run_cc_lt ( ( i ) , ( 10 ) )  ;  i ++  )  
    {   sum += i ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_for_empty_init_step ( run_obj_t self_void , run_obj_t test_for_empty_init_arg_void ) { 
  run_cc_start_test_for_empty_init_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
     int sum = 0 ; 
  for (   ;     run_cc_lt ( ( i ) , ( 5 ) )  ;  i ++  )  
    {   sum += i ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_for_empty_cond_step ( run_obj_t self_void , run_obj_t test_for_empty_cond_arg_void ) { 
  run_cc_start_test_for_empty_cond_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
  for (     int i = 0;   ;  i ++  )  
    {    if (  run_cc_ge ( ( i ) , ( 5 ) )  )  break ; 
      sum += i ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_for_empty_incr_step ( run_obj_t self_void , run_obj_t test_for_empty_incr_arg_void ) { 
  run_cc_start_test_for_empty_incr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
  for (     int i = 0;     run_cc_lt ( ( i ) , ( 5 ) )  ;    )  
    {   sum += i ; 
    i ++ ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_for_all_empty_step ( run_obj_t self_void , run_obj_t test_for_all_empty_arg_void ) { 
  run_cc_start_test_for_all_empty_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
     int sum = 0 ; 
  for (   ;  ;   )  
    {    if (  run_cc_ge ( ( i ) , ( 5 ) )  )  break ; 
      sum += i ; 
    i ++ ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_for_empty_body_step ( run_obj_t self_void , run_obj_t test_for_empty_body_arg_void ) { 
  run_cc_start_test_for_empty_body_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   int i ; 
  for (    i = 0 ;     run_cc_lt ( ( i ) , ( 5 ) )  ;  i ++  ) 
    ; 
   return ( run_obj_t ) ( i ) ;

}
 run_obj_t test_nested_for_step ( run_obj_t self_void , run_obj_t test_nested_for_arg_void ) { 
  run_cc_start_test_nested_for_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int count = 0 ; 
  for (     int i = 0;     run_cc_lt ( ( i ) , ( 3 ) )  ;  i ++  )  
    { for (     int j = 0;     run_cc_lt ( ( j ) , ( 3 ) )  ;  j ++  )  
      { count ++ ; 
     }
   }
   return ( run_obj_t ) ( count ) ;

}
 run_obj_t test_for_with_continue_step ( run_obj_t self_void , run_obj_t test_for_with_continue_arg_void ) { 
  run_cc_start_test_for_with_continue_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
  for (     int i = 0;     run_cc_lt ( ( i ) , ( 10 ) )  ;  i ++  )  
    {      if (  run_iseq ( (  run_cc_mod ( ( i ) , ( 2 ) )  ) , ( 0 ) )  )  continue ; 
      sum += i ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_for_decl_outside_step ( run_obj_t self_void , run_obj_t test_for_decl_outside_arg_void ) { 
  run_cc_start_test_for_decl_outside_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
   int i ; 
  for (    i = 0 ;     run_cc_lt ( ( i ) , ( 5 ) )  ;  i ++  )  
    {   sum += i ; 
   }
     return ( run_obj_t ) (  nat_add ( ( sum ) , ( i ) )  ) ;

}

/* SPECIALIZED CODE END */
