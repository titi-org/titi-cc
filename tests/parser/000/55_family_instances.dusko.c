/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Iteration 16: Specialization - family of instances
     int transform ( int base , int n ) {
 run_obj_t transform_step ( run_obj_t self_void , run_obj_t transform_arg_void );
  run_obj_t args[] = { (run_obj_t)(base) , (run_obj_t)(n) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)transform_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t transform_step ( run_obj_t self_void , run_obj_t transform_arg_void ) { 
  run_cc_start_transform_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type base = ((run_obj_t*)transform_arg_void)[0];
  __auto_type n = ((run_obj_t*)transform_arg_void)[1];

       int result = base ; 
       int i = 0 ; 
       while (  run_cc_lt ( ( i ) , ( n ) )  )  
        {     result =  nat_mult ( ( result ) , ( 2 ) )  ; 
            i =  nat_add ( ( i ) , ( 1 ) )  ; 
     }
     return ( run_obj_t ) ( result ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        int f1 = transform ( 1 , 3 ) ; 
        int f2 = transform ( 2 , 3 ) ; 
        int f3 = transform ( 3 , 3 ) ; 
         return ( run_obj_t ) (  nat_add ( (  nat_add ( ( f1 ) , ( f2 ) )  ) , ( f3 ) )  ) ;

}

/* SPECIALIZED CODE END */
