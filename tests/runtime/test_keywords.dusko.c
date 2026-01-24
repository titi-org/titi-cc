/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */


       static inline int add ( int a , int b ) {
 run_obj_t add_step ( run_obj_t self_void , run_obj_t add_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)add_step , (run_obj_t)args )) ;
}


       static inline int sub ( int a , int b ) {
 run_obj_t sub_step ( run_obj_t self_void , run_obj_t sub_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)sub_step , (run_obj_t)args )) ;
}


// Simple function to test for loop
   int sum_to_n ( int n ) {
 run_obj_t sum_to_n_step ( run_obj_t self_void , run_obj_t sum_to_n_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)sum_to_n_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t add_step ( run_obj_t self_void , run_obj_t add_arg_void ) { 
  run_cc_start_add_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)add_arg_void)[0];
  __auto_type b = ((run_obj_t*)add_arg_void)[1];
    return ( run_obj_t ) (  a + b  ) ;
 }
 run_obj_t sub_step ( run_obj_t self_void , run_obj_t sub_arg_void ) { 
  run_cc_start_sub_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)sub_arg_void)[0];
  __auto_type b = ((run_obj_t*)sub_arg_void)[1];
    return ( run_obj_t ) (  a - b  ) ;
 }
 run_obj_t sum_to_n_step ( run_obj_t self_void , run_obj_t sum_to_n_arg_void ) { 
  run_cc_start_sum_to_n_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = sum_to_n_arg_void;

     int sum = ( 0 ) ; 
   int i ; 
  for (    i = ( 1 ) ;     i <= n  ;  i ++  )  
    {     sum =  sum + i  ; 
   }
   return ( run_obj_t ) ( sum ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    printf ( "Add: %d\n" , add ( ( 10 ) , ( 20 ) ) ) ; 
    printf ( "Sub: %d\n" , sub ( ( 20 ) , ( 10 ) ) ) ; 
   printf ( "Sum 1-10: %d\n" , sum_to_n ( ( 10 ) ) ) ; 
   return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
