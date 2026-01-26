/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Iteration 10: Enum basic declarations
  
      
      
      
enum Color { ... } ;


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      enum Color c ; 
      c = RED ; 
     return ( run_obj_t ) ( c ) ;

}

/* SPECIALIZED CODE END */
