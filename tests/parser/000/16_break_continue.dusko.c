/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 8: Break and continue in loops
  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int i = 0 ; 
       int sum = 0 ; 
       while (  run_cc_lt ( ( i ) , ( 20 ) )  )  
        {     i =  nat_add ( ( i ) , ( 1 ) )  ; 
           if (  run_iseq ( ( i ) , ( 5 ) )  )  
            { continue ; 
         }
           if (  run_iseq ( ( i ) , ( 15 ) )  )  
            { break ; 
         }
            sum =  nat_add ( ( sum ) , ( i ) )  ; 
     }
     return ( run_obj_t ) ( sum ) ;

}

/* SPECIALIZED CODE END */
