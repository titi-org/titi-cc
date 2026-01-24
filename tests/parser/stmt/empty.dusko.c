/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test empty and expression statements
  int test_empty ( ) {
 run_obj_t test_empty_step ( run_obj_t self_void , run_obj_t test_empty_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_empty_step , 0 )) ;
}


  int test_expr_stmt ( ) {
 run_obj_t test_expr_stmt_step ( run_obj_t self_void , run_obj_t test_expr_stmt_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_expr_stmt_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t test_empty_step ( run_obj_t self_void , run_obj_t test_empty_arg_void ) { 
  run_cc_start_test_empty_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

  ; 
  ; 
  ; 
   return ( run_obj_t ) ( 0 ) ;

}
 run_obj_t test_expr_stmt_step ( run_obj_t self_void , run_obj_t test_expr_stmt_arg_void ) { 
  run_cc_start_test_expr_stmt_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     int a = 5 ; 
  a ; 
     nat_add ( ( a ) , ( 1 ) )  ; 
  a ++ ; 
  ++ a ; 
   return ( run_obj_t ) ( a ) ;

}

/* SPECIALIZED CODE END */
