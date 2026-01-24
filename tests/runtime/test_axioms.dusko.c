/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */




      void RUN_ASSERT ( int cond , const char * msg ) {
 run_obj_t RUN_ASSERT_step ( run_obj_t self_void , run_obj_t RUN_ASSERT_arg_void );
  run_obj_t args[] = { (run_obj_t)(cond) , (run_obj_t)(msg) };
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)RUN_ASSERT_step , (run_obj_t)args );
}


   int f ( int x ) {
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)f_step , (run_obj_t)(x) )) ;
}

   int g ( int x ) {
 run_obj_t g_step ( run_obj_t self_void , run_obj_t g_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)g_step , (run_obj_t)(x) )) ;
}

   int e ( int x ) {
 run_obj_t e_step ( run_obj_t self_void , run_obj_t e_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)e_step , (run_obj_t)(x) )) ;
}


/* Test functions to check properties */
         int test_axioms ( run_obj_t x , run_obj_t y , run_obj_t a , run_obj_t c ) {
 run_obj_t test_axioms_step ( run_obj_t self_void , run_obj_t test_axioms_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) , (run_obj_t)(a) , (run_obj_t)(c) };
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)test_axioms_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t RUN_ASSERT_step ( run_obj_t self_void , run_obj_t RUN_ASSERT_arg_void ) { 
  run_cc_start_RUN_ASSERT_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type cond = ((run_obj_t*)RUN_ASSERT_arg_void)[0];
  __auto_type msg = ((run_obj_t*)RUN_ASSERT_arg_void)[1];

   if (  ! cond  )  
    {    printf ( "Assertion failed: %s\n" , ( const char * ) msg ) ; 
    exit ( ( 1 ) ) ; 
   }
  return (run_obj_t)0;
}
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void ) { 
  run_cc_start_f_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = f_arg_void;
    return ( run_obj_t ) (  x + ( 1 )  ) ;
 }
 run_obj_t g_step ( run_obj_t self_void , run_obj_t g_arg_void ) { 
  run_cc_start_g_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = g_arg_void;
    return ( run_obj_t ) (  x * ( 2 )  ) ;
 }
 run_obj_t e_step ( run_obj_t self_void , run_obj_t e_arg_void ) { 
  run_cc_start_e_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = e_arg_void;
  return ( run_obj_t ) ( x ) ;
 }
 run_obj_t test_axioms_step ( run_obj_t self_void , run_obj_t test_axioms_arg_void ) { 
  run_cc_start_test_axioms_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type x = ((run_obj_t*)test_axioms_arg_void)[0];
  __auto_type y = ((run_obj_t*)test_axioms_arg_void)[1];
  __auto_type a = ((run_obj_t*)test_axioms_arg_void)[2];
  __auto_type c = ((run_obj_t*)test_axioms_arg_void)[3];

  /* Basic identity axioms */
     RUN_ASSERT (  compute ( x ) == x  , "compute(x) == x" ) ; 
     RUN_ASSERT (  data ( x ) == x  , "data(x) == x" ) ; 
     RUN_ASSERT (  identity ( x ) == x  , "identity(x) == x" ) ; 

  /* Structure axioms */
      RUN_ASSERT (  swap ( x , y ) == x  , "swap(x, y) == x" ) ; 

     RUN_ASSERT (  copy ( x ) == x  , "copy(x) == x" ) ; 

     RUN_ASSERT (  delete ( x ) == ( 0 )  , "delete(x) == 0" ) ; 

  /* Process axioms */
     RUN_ASSERT (  function ( x ) == x  , "function(x) == x" ) ; 
      RUN_ASSERT (  process ( x , y ) == x  , "process(x, y) == x" ) ; 

  /* Composition */
       RUN_ASSERT (  sequential ( g , f , x ) == x  , "sequential(g, f, x) == x" ) ; 

  /* Parallel */
  /* parallel returns run_obj_t generically */
  /* For now, just test compilation/execution of call */
       struct run_cc_pair p = { a , c } ; 
        run_obj_t res = parallel ( f , g , & p , ( 1 ) ) ; 
  ( void ) res ; 

  /* Partial - now returns a closure, not 0 */
      run_obj_t partial_closure = partial ( f , y ) ;
      RUN_ASSERT (  partial_closure != ( 0 )  , "partial(f, y) creates a closure" ) ; 

  /* Fixpoint */
     RUN_ASSERT (  fixpoint ( e ) == ( 0 )  , "fixpoint(e) == 0" ) ; 

  /* Kleene */
      run_obj_t gres = kleene ( g , y ) ; 
  ( void ) gres ; 

  /* Eval / Run */
      RUN_ASSERT (  eval ( f , x ) == ( run_obj_t ) f ( ( int ) x )  , "eval(f, x) == f(x)" ) ; 
      
             RUN_ASSERT (  run ( program , f , x ) == ( run_obj_t ) f ( ( int ) x )  , "run(program, f, x) == f(x)" ) ; 

  /* Variadic identity/idempotent */
      RUN_ASSERT (  identity ( f , x ) == ( run_obj_t ) f ( ( int ) x )  , "identity(f, x) == f(x)" ) ; 
     
             RUN_ASSERT (  idempotent ( f , x ) == ( run_obj_t ) f ( ( int ) x )  , "idempotent(f, x) == f(x)" ) ; 
      
             RUN_ASSERT (  identity ( f , g , x ) == ( run_obj_t ) f ( ( int ) g ( ( int ) x ) )  , "identity(f, g, x) == f(g(x))" ) ; 
      
             RUN_ASSERT (  idempotent ( f , g , ( run_obj_t ) ( 1 ) ) == ( run_obj_t ) f ( ( int ) g ( ( 1 ) ) )  , "idempotent(f, g, 1) == f(g(1))" ) ; 

   return ( run_obj_t ) ( ( 0 ) ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     run_obj_t dummy = ( 1 ) ; 
     test_axioms ( dummy , dummy , dummy , dummy ) ; 
   return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
