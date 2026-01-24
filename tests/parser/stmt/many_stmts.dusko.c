/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
/* Many statements stress test */

  void many ( void ) {
 run_obj_t many_step ( run_obj_t self_void , run_obj_t many_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)many_step , 0 );
}


/* SPECIALIZED CODE START */
 run_obj_t many_step ( run_obj_t self_void , run_obj_t many_arg_void ) { 
  run_cc_start_many_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int x = 0 ; 
    x ++ ;  x ++ ;  x ++ ;  x ++ ;  x ++ ; 
    x ++ ;  x ++ ;  x ++ ;  x ++ ;  x ++ ; 
    x ++ ;  x ++ ;  x ++ ;  x ++ ;  x ++ ; 
    x ++ ;  x ++ ;  x ++ ;  x ++ ;  x ++ ; 
    x ++ ;  x ++ ;  x ++ ;  x ++ ;  x ++ ; 
  return (run_obj_t)0;
}

/* SPECIALIZED CODE END */
