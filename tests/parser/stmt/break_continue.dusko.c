/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test break and continue
  int test_break_while ( ) {
 run_obj_t test_break_while_step ( run_obj_t self_void , run_obj_t test_break_while_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_break_while_step , 0 )) ;
}


  int test_continue_while ( ) {
 run_obj_t test_continue_while_step ( run_obj_t self_void , run_obj_t test_continue_while_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_continue_while_step , 0 )) ;
}


  int test_break_for ( ) {
 run_obj_t test_break_for_step ( run_obj_t self_void , run_obj_t test_break_for_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_break_for_step , 0 )) ;
}


  int test_continue_for ( ) {
 run_obj_t test_continue_for_step ( run_obj_t self_void , run_obj_t test_continue_for_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_continue_for_step , 0 )) ;
}


  int test_nested_break ( ) {
 run_obj_t test_nested_break_step ( run_obj_t self_void , run_obj_t test_nested_break_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_nested_break_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_break_while_step ( run_obj_t self_void , run_obj_t test_break_while_arg_void ) { 
  run_cc_start_test_break_while_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
   while ( 1 )  
    {    if (  run_cc_ge ( ( i ) , ( 5 ) )  ) 
      break ; 
    i ++ ; 
   }
   return ( run_obj_t ) ( i ) ;

}
 run_obj_t test_continue_while_step ( run_obj_t self_void , run_obj_t test_continue_while_arg_void ) { 
  run_cc_start_test_continue_while_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
     int i = 0 ; 
     while (  run_cc_lt ( ( i ) , ( 10 ) )  )  
    { i ++ ; 
         if (  run_iseq ( (  run_cc_mod ( ( i ) , ( 2 ) )  ) , ( 0 ) )  ) 
      continue ; 
      sum += i ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_break_for_step ( run_obj_t self_void , run_obj_t test_break_for_arg_void ) { 
  run_cc_start_test_break_for_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int last = 0 ; 
  for (     int i = 0;     run_cc_lt ( ( i ) , ( 100 ) )  ;  i ++  )  
    {    if (  run_cc_gt ( ( i ) , ( 5 ) )  ) 
      break ; 
      last = i ; 
   }
   return ( run_obj_t ) ( last ) ;

}
 run_obj_t test_continue_for_step ( run_obj_t self_void , run_obj_t test_continue_for_arg_void ) { 
  run_cc_start_test_continue_for_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int sum = 0 ; 
  for (     int i = 0;     run_cc_lt ( ( i ) , ( 10 ) )  ;  i ++  )  
    {      if (  run_iseq ( (  run_cc_mod ( ( i ) , ( 2 ) )  ) , ( 1 ) )  ) 
      continue ; 
      sum += i ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t test_nested_break_step ( run_obj_t self_void , run_obj_t test_nested_break_arg_void ) { 
  run_cc_start_test_nested_break_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int count = 0 ; 
  for (     int i = 0;     run_cc_lt ( ( i ) , ( 5 ) )  ;  i ++  )  
    { for (     int j = 0;     run_cc_lt ( ( j ) , ( 5 ) )  ;  j ++  )  
      {    if (  run_iseq ( ( j ) , ( 2 ) )  ) 
        break ; 
      count ++ ; 
     }
   }
   return ( run_obj_t ) ( count ) ;

}

/* SPECIALIZED CODE END */
