/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
/* sizeof and alignof edge cases */

       struct S { int a ; double b ; } ;

         int x =  nat_add ( (  nat_add ( ( sizeof ( int ) ) , ( sizeof ( x ) ) )  ) , ( sizeof ( struct S ) ) )  ;

   int y = alignof ( double ) ;

