/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test goto and labels
  int test_goto_forward ( ) {
 run_obj_t test_goto_forward_step ( run_obj_t self_void , run_obj_t test_goto_forward_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_goto_forward_step , 0 )) ;
}


  int test_goto_backward ( ) {
 run_obj_t test_goto_backward_step ( run_obj_t self_void , run_obj_t test_goto_backward_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_goto_backward_step , 0 )) ;
}


  int test_multiple_labels ( ) {
 run_obj_t test_multiple_labels_step ( run_obj_t self_void , run_obj_t test_multiple_labels_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_multiple_labels_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_goto_forward_step ( run_obj_t self_void , run_obj_t test_goto_forward_arg_void ) { 
  run_cc_start_test_goto_forward_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int x = 0 ; 
   goto end ; 
    x = 100 ; 
end : 
   return ( run_obj_t ) ( x ) ;

}
 run_obj_t test_goto_backward_step ( run_obj_t self_void , run_obj_t test_goto_backward_arg_void ) { 
  run_cc_start_test_goto_backward_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int i = 0 ; 
loop : 
     if (  run_cc_lt ( ( i ) , ( 5 ) )  )  
    { i ++ ; 
     goto loop ; 
   }
   return ( run_obj_t ) ( i ) ;

}
 run_obj_t test_multiple_labels_step ( run_obj_t self_void , run_obj_t test_multiple_labels_arg_void ) { 
  run_cc_start_test_multiple_labels_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int x = 0 ; 
first : 
    x = 1 ; 
second : 
    x = 2 ; 
third : 
    x = 3 ; 
   return ( run_obj_t ) ( x ) ;

}

/* SPECIALIZED CODE END */
