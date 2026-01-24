/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
/* Complex declarator edge cases */

 int ( * ( * f ) ( int ) ) [ 10 ] ;

 int * ( * p ) [ 10 ] ;

 int ( * g ( int ) ) ( int ) ;


  typedef int INT ;

  typedef INT MYINT ;

 MYINT x ;


        typedef struct { int x ; int y ; } Point ;

 Point origin ;

