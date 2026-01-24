/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
/* DSL keyword edge cases */

  void test_dsl ( void ) {
 run_obj_t test_dsl_step ( run_obj_t self_void , run_obj_t test_dsl_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)test_dsl_step , 0 );
}


/* SPECIALIZED CODE START */
 run_obj_t test_dsl_step ( run_obj_t self_void , run_obj_t test_dsl_arg_void ) { 
  run_cc_start_test_dsl_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    RUN ; 
    EVAL ; 
    COMPUTE ; 
    PROGRAM ; 
    DATA ; 
    IDEMPOTENT ; 
    IDENTITY ; 
    UNIT ; 
    SWAP ; 
    COPY ; 
    DELETE ; 
    FUNCTION ; 
    PROCESS ; 
    SEQUENTIAL ; 
    PARALLEL ; 
    PARTIAL ; 
    FIXPOINT ; 
    KLEENE ; 
  return (run_obj_t)0;
}

/* SPECIALIZED CODE END */
