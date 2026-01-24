/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test bitfield declarations
  
      
      
      
     
      
struct Flags { unsigned int a : 1 ; unsigned int b : 2 ; unsigned int c : 5 ; unsigned int  : 0 ; unsigned int d : 8 ; } ;


  int test_bitfield ( ) {
 run_obj_t test_bitfield_step ( run_obj_t self_void , run_obj_t test_bitfield_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_bitfield_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_bitfield_step ( run_obj_t self_void , run_obj_t test_bitfield_arg_void ) { 
  run_cc_start_test_bitfield_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    struct Flags f ; 
    f . a = 1 ; 
    f . b = 3 ; 
    f . c = 16 ; 
    f . d = 255 ; 
         return ( run_obj_t ) (  nat_add ( (  nat_add ( (  nat_add ( ( f . a ) , ( f . b ) )  ) , ( f . c ) )  ) , ( f . d ) )  ) ;

}

/* SPECIALIZED CODE END */
