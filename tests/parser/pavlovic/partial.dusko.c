/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
// Test partial morphism


// Define a function that takes two arguments
     void * f ( void * x , void * y ) {
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) };
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)f_step , (run_obj_t)args )) ;
}


   void * test_partial ( void * y ) {
 run_obj_t test_partial_step ( run_obj_t self_void , run_obj_t test_partial_arg_void );
  return ((void *) run_step ( (run_obj_t)program_step , (run_obj_t)test_partial_step , (run_obj_t)(y) )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void ) { 
  run_cc_start_f_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)f_arg_void)[0];
  __auto_type y = ((run_obj_t*)f_arg_void)[1];
   return ( run_obj_t ) ( nat_add ( x , y ) ) ;
 }
 run_obj_t test_partial_step ( run_obj_t self_void , run_obj_t test_partial_arg_void ) { 
  run_cc_start_test_partial_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type y = test_partial_arg_void;

  // partial(f, y) should return a function g such that g(z) = f(y, z)
  // In this case, f(y, z) = y + z
  // So we are creating a function that adds y to its argument
         return ( run_obj_t ) ( partial ( f , y ) ) ;

}

/* SPECIALIZED CODE END */
