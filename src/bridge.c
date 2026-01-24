#include "cc.h"
#include <stdlib.h>

#define MAX_PARK_STACK 32
static val_ptr parked_val_stack[MAX_PARK_STACK];
static int parked_val_ptr = 0;
static char *parked_str_stack[MAX_PARK_STACK];
static int parked_str_ptr = 0;

static int parked_token = -1;
static YYSTYPE parked_lval;

static int entry_marker = -1;

void set_entry_marker(int tok) { entry_marker = tok; }

void park_lookahead(int tok, YYSTYPE lval) {
  parked_token = tok;
  parked_lval = lval;
}

int bridging_lex(YYSTYPE *lvalp, yyscan_t yyscanner) {
  if (entry_marker != -1) {
    int tok = entry_marker;
    entry_marker = -1;
    *lvalp = (YYSTYPE){0};
    return tok;
  }
  if (parked_token != -1) {
    int tok = parked_token;
    *lvalp = parked_lval;
    parked_token = -1;
    return tok;
  }
  return top_lex(lvalp, yyscanner);
}

void park_val(val_ptr p) {
  if (parked_val_ptr < MAX_PARK_STACK)
    parked_val_stack[parked_val_ptr++] = p;
}
val_ptr pickup_val(void) {
  if (parked_val_ptr > 0)
    return parked_val_stack[--parked_val_ptr];
  return NULL;
}

void park_str(char *s) {
  if (parked_str_ptr < MAX_PARK_STACK)
    parked_str_stack[parked_str_ptr++] = s;
}
char *pickup_str(void) {
  if (parked_str_ptr > 0)
    return parked_str_stack[--parked_str_ptr];
  return NULL;
}

void bridge_val_cb(val_ptr p) { park_val(p); }
void bridge_str_cb(val_ptr p) { park_str((char *)p); }

/* Real Bison-generated parser */
extern int real_parse(yyscan_t scanner, val_callback_t callback);

int top_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_TOP);
  return real_parse(scanner, callback);
}

int stmt_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_STMT);
  return real_parse(scanner, callback);
}

int expr_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_EXPR);
  return real_parse(scanner, callback);
}

int decl_parse(yyscan_t scanner, val_callback_t callback) {
  set_active_scanner(scanner);
  set_entry_marker(START_DECL);
  return real_parse(scanner, callback);
}

extern int nat_parse(yyscan_t scanner, val_callback_t callback);
extern int bool_parse(yyscan_t scanner, val_callback_t callback);
extern int val_parse(yyscan_t scanner, val_callback_t callback);

static yyscan_t active_scanner = NULL;
void set_active_scanner(yyscan_t scanner) { active_scanner = scanner; }
yyscan_t get_active_scanner(void) { return active_scanner; }

ExprInfo *reduce_axiom_string(const char *text, yyscan_t scanner) {
  (void)scanner; // Use isolated scanner
  yyscan_t temp_scanner;
  if (top_lex_init(&temp_scanner)) {
    return new_expr_info(text);
  }

  top__scan_string(text, temp_scanner);

  /* Reset bridging state for the isolated parse */
  int old_parked = parked_token;
  YYSTYPE old_parked_lval = parked_lval;
  int old_marker = entry_marker;
  char *old_last_id = last_id;
  parked_token = -1;
  entry_marker = -1;
  last_id = NULL;

  int old_suppress = suppress_val_errors;
  suppress_val_errors = 1;
  val_parse(temp_scanner, bridge_val_cb);
  suppress_val_errors = old_suppress;
  ExprInfo *res = pickup_val();

  if (last_id)
    free(last_id);
  last_id = old_last_id;

  /* Restore bridging state */
  parked_token = old_parked;
  parked_lval = old_parked_lval;
  entry_marker = old_marker;

  top_lex_destroy(temp_scanner);

  return res;
}
