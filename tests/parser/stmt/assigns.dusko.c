/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
/* All assignment operators edge cases */

  void f ( void ) {
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)f_step , 0 );
}


/* SPECIALIZED CODE START */
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void ) { 
  run_cc_start_f_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

           int a , b , c , d , e , f , g ; 
                a = b += c -= d *= e /= f %= g ; 
              a &= b |= c ^= d <<= e >>= f ; 
  return (run_obj_t)0;
}

/* SPECIALIZED CODE END */
