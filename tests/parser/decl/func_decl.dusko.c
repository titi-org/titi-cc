/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test function declarations
    int simple_func ( int a , int b ) ;

 void no_return ( void ) ;

    int varargs_func ( const char * fmt , ... ) ;


     int simple_func ( int a , int b ) {
 run_obj_t simple_func_step ( run_obj_t self_void , run_obj_t simple_func_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)simple_func_step , (run_obj_t)args )) ;
}


  void no_return ( void ) {
 run_obj_t no_return_step ( run_obj_t self_void , run_obj_t no_return_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)no_return_step , 0 );
}


     static inline int inline_func ( int x ) {
 run_obj_t inline_func_step ( run_obj_t self_void , run_obj_t inline_func_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)inline_func_step , (run_obj_t)(x) )) ;
}


  int test_func_decls ( ) {
 run_obj_t test_func_decls_step ( run_obj_t self_void , run_obj_t test_func_decls_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_func_decls_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t simple_func_step ( run_obj_t self_void , run_obj_t simple_func_arg_void ) { 
  run_cc_start_simple_func_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)simple_func_arg_void)[0];
  __auto_type b = ((run_obj_t*)simple_func_arg_void)[1];

     return ( run_obj_t ) (  nat_add ( ( a ) , ( b ) )  ) ;

}
 run_obj_t no_return_step ( run_obj_t self_void , run_obj_t no_return_arg_void ) { 
  run_cc_start_no_return_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  return;

  return (run_obj_t)0;
}
 run_obj_t inline_func_step ( run_obj_t self_void , run_obj_t inline_func_arg_void ) { 
  run_cc_start_inline_func_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = inline_func_arg_void;

     return ( run_obj_t ) (  nat_mult ( ( x ) , ( 2 ) )  ) ;

}
 run_obj_t test_func_decls_step ( run_obj_t self_void , run_obj_t test_func_decls_arg_void ) { 
  run_cc_start_test_func_decls_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      return ( run_obj_t ) (  nat_add ( ( simple_func ( 1 , 2 ) ) , ( inline_func ( 3 ) ) )  ) ;

}

/* SPECIALIZED CODE END */
