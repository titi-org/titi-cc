/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */


// Test switch statement
    const char * get_day_name ( int day ) {
 run_obj_t get_day_name_step ( run_obj_t self_void , run_obj_t get_day_name_arg_void );
  return ((const char *) run_step ( (run_obj_t)program_step , (run_obj_t)get_day_name_step , (run_obj_t)(day) )) ;
}


   int classify_number ( int n ) {
 run_obj_t classify_number_step ( run_obj_t self_void , run_obj_t classify_number_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)classify_number_step , (run_obj_t)(n) )) ;
}


  int main ( ) {
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void );
  return ((int) run_step ( (run_obj_t)program_step , (run_obj_t)main_step , 0 )) ;
}


/* SPECIALIZED CODE START */
 run_obj_t get_day_name_step ( run_obj_t self_void , run_obj_t get_day_name_arg_void ) { 
  run_cc_start_get_day_name_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type day = get_day_name_arg_void;

   switch ( day )  
  {  case 1 : 
     return ( run_obj_t ) ( "Monday" ) ;

   case 2 : 
     return ( run_obj_t ) ( "Tuesday" ) ;

   case 3 : 
     return ( run_obj_t ) ( "Wednesday" ) ;

   case 4 : 
     return ( run_obj_t ) ( "Thursday" ) ;

   case 5 : 
     return ( run_obj_t ) ( "Friday" ) ;

   case 6 : 
     return ( run_obj_t ) ( "Saturday" ) ;

   case 7 : 
     return ( run_obj_t ) ( "Sunday" ) ;

  default : 
     return ( run_obj_t ) ( "Invalid" ) ;

   }
}
 run_obj_t classify_number_step ( run_obj_t self_void , run_obj_t classify_number_arg_void ) { 
  run_cc_start_classify_number_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;
  __auto_type n = classify_number_arg_void;

   switch ( n )  
  {  case 0 : 
     return ( run_obj_t ) ( 0 ) ;

   case 1 : 
   case 2 : 
   case 3 : 
     return ( run_obj_t ) ( 1 ) ;

  default : 
     return ( run_obj_t ) ( 2 ) ;

   }
}
 run_obj_t main_step ( run_obj_t self_void , run_obj_t main_arg_void ) { 
  run_cc_start_main_step: ;
  run_obj_t (*self)(run_obj_t, run_obj_t) = (run_obj_t(*)(run_obj_t, run_obj_t))self_void;

   printf ( "Day 1: %s\n" , get_day_name ( 1 ) ) ; 
   printf ( "Day 7: %s\n" , get_day_name ( 7 ) ) ; 
   printf ( "Day 99: %s\n" , get_day_name ( 99 ) ) ; 
   printf ( "Classify 0: %d\n" , classify_number ( 0 ) ) ; 
   printf ( "Classify 2: %d\n" , classify_number ( 2 ) ) ; 
   printf ( "Classify 5: %d\n" , classify_number ( 5 ) ) ; 
   return ( run_obj_t ) ( 0 ) ;

}

/* SPECIALIZED CODE END */
