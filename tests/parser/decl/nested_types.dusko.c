parser/decl/nested_types.c:11: error: syntax error at '}'
parser/decl/nested_types.c:11: error: syntax error at '}'
/* PREAMBLE START */
#define __RUN_CC__ 1
#include "run_runtime.h"
/* PREAMBLE END */
/* Nested type definitions edge cases */

  
      
          
             
         
     
 struct A { struct B { struct C { int x ; } c ; } b ; } a ;


  

      enum E { ... } ;

