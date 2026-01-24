#ifndef RUN_NAT_H
#define RUN_NAT_H

#include "run_bool.h"

/*
 * Natural Number Formalism (Dusko/von Neumann encoding)
 *
 * Numbers are encoded as paired structures with boolean prefixes:
 *   0bar = <true, 0bar>   (self-referential fixpoint)
 *   nbar+1 = <false, nbar> (successor wraps predecessor)
 *
 * The encoding uses run_cc_pair where:
 *   - first: boolean flag (true for zero, false for successors)
 *   - second: predecessor value (or self-reference for zero)
 *
 * Operations:
 *   run_nat_zero()    - returns the representation of 0
 *   run_nat_succ(n)   - returns <false, n>
 *   run_nat_iszero(n) - returns the first component (true if 0)
 *   run_nat_pred(n)   - returns the second component (predecessor)
 *   run_nat(x)        - idempotent type filter for natural numbers
 */

/* Boolean constants for natural number encoding */
#define RUN_NAT_TRUE RUN_BOOL_TRUE
#define RUN_NAT_FALSE RUN_BOOL_FALSE

/* Pre-allocated zero representation (allocated on first use) */
static struct run_cc_pair *run_nat_zero_value = NULL;

/* Initialize the zero value (lazy initialization) */
RUN_REPRODUCIBLE
static inline run_obj_t run_nat_zero(void) {
  static run_obj_t canonical_zero = 0;
  if (canonical_zero == 0) {
    run_nat_zero_value =
        (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));
    run_nat_zero_value->first = RUN_NAT_TRUE;
    /* Fixed point: zero points to its own container */
    run_nat_zero_value->second = 0; // Temporary
    canonical_zero = embed((run_obj_t)run_nat_zero_value);
    run_nat_zero_value->second = canonical_zero; // Complete the fixpoint
  }
  return canonical_zero;
}

/* succ: Successor function */
RUN_REPRODUCIBLE
static inline run_obj_t run_nat_succ(run_obj_t n) {
  return embed(run_data_va(2, RUN_NAT_FALSE, n));
}

/* iszero: Test if a natural number is zero */
RUN_UNSEQUENCED
static inline run_obj_t run_nat_iszero(run_obj_t n) {
  if (n == 0)
    return RUN_NAT_TRUE;
  if (n >= (run_obj_t)1 && n <= (run_obj_t)4096)
    return RUN_NAT_FALSE;
  struct run_cc_pair *p = (struct run_cc_pair *)(uintptr_t)eval(n, 0);
  return p ? p->first : RUN_NAT_FALSE;
}

/* pred: Predecessor function */
RUN_UNSEQUENCED
static inline run_obj_t run_nat_pred(run_obj_t n) {
  if (n == 0)
    return 0;
  if (n >= (run_obj_t)1 && n <= (run_obj_t)4096)
    return n - 1;
  struct run_cc_pair *p = (struct run_cc_pair *)(uintptr_t)eval(n, 0);
  return p ? p->second : 0;
}

/* run_nat: Idempotent type filter for natural numbers */
RUN_REPRODUCIBLE
static inline run_obj_t run_nat(run_obj_t x) {
  /* Check if this is the zero representation */
  if (run_nat_iszero(x) == RUN_NAT_TRUE) {
    return x;
  }

  /* For successors, recursively validate the predecessor */
  run_obj_t pred = run_nat_pred(x);
  run_obj_t pred_validated = run_nat(pred);
  if (pred_validated == pred) {
    return x;
  }
  return run_nat_succ(pred_validated);
}

/* Convert C integer to natural number representation */
RUN_REPRODUCIBLE
static inline run_obj_t run_nat_from_int(intptr_t n) {
  if (n <= 0)
    return run_nat_zero();
  /* Safety: if n looks like a pointer, don't recurse (avoids double-wrapping
   * stack overflow) */
  if (n > 1000000)
    return (run_obj_t)n;
  return run_nat_succ(run_nat_from_int(n - 1));
}

/* Convert natural number representation to C integer */
RUN_REPRODUCIBLE
static inline intptr_t run_nat_to_int(run_obj_t n) {
  intptr_t count = 0;
  while (run_nat_iszero(n) == RUN_NAT_FALSE) {
    count++;
    n = run_nat_pred(n);
  }
  return count;
}

/* add: Addition morphism (recursive structural definition) */
RUN_REPRODUCIBLE
static inline run_obj_t run_nat_add(run_obj_t n, run_obj_t m) {
  /* if n is zero, return m */
  if (run_nat_iszero(n) == RUN_NAT_TRUE) {
    return m;
  }
  /* if n is succ(n'), return succ(add(n', m)) */
  return run_nat_succ(run_nat_add(run_nat_pred(n), m));
}

/* mult: Multiplication morphism */
RUN_REPRODUCIBLE
static inline run_obj_t run_nat_mult(run_obj_t n, run_obj_t m) {
  /* if n is zero, return zero */
  if (run_nat_iszero(n) == RUN_NAT_TRUE) {
    return run_nat_zero();
  }
  /* if n is succ(n'), return add(m, mult(n', m)) */
  return run_nat_add(m, run_nat_mult(run_nat_pred(n), m));
}

/* Macros for cleaner syntax */
#define nat_zero() run_nat_zero()
#define nat_succ(n) run_nat_succ((run_obj_t)(uintptr_t)(n))
#define nat_iszero(n) run_nat_iszero((run_obj_t)(uintptr_t)(n))
#define nat_pred(n) run_nat_pred((run_obj_t)(uintptr_t)(n))
#define nat(x) run_nat((run_obj_t)(uintptr_t)(x))
#define nat_from_int(n) run_nat_from_int((intptr_t)(n))
#define nat_to_int(n) run_nat_to_int((run_obj_t)(uintptr_t)(n))
#define nat_add(n, m)                                                          \
  run_nat_add((run_obj_t)(uintptr_t)(n), (run_obj_t)(uintptr_t)(m))
#define nat_mult(n, m)                                                         \
  run_nat_mult((run_obj_t)(uintptr_t)(n), (run_obj_t)(uintptr_t)(m))

#endif /* RUN_NAT_H */
