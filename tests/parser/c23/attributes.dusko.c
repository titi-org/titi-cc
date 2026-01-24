/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
// Test C23 attributes [[ ]]

// nodiscard attribute
   [[ nodiscard  ]] int must_check ( ) {
[[ nodiscard  ]] run_obj_t must_check_step ( run_obj_t self_void , run_obj_t must_check_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)must_check_step , 0 )) ;
}


// deprecated attribute
   [[ deprecated  ]] int old_function ( ) {
[[ deprecated  ]] run_obj_t old_function_step ( run_obj_t self_void , run_obj_t old_function_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)old_function_step , 0 )) ;
}


// maybe_unused attribute
     [[ maybe_unused  ]] static int unused_var = 10 ;


// noreturn attribute
   [[ noreturn  ]] void abort_program ( ) {
[[ noreturn  ]] run_obj_t abort_program_step ( run_obj_t self_void , run_obj_t abort_program_arg_void );
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)abort_program_step , 0 );
}


// Multiple attributes
    [[ nodiscard  , deprecated ( "use new_api instead" ) ]] int legacy_api ( ) {
[[ nodiscard  , deprecated ( "use new_api instead" ) ]] run_obj_t legacy_api_step ( run_obj_t self_void , run_obj_t legacy_api_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)legacy_api_step , 0 )) ;
}


// Scoped attribute (gnu::pure - not using const as it's a keyword)
    [[ gnu :: pure  ]] int pure_function ( int x ) {
[[ gnu :: pure  ]] run_obj_t pure_function_step ( run_obj_t self_void , run_obj_t pure_function_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)pure_function_step , (run_obj_t)(x) )) ;
}


/* SPECIALIZED CODE START */
[[ nodiscard  ]] run_obj_t must_check_step ( run_obj_t self_void , run_obj_t must_check_arg_void ) { 
  run_cc_start_must_check_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   return ( run_obj_t ) ( 42 ) ;

}
[[ deprecated  ]] run_obj_t old_function_step ( run_obj_t self_void , run_obj_t old_function_arg_void ) { 
  run_cc_start_old_function_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   return ( run_obj_t ) ( 0 ) ;

}
[[ noreturn  ]] run_obj_t abort_program_step ( run_obj_t self_void , run_obj_t abort_program_arg_void ) { 
  run_cc_start_abort_program_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   while ( 1 ) 
    ; 
  return (run_obj_t)0;
}
[[ nodiscard  , deprecated ( "use new_api instead" ) ]] run_obj_t legacy_api_step ( run_obj_t self_void , run_obj_t legacy_api_arg_void ) { 
  run_cc_start_legacy_api_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   return ( run_obj_t ) (  - 1  ) ;

}
[[ gnu :: pure  ]] run_obj_t pure_function_step ( run_obj_t self_void , run_obj_t pure_function_arg_void ) { 
  run_cc_start_pure_function_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = pure_function_arg_void;

     return ( run_obj_t ) (  nat_mult ( ( x ) , ( 2 ) )  ) ;

}

/* SPECIALIZED CODE END */
