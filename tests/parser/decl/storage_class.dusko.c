/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test storage class specifiers
    static int static_var = 10 ;

  extern int extern_var ;


   static int static_func ( ) {
 run_obj_t static_func_step ( run_obj_t self_void , run_obj_t static_func_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)static_func_step , 0 )) ;
}


  int test_auto ( ) {
 run_obj_t test_auto_step ( run_obj_t self_void , run_obj_t test_auto_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_auto_step , 0 )) ;
}


  int test_static_local ( ) {
 run_obj_t test_static_local_step ( run_obj_t self_void , run_obj_t test_static_local_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_static_local_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t static_func_step ( run_obj_t self_void , run_obj_t static_func_arg_void ) { 
  run_cc_start_static_func_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   return ( run_obj_t ) ( static_var ) ;

}
 run_obj_t test_auto_step ( run_obj_t self_void , run_obj_t test_auto_arg_void ) { 
  run_cc_start_test_auto_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      auto int a = 1 ; 
      register int b = 2 ; 
     return ( run_obj_t ) (  nat_add ( ( a ) , ( b ) )  ) ;

}
 run_obj_t test_static_local_step ( run_obj_t self_void , run_obj_t test_static_local_arg_void ) { 
  run_cc_start_test_static_local_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      static int counter = 0 ; 
  counter ++ ; 
   return ( run_obj_t ) ( counter ) ;

}

/* SPECIALIZED CODE END */
