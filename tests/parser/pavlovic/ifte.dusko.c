/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
/* ifte keyword edge case */

  void test_ifte ( void ) {
 run_obj_t test_ifte_step ( run_obj_t self_void , run_obj_t test_ifte_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)test_ifte_step , 0 );
}


/* SPECIALIZED CODE START */
 run_obj_t test_ifte_step ( run_obj_t self_void , run_obj_t test_ifte_arg_void ) { 
  run_cc_start_test_ifte_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      ifte ( 1 , 2 , 3 ) ; 
        ifte (  run_cc_gt ( ( a ) , ( b ) )  , a , b ) ; 
  return (run_obj_t)0;
}

/* SPECIALIZED CODE END */
