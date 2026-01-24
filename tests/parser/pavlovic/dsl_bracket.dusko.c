/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
/* DSL bracket form edge cases */

  void test_bracket ( void ) {
 run_obj_t test_bracket_step ( run_obj_t self_void , run_obj_t test_bracket_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)test_bracket_step , 0 );
}


/* SPECIALIZED CODE START */
 run_obj_t test_bracket_step ( run_obj_t self_void , run_obj_t test_bracket_arg_void ) { 
  run_cc_start_test_bracket_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

          int x = run ( 1 ) ; 
       int y = EVAL ( 2 ) ; 
          int z = 3 ; 
  return (run_obj_t)0;
}

/* SPECIALIZED CODE END */
