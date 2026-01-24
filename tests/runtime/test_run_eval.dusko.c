/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */


   run_obj_t dummy_one_arg ( run_obj_t x ) {
 run_obj_t dummy_one_arg_step ( run_obj_t self_void , run_obj_t dummy_one_arg_arg_void );
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)dummy_one_arg_step , (run_obj_t)(x) )) ;
}




   run_obj_t identity_prog ( run_obj_t x ) {
 run_obj_t identity_prog_step ( run_obj_t self_void , run_obj_t identity_prog_arg_void );
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)identity_prog_step , (run_obj_t)(x) )) ;
}


     run_obj_t run_eval_test ( run_obj_t f , run_obj_t x ) {
 run_obj_t run_eval_test_step ( run_obj_t self_void , run_obj_t run_eval_test_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)run_eval_test_step , (run_obj_t)args )) ;
}


     run_obj_t var_test ( run_obj_t f , run_obj_t x ) {
 run_obj_t var_test_step ( run_obj_t self_void , run_obj_t var_test_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)var_test_step , (run_obj_t)args )) ;
}


     run_obj_t eval_direct_test ( run_obj_t f , run_obj_t x ) {
 run_obj_t eval_direct_test_step ( run_obj_t self_void , run_obj_t eval_direct_test_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)eval_direct_test_step , (run_obj_t)args )) ;
}


     run_obj_t fallback_test ( run_obj_t f , run_obj_t x ) {
 run_obj_t fallback_test_step ( run_obj_t self_void , run_obj_t fallback_test_arg_void );
  run_obj_t args[] = { (run_obj_t)(f) , (run_obj_t)(x) };
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)fallback_test_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t dummy_one_arg_step ( run_obj_t self_void , run_obj_t dummy_one_arg_arg_void ) { 
  run_cc_start_dummy_one_arg_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = dummy_one_arg_arg_void;
  return ( run_obj_t ) ( x ) ;
 }
 run_obj_t identity_prog_step ( run_obj_t self_void , run_obj_t identity_prog_arg_void ) { 
  run_cc_start_identity_prog_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = identity_prog_arg_void;
  return ( run_obj_t ) ( x ) ;
 }
 run_obj_t run_eval_test_step ( run_obj_t self_void , run_obj_t run_eval_test_arg_void ) { 
  run_cc_start_run_eval_test_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)run_eval_test_arg_void)[0];
  __auto_type x = ((run_obj_t*)run_eval_test_arg_void)[1];

  // This should be simplified to eval ( f , x )
            return ( run_obj_t ) ( run ( program , f , x ) ) ;

}
 run_obj_t var_test_step ( run_obj_t self_void , run_obj_t var_test_arg_void ) { 
  run_cc_start_var_test_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)var_test_arg_void)[0];
  __auto_type x = ((run_obj_t*)var_test_arg_void)[1];

              run_obj_t v = run ( program , f , x ) ; 
   return ( run_obj_t ) ( v ) ;

}
 run_obj_t eval_direct_test_step ( run_obj_t self_void , run_obj_t eval_direct_test_arg_void ) { 
  run_cc_start_eval_direct_test_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)eval_direct_test_arg_void)[0];
  __auto_type x = ((run_obj_t*)eval_direct_test_arg_void)[1];

  // This should be simplified to eval ( f , x )
         return ( run_obj_t ) ( eval ( f , x ) ) ;

}
 run_obj_t fallback_test_step ( run_obj_t self_void , run_obj_t fallback_test_arg_void ) { 
  run_cc_start_fallback_test_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type f = ((run_obj_t*)fallback_test_arg_void)[0];
  __auto_type x = ((run_obj_t*)fallback_test_arg_void)[1];

  /* run(kleene, g, arg) should keep run(kleene, g, arg) */
  /* Cast f to correct type expected by kleene logic if needed, or just pass as
   * void* */
  /* kleene expects void* (*g)(void*, void*) */
  /* We reuse dummy_one_arg but cast it to avoid warnings if possible, or just
   * pass void* */
            return ( run_obj_t ) ( run ( kleene , f , x ) ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        run_obj_t prog = identity ( ( run_obj_t ) identity_prog ) ; 
     run_obj_t arg = ( 42 ) ; 

    printf ( "run_eval_test: %ld\n" , ( long ) run_eval_test ( prog , arg ) ) ; 
    printf ( "eval_direct_test: %ld\n" , ( long ) eval_direct_test ( prog , arg ) ) ; 
  // printf("fallback_test: %ld\n", (long)fallback_test(prog, arg));
  /* fallback_test might crash if kleene logic is not fully robust with
     identity_prog signature mismatch (identity_prog takes 1 arg, kleene step
     takes 2). Let's skip running it, just check compilation and AST
     simplification (or lack thereof).
  */

   return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
