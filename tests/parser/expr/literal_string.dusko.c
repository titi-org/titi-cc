/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test string literals
     extern int printf ( const char * fmt , ... ) ;


  int test_string_literals ( ) {
 run_obj_t test_string_literals_step ( run_obj_t self_void , run_obj_t test_string_literals_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_string_literals_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_string_literals_step ( run_obj_t self_void , run_obj_t test_string_literals_arg_void ) { 
  run_cc_start_test_string_literals_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      const char * a = "hello" ; 
      const char * b = "world" ; 
      const char * c = "line1\nline2" ; 
      const char * d = "tab\there" ; 
      const char * e = "" ; 
    printf ( "%s %s\n" , a , b ) ; 
   printf ( "%s\n" , c ) ; 
   printf ( "%s\n" , d ) ; 
   return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
