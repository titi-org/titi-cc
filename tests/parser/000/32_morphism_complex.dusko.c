/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 11: Morphism mapping - mixed morphisms
   int fib ( int n ) {
 run_obj_t fib_step ( run_obj_t self_void , run_obj_t fib_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)fib_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t fib_step ( run_obj_t self_void , run_obj_t fib_arg_void ) { 
  run_cc_start_fib_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = fib_arg_void;

       if (  run_iseq ( ( n ) , ( 0 ) )  )  
        {  return ( run_obj_t ) ( 0 ) ;

     }
       if (  run_iseq ( ( n ) , ( 1 ) )  )  
        {  return ( run_obj_t ) ( 1 ) ;

     }
       int a = 0 ; 
       int b = 1 ; 
       int i = 2 ; 
       while (  run_cc_le ( ( i ) , ( n ) )  )  
        {      int c =  nat_add ( ( a ) , ( b ) )  ; 
          a = b ; 
          b = c ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( b ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     return ( run_obj_t ) ( fib ( 10 ) ) ;

}

/* SPECIALIZED CODE END */
