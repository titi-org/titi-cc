/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */


// Test struct and union definitions
  
   
   
struct Point { long x ; long y ; } ;


  
   
   
union Data { long i ; double d ; } ;


      struct Point make_point ( long x , long y ) { 
    struct Point p ; 
    p . x = x ; 
    p . y = y ; 
   return p ;

 }


    long point_distance_squared ( struct Point p ) {         return  nat_add ( (  nat_mult ( ( p . x ) , ( p . x ) )  ) , (  nat_mult ( ( p . y ) , ( p . y ) )  ) )  ;
  }


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

       struct Point p1 = make_point ( 3 , 4 ) ; 
    printf ( "Point: (%ld, %ld)\n" ,  nat_to_int ( p1 . x )  ,  nat_to_int ( p1 . y )  ) ; 
   printf ( "Distance squared: %ld\n" ,  nat_to_int ( point_distance_squared ( p1 ) )  ) ; 

    union Data d ; 
    d . i = 42 ; 
   printf ( "Union int: %ld\n" ,  nat_to_int ( d . i )  ) ; 

   return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
