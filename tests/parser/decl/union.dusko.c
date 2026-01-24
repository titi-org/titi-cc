/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test union declarations
  
   
   
union IntOrFloat { int i ; float f ; } ;


  int test_union ( ) {
 run_obj_t test_union_step ( run_obj_t self_void , run_obj_t test_union_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_union_step , 0 )) ;
}


  
         
         
union Tagged { struct { char tag ; int value ; } as_int ; struct { char tag ; float value ; } as_float ; } ;


/* SPECIALIZED CODE START */
 run_obj_t test_union_step ( run_obj_t self_void , run_obj_t test_union_arg_void ) { 
  run_cc_start_test_union_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    union IntOrFloat u ; 
    u . i = 42 ; 
     int a = u . i ; 
    u . f = 3.14f ; 
   return ( run_obj_t ) ( a ) ;

}

/* SPECIALIZED CODE END */
