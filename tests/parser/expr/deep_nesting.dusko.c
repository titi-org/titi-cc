/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
/* Deep nesting edge cases */

   int deep_parens = ( ( ( ( ( ( ( ( ( ( 1 ) ) ) ) ) ) ) ) ) ) ;

                   int deep_ternary = (( 1 ) ? ( (( 2 ) ? ( (( 3 ) ? ( (( 4 ) ? ( 5 ) : ( 6 )) ) : ( 7 )) ) : ( 8 )) ) : ( 9 )) ;

   int cast_chain =  nat_to_int (  nat_to_int ( ( short ) ( char ) 42 )  )  ;

                   int mixed_ops =  run_cc_sub ( (  nat_add ( ( 1 ) , (  run_cc_div ( (  nat_mult ( ( 2 ) , ( 3 ) )  ) , ( 4 ) )  ) )  ) , (  run_cc_mod ( ( 5 ) , ( 6 ) )  ) )  & 7 | 8 ^ 9 ;

