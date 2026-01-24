/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test character literals
  int test_char_literals ( ) {
 run_obj_t test_char_literals_step ( run_obj_t self_void , run_obj_t test_char_literals_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_char_literals_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_char_literals_step ( run_obj_t self_void , run_obj_t test_char_literals_arg_void ) { 
  run_cc_start_test_char_literals_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     char a = 'A' ; 
     char b = '0' ; 
     char c = '\n' ; 
     char d = '\t' ; 
     char e = '\\' ; 
     char f = '\'' ; 
             return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( (  nat_add ( ( a ) , ( b ) )  ) , ( c ) )  ) , ( d ) )  ) , ( e ) )  ) , ( f ) )  ) ;

}

/* SPECIALIZED CODE END */
