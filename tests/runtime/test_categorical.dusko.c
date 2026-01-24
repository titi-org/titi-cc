/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */


  long simple_const ( ) {
 run_obj_t simple_const_step ( run_obj_t self_void , run_obj_t simple_const_arg_void );
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)simple_const_step , 0 )) ;
}


     long add_vars ( long x , long y ) {
 run_obj_t add_vars_step ( run_obj_t self_void , run_obj_t add_vars_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) };
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)add_vars_step , (run_obj_t)args )) ;
}


   long factorial_recursive ( long n ) {
 run_obj_t factorial_recursive_step ( run_obj_t self_void , run_obj_t factorial_recursive_arg_void );
  return ((long) run_step ( (run_obj_t)kleene_step , (run_obj_t)factorial_recursive_step , (run_obj_t)(n) )) ;
}


         long multiple_args ( long a , long b , long c , long d ) {
 run_obj_t multiple_args_step ( run_obj_t self_void , run_obj_t multiple_args_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) , (run_obj_t)(c) , (run_obj_t)(d) };
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)multiple_args_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t simple_const_step ( run_obj_t self_void , run_obj_t simple_const_arg_void ) { 
  run_cc_start_simple_const_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  return ( run_obj_t ) ( ( 123 ) ) ;
 }
 run_obj_t add_vars_step ( run_obj_t self_void , run_obj_t add_vars_arg_void ) { 
  run_cc_start_add_vars_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)add_vars_arg_void)[0];
  __auto_type y = ((run_obj_t*)add_vars_arg_void)[1];
    return ( run_obj_t ) (  x + y  ) ;
 }
 run_obj_t factorial_recursive_step ( run_obj_t self_void , run_obj_t factorial_recursive_arg_void ) { 
  run_cc_start_factorial_recursive_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = factorial_recursive_arg_void;

     if (  n <= ( 1 )  ) 
     return ( run_obj_t ) ( ( 1 ) ) ;

       return ( run_obj_t ) (  n *  ( self ( (run_obj_t)self , (run_obj_t)( (  n - ( 1 )  ) ) ) )   ) ;

}
 run_obj_t multiple_args_step ( run_obj_t self_void , run_obj_t multiple_args_arg_void ) { 
  run_cc_start_multiple_args_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)multiple_args_arg_void)[0];
  __auto_type b = ((run_obj_t*)multiple_args_arg_void)[1];
  __auto_type c = ((run_obj_t*)multiple_args_arg_void)[2];
  __auto_type d = ((run_obj_t*)multiple_args_arg_void)[3];
        return ( run_obj_t ) (  (  a + b  ) * (  c - d  )  ) ;
 }
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   printf ( "simple_const: %ld\n" , simple_const ( ) ) ; 
    printf ( "add_vars(10, 20): %ld\n" , add_vars ( ( 10 ) , ( 20 ) ) ) ; 
   printf ( "factorial_recursive(5): %ld\n" , factorial_recursive ( ( 5 ) ) ) ; 
      printf ( "multiple_args(1, 2, 10, 5): %ld\n" , multiple_args ( ( 1 ) , ( 2 ) , ( 10 ) , ( 5 ) ) ) ; 
   return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
