#ifndef VAL_H
#define VAL_H

#include "context.h"
#include "expr.h"

/*
 * val_ptr is the core semantic value shared across modular parsers.
 * In run-cc, this corresponds to the ExprInfo pointer.
 */
struct ExprInfo;
typedef struct ExprInfo *val_ptr;

/* Standard YYSTYPE mapping is now handled by generated parser headers */

/*
 * val_callback_t defines a generic callback signature for communication
 * between grammar modules or other driver logic.
 */
typedef void (*val_callback_t)(val_ptr);

typedef enum {
  TYPE_KIND_NONE = 0,
  TYPE_KIND_INT,
  TYPE_KIND_LONG,
  TYPE_KIND_RUN_OBJ_T,
  TYPE_KIND_VOID,
  TYPE_KIND_OTHER
} TypeKind;

typedef struct {
  char *full;
  char *stripped;
  TypeKind kind;
  unsigned int type_count;
  unsigned int qualifier_count;
  unsigned int has_struct_union;
} TypeSpecInfo;

typedef enum {
  SIMPLE_CAST_NONE = 0,
  SIMPLE_CAST_INT,
  SIMPLE_CAST_LONG,
  SIMPLE_CAST_RUN_OBJ_T
} SimpleCastKind;

typedef struct {
  char *text;
  SimpleCastKind simple_kind;
} TypeNameInfo;

typedef struct {
  int kind;
  char *lexeme;
} MorphInfo;

typedef struct {
  char *text;
  char *ptr_prefix;
} DeclaratorInfo;

typedef struct ExprList {
  struct ExprInfo *expr;
  struct ExprList *next;
} ExprList;

#ifndef REAL_STYPE_DEFINED
#define REAL_STYPE_DEFINED
union REAL_STYPE {
  char *str;
  val_ptr val;
  TypeSpecInfo type_spec;
  MorphInfo morph;
  DeclaratorInfo decl;
  TypeNameInfo type_name;
  ExprList *list;
};
typedef union REAL_STYPE REAL_STYPE;
typedef union REAL_STYPE BOOL_STYPE;
typedef union REAL_STYPE NAT_STYPE;
typedef union REAL_STYPE VAL_STYPE;
#endif

#ifndef YYSTYPE
#define YYSTYPE REAL_STYPE
#endif
#define YYSTYPE_IS_DECLARED 1

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

/* Cross-parser bridge helpers */
void park_val(val_ptr p);
val_ptr pickup_val(void);
void park_str(char *s);
char *pickup_str(void);
void bridge_val_cb(val_ptr p);
void bridge_str_cb(val_ptr p);

#endif /* VAL_H */
