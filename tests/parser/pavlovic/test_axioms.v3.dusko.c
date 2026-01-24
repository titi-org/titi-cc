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

   if (  ! cond  )  
    {    printf ( "Assertion failed: %s\n" , ( const char * ) msg ) ; 
    exit (  nat_from_int ( 1 )  ) ; 
   }
  return (run_obj_t)0;
}
 run_obj_t f_step ( run_obj_t self_void , run_obj_t f_arg_void ) { 
  run_cc_start_f_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = f_arg_void;
    return ( run_obj_t ) (  nat_succ ( x )  ) ;
 }
 run_obj_t g_step ( run_obj_t self_void , run_obj_t g_arg_void ) { 
  run_cc_start_g_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type x = g_arg_void;
    return ( run_obj_t ) (  nat_mult ( x ,  nat_from_int ( 2 )  )  ) ;
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
        RUN_ASSERT (  run_iseq ( x , x )  , "compute(x) == x" ) ; 
        RUN_ASSERT (  run_iseq ( x , x )  , "data(x) == x" ) ; 
        RUN_ASSERT (  run_iseq ( x , x )  , "identity(x) == x" ) ; 
        RUN_ASSERT (  run_iseq ( x , x )  , "unit(x) == x" ) ; 

  /* Structure axioms */
           RUN_ASSERT (  run_iseq ( x , x )  , "swap(x, y) == x" ) ; 

        RUN_ASSERT (  run_iseq ( x , x )  , "copy(x) == x" ) ; 

        RUN_ASSERT (  run_iseq ( 0 ,  nat_from_int ( 0 )  )  , "delete(x) == 0" ) ; 

  /* Process axioms */
        RUN_ASSERT (  run_iseq ( x , x )  , "function(x) == x" ) ; 
           RUN_ASSERT (  run_iseq ( x , x )  , "process(x, y) == x" ) ; 

  /* Composition */
              RUN_ASSERT (  run_iseq ( x , x )  , "sequential(g, f, x) == x" ) ; 

  /* Parallel */
       struct run_cc_pair p = { a , c } ; 
               run_obj_t res = parallel ( f , g , & p ,  nat_from_int ( 1 )  ) ; 
  ( void ) res ; 

  /* Partial */
           RUN_ASSERT (  run_iseq ( 0 ,  nat_from_int ( 0 )  )  , "partial(f, y) == 0" ) ; 

  /* Fixpoint */
        RUN_ASSERT (  run_iseq ( 0 ,  nat_from_int ( 0 )  )  , "fixpoint(e) == 0" ) ; 

  /* Kleene */
  /* run_obj_t gres = kleene(g, y); */
  /* (void)gres; */

  /* Eval / Run */
     
     
             

  /* Variadic identity/idempotent */
     
    
             
     
             
     
             

  /* Equality and Decidability */
    
      

  /* rho(x) == x if x is a boolean projection (true or false) */
   
             

   return ( run_obj_t ) (  nat_from_int ( 0 )  ) ;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

     run_obj_t dummy =  nat_from_int ( 1 )  ; 
     test_axioms ( dummy , dummy , dummy , dummy ) ; 
   return ( run_obj_t ) (  nat_from_int ( 0 )  ) ;

}

/* SPECIALIZED CODE END */
