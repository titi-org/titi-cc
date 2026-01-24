/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
     extern int printf ( const char * fmt , ... ) ;


  
int factorial ( int n ) {
 run_obj_t factorial_step ( run_obj_t self_void , run_obj_t factorial_arg_void );
  return ((int) run_step ( (run_obj_t)kleene_step , (run_obj_t)factorial_step , (run_obj_t)(n) )) ;
}


  int main ( void ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t factorial_step ( run_obj_t self_void , run_obj_t factorial_arg_void ) { 
  run_cc_start_factorial_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = factorial_arg_void;

       if (  n <= ( 1 )  )   return ( run_obj_t ) ( ( 1 ) ) ;

         return ( run_obj_t ) (  n *  ( self ( (run_obj_t)self , (run_obj_t)( (  n - ( 1 )  ) ) ) )   ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       int f = factorial ( ( 13 ) ) ; 
     printf ( "%i\n" , f ) ; 
     return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
