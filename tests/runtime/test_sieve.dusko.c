/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
     extern int printf ( const char * fmt , ... ) ;



       int is_divisible_recursive ( long long n , long long divisor ) {
 run_obj_t is_divisible_recursive_step ( run_obj_t self_void , run_obj_t is_divisible_recursive_arg_void );
  run_obj_t args[] = { (run_obj_t)(n) , (run_obj_t)(divisor) };
  return ((int) run_step ( (run_obj_t)kleene_step , (run_obj_t)is_divisible_recursive_step , (run_obj_t)args )) ;
}


           long long find_nth_prime ( long long n , long long current , long long count ) {
 run_obj_t find_nth_prime_step ( run_obj_t self_void , run_obj_t find_nth_prime_arg_void );
  run_obj_t args[] = { (run_obj_t)(n) , (run_obj_t)(current) , (run_obj_t)(count) };
  return ((long long) run_step ( (run_obj_t)kleene_step , (run_obj_t)find_nth_prime_step , (run_obj_t)args )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t is_divisible_recursive_step ( run_obj_t self_void , run_obj_t is_divisible_recursive_arg_void ) { 
  run_cc_start_is_divisible_recursive_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type n = ((run_obj_t*)is_divisible_recursive_arg_void)[0];
  __auto_type divisor = ((run_obj_t*)is_divisible_recursive_arg_void)[1];

         if (   divisor * divisor  > n  )   return ( run_obj_t ) ( ( 0 ) ) ;

         if (   n % divisor  == ( 0 )  )   return ( run_obj_t ) ( ( 1 ) ) ;

          run_cc_tco_args[0] = (run_obj_t)( n  );
  run_cc_tco_args[1] = (run_obj_t)( divisor + ( 1 )  );
  is_divisible_recursive_arg_void = (run_obj_t)run_cc_tco_args;
  goto run_cc_start_is_divisible_recursive_step;

}
 run_obj_t find_nth_prime_step ( run_obj_t self_void , run_obj_t find_nth_prime_arg_void ) { 
  run_cc_start_find_nth_prime_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  run_obj_t run_cc_tco_args[64];
  __auto_type n = ((run_obj_t*)find_nth_prime_arg_void)[0];
  __auto_type current = ((run_obj_t*)find_nth_prime_arg_void)[1];
  __auto_type count = ((run_obj_t*)find_nth_prime_arg_void)[2];

       if (  count == n  )     return ( run_obj_t ) (  current - ( 1 )  ) ;

    
      if (  ! is_divisible_recursive ( current , ( 2 ) )  )  
         {          run_cc_tco_args[0] = (run_obj_t)( n  );
  run_cc_tco_args[1] = (run_obj_t)( current + ( 1 )   );
  run_cc_tco_args[2] = (run_obj_t)( count + ( 1 )  );
  find_nth_prime_arg_void = (run_obj_t)run_cc_tco_args;
  goto run_cc_start_find_nth_prime_step;

     }
    
           run_cc_tco_args[0] = (run_obj_t)( n  );
  run_cc_tco_args[1] = (run_obj_t)( current + ( 1 )   );
  run_cc_tco_args[2] = (run_obj_t)( count );
  find_nth_prime_arg_void = (run_obj_t)run_cc_tco_args;
  goto run_cc_start_find_nth_prime_step;

}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

        long long n1 = ( 65536 ) ;  // 2^16
        printf ( "%lldth prime: %lld\n" , n1 , find_nth_prime ( n1 , ( 2 ) , ( 0 ) ) ) ; 

        long long n2 = ( 131072 ) ;  // 2^17
        printf ( "%lldth prime: %lld\n" , n2 , find_nth_prime ( n2 , ( 2 ) , ( 0 ) ) ) ; 

        long long n3 = ( 262144 ) ;  // 2^18
        printf ( "%lldth prime: %lld\n" , n3 , find_nth_prime ( n3 , ( 2 ) , ( 0 ) ) ) ; 
     return ( run_obj_t ) ( ( 0 ) ) ;

}

/* SPECIALIZED CODE END */
