/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */




      void RUN_ASSERT ( int cond , const char * msg ) {
 run_obj_t RUN_ASSERT_step ( run_obj_t self_void , run_obj_t RUN_ASSERT_arg_void );
  run_obj_t args[] = { (run_obj_t)(cond) , (run_obj_t)(msg) };
  (void) run_step ( (run_obj_t)program_step , (run_obj_t)RUN_ASSERT_step , (run_obj_t)args );
}


   run_obj_t f ( run_obj_t x ) {
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void );
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)f_step , (run_obj_t)(x) )) ;
}

   run_obj_t g ( run_obj_t x ) {
 run_obj_t g_step ( run_obj_t self_void , run_obj_t g_arg_void );
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)g_step , (run_obj_t)(x) )) ;
}

   run_obj_t e ( run_obj_t x ) {
 run_obj_t e_step ( run_obj_t self_void , run_obj_t e_arg_void );
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)e_step , (run_obj_t)(x) )) ;
}


/* Test functions to check properties */
         run_obj_t test_axioms ( run_obj_t x , run_obj_t y , run_obj_t a , run_obj_t c ) {
 run_obj_t test_axioms_step ( run_obj_t self_void , run_obj_t test_axioms_arg_void );
  run_obj_t args[] = { (run_obj_t)(x) , (run_obj_t)(y) , (run_obj_t)(a) , (run_obj_t)(c) };
  return ((run_obj_t) run_step ( (run_obj_t)program_step , (run_obj_t)test_axioms_step , (run_obj_t)args )) ;
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

   if (  run_bool_not ( cond )  )  
    {    printf ( "Assertion failed: %s\n" , ( const char * ) msg ) ; 
    exit ( 1 ) ; 
   }
  return (run_obj_t)0;
}
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void ) { 
  run_cc_start_f_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = f_arg_void;
    return ( run_obj_t ) (  nat_add ( ( x ) , ( 1 ) )  ) ;
 }
 run_obj_t g_step ( run_obj_t self_void , run_obj_t g_arg_void ) { 
  run_cc_start_g_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = g_arg_void;
    return ( run_obj_t ) (  nat_mult ( ( x ) , ( 2 ) )  ) ;
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
     RUN_ASSERT (  run_iseq ( ( compute ( x ) ) , ( x ) )  , "compute(x) == x" ) ; 
     RUN_ASSERT (  run_iseq ( ( data ( x ) ) , ( x ) )  , "data(x) == x" ) ; 
        RUN_ASSERT (  run_iseq ( ( x ) , ( x ) )  , "identity(x) == x" ) ; 

  /* Structure axioms */
           RUN_ASSERT (  run_iseq ( ( run_data_va ( 2 , y , x ) ) , ( x ) )  , "swap(x, y) == x" ) ; 

        RUN_ASSERT (  run_iseq ( ( run_data_va ( 2 , x , x ) ) , ( x ) )  , "copy(x) == x" ) ; 

        RUN_ASSERT (  run_iseq ( ( 0 ) , ( 0 ) )  , "delete(x) == 0" ) ; 

  /* Process axioms */
     RUN_ASSERT (  run_iseq ( ( function ( x ) ) , ( x ) )  , "function(x) == x" ) ; 
      RUN_ASSERT (  run_iseq ( ( process ( x , y ) ) , ( x ) )  , "process(x, y) == x" ) ; 

  /* Composition */
              RUN_ASSERT (  run_iseq ( ( eval ( f , eval ( g , x ) ) ) , ( x ) )  , "sequential(g, f, x) == x" ) ; 

  /* Parallel */
       struct run_cc_pair p = { a , c } ; 
               run_obj_t res = parallel ( f , g , & p , 1 ) ; 
  ( void ) res ; 

  /* Partial - now returns a closure, not 0 */
           run_obj_t partial_closure = partial ( f , y ) ; 
     RUN_ASSERT (  run_bool_not (  run_iseq ( ( partial_closure ) , ( 0 ) )  )  , "partial(f, y) creates a closure" ) ; 
       struct run_cc_pair partial_args = { y , a } ; 
      run_obj_t expected_partial = eval ( f ,  nat_to_int ( & partial_args )  ) ; 
      run_obj_t evaluated_partial = eval ( partial_closure , a ) ; 
  
       
      RUN_ASSERT ( bool_value ( iseq ( expected_partial , evaluated_partial ) ) , "eval(partial(f, y), a) == eval(f, pair(y, a))" ) ; 

  /* Fixpoint */
     RUN_ASSERT (  run_iseq ( ( fixpoint ( e ) ) , ( 0 ) )  , "fixpoint(e) == 0" ) ; 

  /* Kleene */
  /* run_obj_t gres = kleene(g, y); */
  /* (void)gres; */

  /* Eval / Run */
     RUN_ASSERT ( bool_value ( iseq ( eval ( f , x ) , f ( x ) ) ) , "eval(f, x) == f(x)" ) ; 
            
             RUN_ASSERT ( bool_value ( iseq ( run ( program , f , x ) , f ( x ) ) ) , "run(program, f, x) == f(x)" ) ; 

  /* Variadic identity/idempotent */
          RUN_ASSERT ( bool_value ( iseq ( eval ( data ( f ) , x ) , f ( x ) ) ) , "identity(f, x) == f(x)" ) ; 
    
             RUN_ASSERT ( bool_value ( iseq ( idempotent ( f , x ) , f ( x ) ) ) , "idempotent(f, x) == f(x)" ) ; 
            
             RUN_ASSERT ( bool_value ( iseq ( eval ( data ( f ) , eval ( data ( g ) , x ) ) , f ( g ( x ) ) ) ) , "identity(f, g, x) == f(g(x))" ) ; 
     
             RUN_ASSERT ( bool_value ( iseq ( idempotent ( f , g , 1 ) , f ( g ( 1 ) ) ) ) , "idempotent(f, g, 1) == f(g(1))" ) ; 

  /* Equality and Decidability */
    RUN_ASSERT ( bool_value ( iseq ( x , x ) ) , "iseq(x, x) == true" ) ; 
      RUN_ASSERT (  run_bool_not ( bool_value ( iseq ( x ,  nat_add ( ( x ) , ( 1 ) )  ) ) )  , "iseq(x, x+1) == false" ) ; 

  /* rho(x) == x if x is a boolean projection (true or false) */
   
             RUN_ASSERT ( bool_value ( iseq ( rho ( RUN_BOOL_TRUE ) , RUN_BOOL_TRUE ) ) , "rho(true) == true" ) ; 

  /* Arithmetic correctness with identity embedding */
     RUN_ASSERT ( bool_value ( iseq ( nat_add ( 1 , 2 ) , 3 ) ) , "nat_add(1, 2) == 3" ) ; 
     RUN_ASSERT ( bool_value ( iseq ( nat_mult ( 2 , 3 ) , 6 ) ) , "nat_mult(2, 3) == 6" ) ; 

  printf ( "✓ All axioms passed successfully\n" ) ; 

   return ( run_obj_t ) ( 0 ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     run_obj_t dummy = 1 ; 
     test_axioms ( dummy , dummy , dummy , dummy ) ; 
   return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
