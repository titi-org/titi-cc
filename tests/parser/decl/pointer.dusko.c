/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test pointer declarations
  int test_pointers ( ) {
 run_obj_t test_pointers_step ( run_obj_t self_void , run_obj_t test_pointers_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_pointers_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_pointers_step ( run_obj_t self_void , run_obj_t test_pointers_arg_void ) { 
  run_cc_start_test_pointers_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 42 ; 
     int * p1 = & a ; 
     int * * p2 = & p1 ; 
     int * * * p3 = & p2 ; 

      const int * cp = & a ; 
       int * const pc = & a ; 
        const int * const cpc = & a ; 

   return ( run_obj_t ) ( * * * p3 ) ;

}

/* SPECIALIZED CODE END */
