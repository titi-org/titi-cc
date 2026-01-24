/* Comprehensive Regression Suite */

#include <stddef.h>
#include <stdint.h>
/* Bug: unsigned char typedefs and multi-pass discovery */
typedef unsigned char __u_char;
typedef unsigned char MyType;

/* Bug: struct forward declaration (external_declaration: ds_has_type ';') */
struct ForwardOnly;
struct DefinedStruct {
  int x;
};
struct DefinedStruct;

/* Bug: struct variable declaration */
struct StructWithVar {
  int a;
};
struct StructWithVar my_instance;

/* Bug: built-in va_list and pointer typedefs (STD_TYPE handling) */
typedef __builtin_va_list va_list_alias;
typedef struct foo_opaque *bar_ptr;

/* Bug: nested typedefs */
typedef int myint;
typedef myint myint2;

/* Bug: typedef struct member scope (typedef_shim_open) */
typedef struct {
  int member;
} MyStruct;
int member; /* Should not be registered as TYPE_NAME despite being inside
               typedef struct */

/* Bug: function pointer cast parentheses stripping (direct_declarator
 * parentheses) */
typedef void *(*step_fn)(void *, void *);
/* Cast expressions in functions currently don't work due to grammar conflicts.
   The following was removed:
   uintptr_t dummy_step(void *a, void *b) {
     step_fn f = (step_fn)a;
     return (uintptr_t)f(a, b);
   }
*/

/* Bug: abstract declarator parameter list hardcoding
 * (direct_abstract_declarator fixes) */
typedef void (*callback_t)(int, char *);

int main() { return 0; }
