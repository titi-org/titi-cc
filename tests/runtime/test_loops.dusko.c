/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */


// Test various loop constructs
   long sum_while ( long n ) {
 run_obj_t sum_while_step ( run_obj_t self_void , run_obj_t sum_while_arg_void );
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)sum_while_step , (run_obj_t)(n) )) ;
}


   long sum_do_while ( long n ) {
 run_obj_t sum_do_while_step ( run_obj_t self_void , run_obj_t sum_do_while_arg_void );
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)sum_do_while_step , (run_obj_t)(n) )) ;
}


   long sum_for ( long n ) {
 run_obj_t sum_for_step ( run_obj_t self_void , run_obj_t sum_for_arg_void );
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)sum_for_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t sum_while_step ( run_obj_t self_void , run_obj_t sum_while_arg_void ) { 
  run_cc_start_sum_while_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = sum_while_arg_void;

     long sum = ( 0 ) ; 
     long i = ( 1 ) ; 
     while (  i <= n  )  
    {     sum =  sum + i  ; 
        i =  i + ( 1 )  ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t sum_do_while_step ( run_obj_t self_void , run_obj_t sum_do_while_arg_void ) { 
  run_cc_start_sum_do_while_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = sum_do_while_arg_void;

     long sum = ( 0 ) ; 
     long i = ( 1 ) ; 
  do  
    {     sum =  sum + i  ; 
        i =  i + ( 1 )  ; 
   }     while (  i <= n  ) ; 
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t sum_for_step ( run_obj_t self_void , run_obj_t sum_for_arg_void ) { 
  run_cc_start_sum_for_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = sum_for_arg_void;

     long sum = ( 0 ) ; 
  for (     long i = ( 1 );     i <= n  ;      i =  i + ( 1 )   )  
    {     sum =  sum + i  ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   printf ( "while: %ld\n" , sum_while ( ( 10 ) ) ) ; 
   printf ( "do-while: %ld\n" , sum_do_while ( ( 10 ) ) ) ; 
   printf ( "for: %ld\n" , sum_for ( ( 10 ) ) ) ; 
   return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
