/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test function pointer declarations
     int add ( int a , int b ) {
 run_obj_t add_step ( run_obj_t self_void , run_obj_t add_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)add_step , (run_obj_t)args )) ;
}

     int sub ( int a , int b ) {
 run_obj_t sub_step ( run_obj_t self_void , run_obj_t sub_arg_void );
  run_obj_t args[] = { (run_obj_t)(a) , (run_obj_t)(b) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)sub_step , (run_obj_t)args )) ;
}


  int test_func_ptr ( ) {
 run_obj_t test_func_ptr_step ( run_obj_t self_void , run_obj_t test_func_ptr_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_func_ptr_step , 0 )) ;
}


        int apply ( int ( * op ) ( int , int ) , int x , int y ) {
 run_obj_t ( * op )_step ( run_obj_t self_void , run_obj_t ( * op )_arg_void );
  run_obj_t args[] = { (run_obj_t)(op) , (run_obj_t)(x) , (run_obj_t)(y) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)( * op )_step , (run_obj_t)args )) ;
}


  int test_func_ptr_param ( ) {
 run_obj_t test_func_ptr_param_step ( run_obj_t self_void , run_obj_t test_func_ptr_param_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_func_ptr_param_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t add_step ( run_obj_t self_void , run_obj_t add_arg_void ) { 
  run_cc_start_add_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)add_arg_void)[0];
  __auto_type b = ((run_obj_t*)add_arg_void)[1];
    return ( run_obj_t ) (  nat_add ( ( a ) , ( b ) )  ) ;
 }
 run_obj_t sub_step ( run_obj_t self_void , run_obj_t sub_arg_void ) { 
  run_cc_start_sub_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type a = ((run_obj_t*)sub_arg_void)[0];
  __auto_type b = ((run_obj_t*)sub_arg_void)[1];
    return ( run_obj_t ) (  run_cc_sub ( ( a ) , ( b ) )  ) ;
 }
 run_obj_t test_func_ptr_step ( run_obj_t self_void , run_obj_t test_func_ptr_arg_void ) { 
  run_cc_start_test_func_ptr_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

    int ( * fp ) ( int , int ) ; 
    fp = add ; 
      int r1 = fp ( 10 , 5 ) ; 
    fp = sub ; 
      int r2 = fp ( 10 , 5 ) ; 
     return ( run_obj_t ) (  nat_add ( ( r1 ) , ( r2 ) )  ) ;

}
 run_obj_t ( * op )_step ( run_obj_t self_void , run_obj_t ( * op )_arg_void ) { 
  run_cc_start_( * op )_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type op = ((run_obj_t*)( * op )_arg_void)[0];
  __auto_type x = ((run_obj_t*)( * op )_arg_void)[1];
  __auto_type y = ((run_obj_t*)( * op )_arg_void)[2];

    return ( run_obj_t ) ( op ( x , y ) ) ;

}
 run_obj_t test_func_ptr_param_step ( run_obj_t self_void , run_obj_t test_func_ptr_param_arg_void ) { 
  run_cc_start_test_func_ptr_param_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

         return ( run_obj_t ) (  nat_add ( ( apply ( add , 3 , 4 ) ) , ( apply ( sub , 7 , 2 ) ) )  ) ;

}

/* SPECIALIZED CODE END */
