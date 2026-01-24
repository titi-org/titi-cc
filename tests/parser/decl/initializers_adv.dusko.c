parser/decl/initializers_adv.c:4: error: syntax error at '{'
parser/decl/initializers_adv.c:4: error: syntax error at '{'
/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
#include "run_bool.h"
#include "run_nat.h"
/* PREAMBLE END */
/* Advanced initializer edge cases */

          int arr [ 10 ] = { [ 5 ] 5 , [ 3 ] 3 } ;

     
                struct { int a ; int b ; } s = { . a 1 , . b 2 } ;

