/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test C23 basic features

// Boolean type and literals
  bool test_bool_literal ( ) {
 run_obj_t test_bool_literal_step ( run_obj_t self_void , run_obj_t test_bool_literal_arg_void );
  return ((bool) run_step ( (run_obj_t)program_step , (run_obj_t)test_bool_literal_step , 0 )) ;
}


// nullptr literal
  int * test_nullptr ( ) {
 run_obj_t test_nullptr_step ( run_obj_t self_void , run_obj_t test_nullptr_arg_void );
  return ((int *) run_step ( (run_obj_t)program_step , (run_obj_t)test_nullptr_step , 0 )) ;
}


// static_assert with message
   static_assert ( sizeof ( int ) >= 4 , "int must be at least 4 bytes" ) ;


// static_assert without message (C23)
  static_assert ( sizeof ( char ) == 1  ) ;


// thread_local storage class
    thread_local int tls_var = 42 ;


  int test_thread_local ( ) {
 run_obj_t test_thread_local_step ( run_obj_t self_void , run_obj_t test_thread_local_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_thread_local_step , 0 )) ;
}


// constexpr (C23)
    constexpr int CONSTANT = 100 ;


  int test_constexpr ( ) {
 run_obj_t test_constexpr_step ( run_obj_t self_void , run_obj_t test_constexpr_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_constexpr_step , 0 )) ;
}


// alignof (alignas tested separately after parser fix)
  int test_alignof ( ) {
 run_obj_t test_alignof_step ( run_obj_t self_void , run_obj_t test_alignof_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_alignof_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_bool_literal_step ( run_obj_t self_void , run_obj_t test_bool_literal_arg_void ) { 
  run_cc_start_test_bool_literal_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     bool a = true ; 
     bool b = false ; 
     return ( run_obj_t ) (  run_cc_and ( ( a ) , (  run_bool_not ( b )  ) )  ) ;

}
 run_obj_t test_nullptr_step ( run_obj_t self_void , run_obj_t test_nullptr_arg_void ) { 
  run_cc_start_test_nullptr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int * p = nullptr ; 
   return ( run_obj_t ) ( p ) ;

}
 run_obj_t test_thread_local_step ( run_obj_t self_void , run_obj_t test_thread_local_arg_void ) { 
  run_cc_start_test_thread_local_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   return ( run_obj_t ) ( tls_var ) ;

}
 run_obj_t test_constexpr_step ( run_obj_t self_void , run_obj_t test_constexpr_arg_void ) { 
  run_cc_start_test_constexpr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

      constexpr int local_const = 50 ; 
     return ( run_obj_t ) (  nat_add ( ( CONSTANT ) , ( local_const ) )  ) ;

}
 run_obj_t test_alignof_step ( run_obj_t self_void , run_obj_t test_alignof_arg_void ) { 
  run_cc_start_test_alignof_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int alignment = alignof ( double ) ; 
   return ( run_obj_t ) ( alignment ) ;

}

/* SPECIALIZED CODE END */
