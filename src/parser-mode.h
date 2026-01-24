/* Parser Mode Selection - Implementing Structural Grammar Dispatch
 *
 * This file shows how to implement mode selection at parser initialization
 * to enable structural grammar dispatch without runtime conditionals.
 */

#ifndef RUN_CC_PARSER_MODE_H
#define RUN_CC_PARSER_MODE_H

#include "cc.h"

/* ============================================================================
 * APPROACH 1: GLR Parsing with Ambiguity Resolution
 * ============================================================================
 *
 * Use Bison's GLR parser to maintain multiple parse paths simultaneously,
 * then resolve ambiguity based on mode at reduction time.
 *
 * In run-cc-gram-defs.y:
 *   %glr-parser
 *   %expect-rr 100  // Expect reduce/reduce conflicts from mode variants
 *
 * The grammar would have both variants:
 *   primary_expression
 *       : primary_expression_c_to_run
 *       | primary_expression_passthrough
 *       ;
 *
 * Then use %dprec to prioritize based on mode:
 *   primary_expression
 *       : primary_expression_c_to_run %dprec 2
 *       | primary_expression_passthrough %dprec 1
 *       ;
 *
 * And in the semantic actions, use %merge to select based on runtime mode:
 *   %merge <mode_selector>
 */

/* ============================================================================
 * APPROACH 2: Multiple Start Symbols (Recommended)
 * ============================================================================
 *
 * Define separate start symbols for each mode and select at parse time.
 */

typedef enum {
  PARSE_MODE_C_TO_RUN_USER,      // C → Run for user code
  PARSE_MODE_C_TO_RUN_SYSTEM,    // C → Run for system headers (passthrough)
  PARSE_MODE_C_TO_RUN_DISCOVERY, // C → Run discovery pass
  PARSE_MODE_RUN_TO_C,           // Run → C
} ParseMode;

/* Global parse mode - set before calling yyparse() */
extern ParseMode parse_mode;

/* Mode determination function */
static inline ParseMode determine_parse_mode(void) {
  if (mode == MODE_C_TO_RUN) {
    if (in_system_header) {
      return PARSE_MODE_C_TO_RUN_SYSTEM;
    } else if (in_discovery_pass) {
      return PARSE_MODE_C_TO_RUN_DISCOVERY;
    } else {
      return PARSE_MODE_C_TO_RUN_USER;
    }
  } else {
    return PARSE_MODE_RUN_TO_C;
  }
}

/* ============================================================================
 * APPROACH 3: Lexer-Injected Mode Tokens
 * ============================================================================
 *
 * The lexer injects a mode token at the start of parsing based on current
 * state. This is the most aligned with the Run philosophy.
 */

/* Mode tokens - defined in run-cc-gram-defs.y */
// %token MODE_C_TO_RUN_USER_TOKEN MODE_C_TO_RUN_SYSTEM_TOKEN
//        MODE_C_TO_RUN_DISCOVERY_TOKEN MODE_RUN_TO_C_TOKEN

/* Lexer state for mode token injection */
extern int mode_token_injected;

/* Function to get the mode token to inject */
static inline int get_mode_token(void) {
  if (mode == MODE_C_TO_RUN) {
    if (in_system_header) {
      return MODE_C_TO_RUN_SYSTEM_TOKEN;
    } else if (in_discovery_pass) {
      return MODE_C_TO_RUN_DISCOVERY_TOKEN;
    } else {
      return MODE_C_TO_RUN_USER_TOKEN;
    }
  } else {
    return MODE_RUN_TO_C_TOKEN;
  }
}

/* ============================================================================
 * IMPLEMENTATION: Lexer Integration
 * ============================================================================
 *
 * In run-cc.l, add at the beginning of the rules section:
 *
 * %%
 *
 * <INITIAL>{
 *     // Inject mode token at start of parsing
 *     if (!mode_token_injected) {
 *         mode_token_injected = 1;
 *         return get_mode_token();
 *     }
 * }
 *
 * Then in the grammar, each mode-dependent rule is prefixed with the mode
 * token:
 *
 * primary_expression
 *     : MODE_C_TO_RUN_USER_TOKEN primary_expression_c_to_run
 *     | MODE_C_TO_RUN_SYSTEM_TOKEN primary_expression_passthrough
 *     | MODE_C_TO_RUN_DISCOVERY_TOKEN primary_expression_passthrough
 *     | MODE_RUN_TO_C_TOKEN primary_expression_run_to_c
 *     ;
 */

/* ============================================================================
 * IMPLEMENTATION: Grammar Structure
 * ============================================================================
 *
 * The grammar would be structured as:
 *
 * // Top-level with mode token
 * translation_unit
 *     : mode_token translation_unit_body
 *     ;
 *
 * mode_token
 *     : MODE_C_TO_RUN_USER_TOKEN { parse_mode =
 * PARSE_MODE_C_TO_RUN_USER; } | MODE_C_TO_RUN_SYSTEM_TOKEN { parse_mode
 * = PARSE_MODE_C_TO_RUN_SYSTEM; } | MODE_C_TO_RUN_DISCOVERY_TOKEN {
 * parse_mode = PARSE_MODE_C_TO_RUN_DISCOVERY; } | MODE_RUN_TO_C_TOKEN {
 * parse_mode = PARSE_MODE_RUN_TO_C; }
 *     ;
 *
 * translation_unit_body
 *     : external_declaration
 *     | translation_unit_body external_declaration
 *     ;
 *
 * // Mode-dependent rules use the parse_mode global
 * primary_expression
 *     : CONSTANT {
 *         if (parse_mode == PARSE_MODE_C_TO_RUN_USER) {
 *             print_constant_wrapped($1);
 *         } else {
 *             print_token($1);
 *         }
 *         $$ = NULL;
 *     }
 *     ;
 *
 * PROBLEM: This still has runtime conditionals!
 */

/* ============================================================================
 * BEST APPROACH: Separate Grammar Files with Shared Core
 * ============================================================================
 *
 * Create separate grammar files for each mode:
 *
 * run-cc-gram-core.y        - Shared rules (expressions, operators, etc.)
 * run-cc-gram-c-to-run.y    - C → Run specific rules
 * run-cc-gram-passthrough.y - Passthrough rules (system headers, discovery)
 * run-cc-gram-run-to-c.y    - Run → C specific rules
 *
 * Each mode-specific file includes the core and overrides mode-dependent rules:
 *
 * // run-cc-gram-c-to-run.y
 * %include "run-cc-gram-core.y"
 *
 * primary_expression
 *     : IDENTIFIER { print_token($1); $$ = $1; }
 *     | CONSTANT { print_constant_wrapped($1); $$ = NULL; }  // WRAPPED
 *     | ...
 *     ;
 *
 * return_statement
 *     : RETURN {
 *         print_token("return");
 *         print_token("( uintptr_t )");  // CAST
 *       } ';' { print_token(";"); }
 *     ;
 *
 * selection_statement
 *     : IF { print_token("ifte"); }  // IFTE, not IF
 *       ...
 *     ;
 *
 * // run-cc-gram-passthrough.y
 * %include "run-cc-gram-core.y"
 *
 * primary_expression
 *     : IDENTIFIER { print_token($1); $$ = $1; }
 *     | CONSTANT { print_token($1); $$ = NULL; }  // NOT WRAPPED
 *     | ...
 *     ;
 *
 * return_statement
 *     : RETURN { print_token("return"); } ';' { print_token(";");
 * }  // NO CAST
 *     ;
 *
 * selection_statement
 *     : IF { print_token("if"); }  // IF, not IFTE
 *       ...
 *     ;
 *
 * Then in run-cc-main.c:
 *
 * int main(int argc, char **argv) {
 *     // ... parse arguments ...
 *
 *     if (mode == MODE_C_TO_RUN) {
 *         if (in_system_header) {
 *             return parse_passthrough();  // Uses passthrough grammar
 *         } else if (in_discovery_pass) {
 *             return parse_passthrough();  // Uses passthrough grammar
 *         } else {
 *             return parse_c_to_run();     // Uses C→Run grammar
 *         }
 *     } else {
 *         return parse_run_to_c();         // Uses Run→C grammar
 *     }
 * }
 *
 * Each parse function is generated from its respective grammar file:
 *
 * // Generated from run-cc-gram-c-to-run.y
 * int parse_c_to_run(void);
 *
 * // Generated from run-cc-gram-passthrough.y
 * int parse_passthrough(void);
 *
 * // Generated from run-cc-gram-run-to-c.y
 * int parse_run_to_c(void);
 */

/* ============================================================================
 * PRACTICAL HYBRID APPROACH
 * ============================================================================
 *
 * For incremental migration, use a hybrid approach:
 *
 * 1. Keep existing grammar structure
 * 2. Add mode-specific production variants
 * 3. Use a mode-selection macro in actions
 * 4. Gradually eliminate runtime conditionals
 *
 * Define a macro that selects the appropriate action based on parse mode:
 */

/* Mode dispatch macro for grammar actions with different behavior per mode.
 * Use this when an action has two distinct behaviors:
 *   - c_to_run_action: executed when transforming user C code to Run
 *   - passthrough_action: executed for system headers, discovery pass, or Run→C
 *
 * Example usage in parser.y:
 *   primary_expression
 *       : CONSTANT {
 *           RUN_CC_MODE_DISPATCH(
 *               { char *s; safe_asprintf(&s, "( %s )", $1); $$ = new_expr_info(s); free(s); },
 *               { $$ = new_expr_info($1); }
 *           );
 *           free($1);
 *       }
 *       ;
 */
#define RUN_CC_MODE_DISPATCH(c_to_run_action, passthrough_action)              \
  do {                                                                         \
    if (should_emit_run()) {                                                   \
      c_to_run_action;                                                         \
    } else {                                                                   \
      passthrough_action;                                                      \
    }                                                                          \
  } while (0)

/* Variant that returns a value - for use in expression contexts */
#define RUN_CC_MODE_SELECT(c_to_run_expr, passthrough_expr)                    \
  (should_emit_run() ? (c_to_run_expr) : (passthrough_expr))

/*
 * Then in grammar actions:
 *
 * primary_expression
 *     : CONSTANT {
 *         RUN_CC_MODE_DISPATCH(
 *             print_constant_wrapped($1),
 *             print_token($1)
 *         );
 *         $$ = NULL;
 *     }
 *     ;
 *
 * This is still not ideal (still has runtime dispatch), but it:
 * - Centralizes the mode logic
 * - Makes it clear where mode-dependent behavior exists
 * - Provides a clear migration path to structural dispatch
 *
 * Eventually, replace with:
 *
 * primary_expression
 *     : constant_c_to_run
 *     | constant_passthrough
 *     ;
 *
 * constant_c_to_run
 *     : CONSTANT { print_constant_wrapped($1); $$ = NULL; }
 *     ;
 *
 * constant_passthrough
 *     : CONSTANT { print_token($1); $$ = NULL; }
 *     ;
 *
 * And use parser mode selection to choose which production to use.
 */

#endif /* RUN_CC_PARSER_MODE_H */
