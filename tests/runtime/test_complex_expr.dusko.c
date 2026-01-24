/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// #include <stdio.h>
     extern int printf ( const char * format , ... ) ;


// Test complex expressions
     long ternary_max ( long a , long b ) {
 run_obj_t ternary_max_step ( run_obj_t self_void , run_obj_t ternary_max_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)ternary_max_step , (run_obj_t)args )) ;
}


       long nested_ternary ( long a , long b , long c ) {
 run_obj_t nested_ternary_step ( run_obj_t self_void , run_obj_t nested_ternary_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) , (run_obj_t)(c) };
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)nested_ternary_step , (run_obj_t)args )) ;
}


       long complex_arithmetic ( long x , long y , long z ) {
 run_obj_t complex_arithmetic_step ( run_obj_t self_void , run_obj_t complex_arithmetic_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) , (run_obj_t)(z) };
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)complex_arithmetic_step , (run_obj_t)args )) ;
}


       long logical_expr ( long a , long b , long c ) {
 run_obj_t logical_expr_step ( run_obj_t self_void , run_obj_t logical_expr_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) , (run_obj_t)(c) };
  return ((long) run_step ( (run_obj_t)program_step , (run_obj_t)logical_expr_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t ternary_max_step ( run_obj_t self_void , run_obj_t ternary_max_arg_void ) { 
  run_cc_start_ternary_max_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)ternary_max_arg_void)[0];
  __auto_type b = ((run_obj_t*)ternary_max_arg_void)[1];
        return ( run_obj_t ) ( ((  a > b  ) ? ( a ) : ( b )) ) ;
 }
 run_obj_t nested_ternary_step ( run_obj_t self_void , run_obj_t nested_ternary_arg_void ) { 
  run_cc_start_nested_ternary_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)nested_ternary_arg_void)[0];
  __auto_type b = ((run_obj_t*)nested_ternary_arg_void)[1];
  __auto_type c = ((run_obj_t*)nested_ternary_arg_void)[2];

                     return ( run_obj_t ) ( ((  a > b  ) ? ( ( ((  a > c  ) ? ( a ) : ( c )) ) ) : ( ( ((  b > c  ) ? ( b ) : ( c )) ) )) ) ;

}
 run_obj_t complex_arithmetic_step ( run_obj_t self_void , run_obj_t complex_arithmetic_arg_void ) { 
  run_cc_start_complex_arithmetic_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)complex_arithmetic_arg_void)[0];
  __auto_type y = ((run_obj_t*)complex_arithmetic_arg_void)[1];
  __auto_type z = ((run_obj_t*)complex_arithmetic_arg_void)[2];

             return ( run_obj_t ) (   (  x + y  ) * (  z - x  )  / (  y + ( 1 )  )  ) ;

}
 run_obj_t logical_expr_step ( run_obj_t self_void , run_obj_t logical_expr_arg_void ) { 
  run_cc_start_logical_expr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)logical_expr_arg_void)[0];
  __auto_type b = ((run_obj_t*)logical_expr_arg_void)[1];
  __auto_type c = ((run_obj_t*)logical_expr_arg_void)[2];

                 return ( run_obj_t ) ( ((  (   a > ( 0 )  &&  b > ( 0 )   ) || (  c < ( 0 )  )  ) ? ( ( 1 ) ) : ( ( 0 ) )) ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    printf ( "max(5, 3): %ld\n" , ternary_max ( ( 5 ) , ( 3 ) ) ) ; 
     printf ( "max(7, 9, 2): %ld\n" , nested_ternary ( ( 7 ) , ( 9 ) , ( 2 ) ) ) ; 
     printf ( "complex(10, 5, 20): %ld\n" , complex_arithmetic ( ( 10 ) , ( 5 ) , ( 20 ) ) ) ; 
     printf ( "logical(1, 1, 0): %ld\n" , logical_expr ( ( 1 ) , ( 1 ) , ( 0 ) ) ) ; 
     printf ( "logical(0, 1, -1): %ld\n" , logical_expr ( ( 0 ) , ( 1 ) ,  - ( 1 )  ) ) ; 
   return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
