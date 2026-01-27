%code top {
    #define _GNU_SOURCE
}

%code requires {

/* START OF run_runtime.h */
#ifndef RUN_RUNTIME_H
#define RUN_RUNTIME_H

#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(__x86_64__) || defined(__i386__)
// #include <x86intrin.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The universal categorical object type.
 *
 * Rationale: run_obj_t is defined as intptr_t because it is the only arithmetic
 * type in C that can hold both pointers and signed integers while remaining
 * compatible with the equality '==' operator. This is essential for maintaining
 * the clean, cast-free DSL syntax in tests.
 */
typedef intptr_t run_obj_t;

/*
 * C23 reproducible and unsequenced attributes
 */
#if defined(__GNUC__) && __GNUC__ < 14
#define RUN_REPRODUCIBLE __attribute__((pure))
#define RUN_UNSEQUENCED __attribute__((const))
#else
#define RUN_REPRODUCIBLE [[reproducible]]
#define RUN_UNSEQUENCED [[unsequenced]]
#endif

#ifndef RUN_CC_PAIR_DEFINED
#define RUN_CC_PAIR_DEFINED
struct run_cc_pair {
  run_obj_t first;
  run_obj_t second;
};
#endif

/*
 * Forward declarations of core functions to break circular dependencies
 */
RUN_REPRODUCIBLE static inline run_obj_t(eval)(run_obj_t p, run_obj_t a);
RUN_UNSEQUENCED static inline run_obj_t(data)(run_obj_t x);
RUN_REPRODUCIBLE static inline run_obj_t(program)(run_obj_t f, run_obj_t y);
RUN_REPRODUCIBLE static inline run_obj_t(kleene)(run_obj_t g, run_obj_t y);
RUN_REPRODUCIBLE static inline run_obj_t(run)(run_obj_t p, run_obj_t x,
                                              run_obj_t a);
RUN_REPRODUCIBLE static inline run_obj_t(embed)(run_obj_t a);
RUN_REPRODUCIBLE static inline run_obj_t run_data_va(int count, ...);
RUN_REPRODUCIBLE static inline run_obj_t partial_step(run_obj_t self,
                                                      run_obj_t args);

/*
 * Removed variadic macro definitions.
 * All variadic forms are now handled by the compiler (val.y)
 * which desugars them into chains of binary eval/program/kleene calls.
 */
#define compute(x) (compute)((run_obj_t)(uintptr_t)(x))
#define data(x) (data)((run_obj_t)(uintptr_t)(x))
#define swap(x, y) (swap)((run_obj_t)(uintptr_t)(x), (run_obj_t)(uintptr_t)(y))
#define copy(x) (copy)((run_obj_t)(uintptr_t)(x))
#define delete(x) (delete)((run_obj_t)(uintptr_t)(x))
#define function(x) (function)((run_obj_t)(uintptr_t)(x))
#define process(x, y)                                                          \
  (process)((run_obj_t)(uintptr_t)(x), (run_obj_t)(uintptr_t)(y))
#define sequential(g, f, x)                                                    \
  (sequential)((run_obj_t)(uintptr_t)(g), (run_obj_t)(uintptr_t)(f),           \
               (run_obj_t)(uintptr_t)(x))
#define partial(f, y)                                                          \
  (partial)((run_obj_t)(uintptr_t)(f), (run_obj_t)(uintptr_t)(y))
#define fixpoint(e) (fixpoint)((run_obj_t)(uintptr_t)(e))
#define run(p, x, a)                                                           \
  (run)((run_obj_t)(uintptr_t)(p), (run_obj_t)(uintptr_t)(x),                  \
        (run_obj_t)(uintptr_t)(a))
#define parallel(f, t, a, c)                                                   \
  (parallel)((run_obj_t)(uintptr_t)(f), (run_obj_t)(uintptr_t)(t),             \
             (run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(c))
#define eval(p, a) (eval)((run_obj_t)(uintptr_t)(p), (run_obj_t)(uintptr_t)(a))
#define program(f, y)                                                          \
  (program)((run_obj_t)(uintptr_t)(f), (run_obj_t)(uintptr_t)(y))
#define kleene(g, y)                                                           \
  (kleene)((run_obj_t)(uintptr_t)(g), (run_obj_t)(uintptr_t)(y))
#define identity(x) (identity)((run_obj_t)(uintptr_t)(x))
#define idempotent(x) (idempotent)((run_obj_t)(uintptr_t)(x))

/* C-like operator helpers used by transformed output. */
RUN_UNSEQUENCED static inline run_obj_t run_cc_add(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a + (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_sub(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a - (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_mul(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a * (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_div(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a / (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_mod(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a % (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_lt(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a < (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_gt(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a > (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_le(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a <= (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_ge(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a >= (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_eq(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a == (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_ne(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a != (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_and(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a && (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_or(run_obj_t a, run_obj_t b) {
  return (run_obj_t)((intptr_t)a || (intptr_t)b);
}
RUN_UNSEQUENCED static inline run_obj_t run_cc_not(run_obj_t a) {
  return (run_obj_t)(!(intptr_t)a);
}

/*
 * Implementations of base morphism functions
 */

RUN_REPRODUCIBLE
static inline run_obj_t(run)(run_obj_t p, run_obj_t x, run_obj_t a) {
  union {
    run_obj_t (*f)(run_obj_t, run_obj_t);
    run_obj_t v;
  } cast;
  cast.v = p;
  return cast.f(x, a);
}

RUN_REPRODUCIBLE
static inline run_obj_t(program)(run_obj_t f, run_obj_t y) {
  return eval(f, y);
}

RUN_REPRODUCIBLE
static inline run_obj_t(kleene)(run_obj_t g, run_obj_t y) { return eval(g, y); }

RUN_UNSEQUENCED
static inline run_obj_t point_step(run_obj_t self, run_obj_t args) {
  (void)args;
  return ((run_obj_t *)self)[1];
}

RUN_UNSEQUENCED
static inline run_obj_t p1_step(run_obj_t self, run_obj_t args) {
  (void)self;
  struct run_cc_pair *p = (struct run_cc_pair *)args;
  return p->first;
}

RUN_UNSEQUENCED
static inline run_obj_t p2_step(run_obj_t self, run_obj_t args) {
  (void)self;
  struct run_cc_pair *p = (struct run_cc_pair *)args;
  return p->second;
}

RUN_REPRODUCIBLE
static inline run_obj_t(eval)(run_obj_t p, run_obj_t a) {
  if (p == (run_obj_t)1) { /* RUN_BOOL_TRUE as first projection p1 */
    struct run_cc_pair *pair = (struct run_cc_pair *)a;
    return pair ? pair->first : (run_obj_t)0;
  }
  if (p == (run_obj_t)0) { /* RUN_BOOL_FALSE as second projection p2 */
    struct run_cc_pair *pair = (struct run_cc_pair *)a;
    return pair ? pair->second : (run_obj_t)0;
  }
  if (p > (run_obj_t)1 && p <= (run_obj_t)4096)
    return p;

  if (p > (run_obj_t)4096) {
    /* Low-level point check: if first element is point_step, return second */
    if (((run_obj_t *)p)[0] == (run_obj_t)point_step) {
      return ((run_obj_t *)p)[1];
    }

    /* Partial evaluator check: [partial_step, f, y] */
    if (((run_obj_t *)p)[0] == (run_obj_t)partial_step) {
      return partial_step(p, a);
    }

    /* Morphism call: assume p is a function pointer run_obj_t (*)(run_obj_t) */
    union {
      run_obj_t (*f)(run_obj_t);
      run_obj_t v;
    } cast;
    cast.v = p;
    return cast.f(a);
  }
  return (run_obj_t)0;
}

RUN_UNSEQUENCED
static inline run_obj_t run_iseq(run_obj_t p, run_obj_t q) {
  return (p == q) ? (run_obj_t)1 : (run_obj_t)0;
}

RUN_REPRODUCIBLE
static inline run_obj_t(embed)(run_obj_t a) {
  struct run_cc_pair *p =
      (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));
  p->first = (run_obj_t)point_step;
  p->second = a;
  return (run_obj_t)p;
}

RUN_REPRODUCIBLE
static inline run_obj_t run_data_va(int count, ...) {
  va_list ap;
  va_start(ap, count);
  if (count <= 0) {
    va_end(ap);
    return 0;
  }
  run_obj_t first = va_arg(ap, run_obj_t);
  if (count == 1) {
    va_end(ap);
    return first;
  }
  struct run_cc_pair *head =
      (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));
  head->first = first;
  struct run_cc_pair *curr = head;
  for (int i = 1; i < count; i++) {
    run_obj_t val = va_arg(ap, run_obj_t);
    if (i == count - 1) {
      curr->second = val;
    } else {
      struct run_cc_pair *next =
          (struct run_cc_pair *)malloc(sizeof(struct run_cc_pair));
      next->first = val;
      curr->second = (run_obj_t)next;
      curr = next;
    }
  }
  va_end(ap);
  return (run_obj_t)head;
}

#ifndef RUN_RUNTIME_DEFS_ONLY
RUN_UNSEQUENCED static inline run_obj_t(compute)(run_obj_t x) { return x; }
RUN_UNSEQUENCED static inline run_obj_t(data)(run_obj_t x) { return x; }
RUN_UNSEQUENCED static inline run_obj_t(identity)(run_obj_t x) { return x; }
RUN_UNSEQUENCED static inline run_obj_t(idempotent)(run_obj_t x) { return x; }
RUN_UNSEQUENCED static inline run_obj_t(swap)(run_obj_t x, run_obj_t y) {
  (void)y;
  return x;
}
RUN_UNSEQUENCED static inline run_obj_t(copy)(run_obj_t x) { return x; }
RUN_UNSEQUENCED static inline run_obj_t(delete)(run_obj_t x) {
  (void)x;
  return 0;
}
RUN_UNSEQUENCED static inline run_obj_t(function)(run_obj_t x) { return x; }
RUN_UNSEQUENCED static inline run_obj_t(process)(run_obj_t x, run_obj_t y) {
  (void)y;
  return x;
}
RUN_UNSEQUENCED static inline run_obj_t(sequential)(run_obj_t g, run_obj_t f,
                                                    run_obj_t x) {
  (void)g;
  (void)f;
  return x;
}

/*
 * Partial evaluator step function.
 * Closure structure: [partial_step, f, y]
 * When evaluated with argument a: returns eval(f, pair(y, a))
 *
 * Derived from: ⟦pev Γ y⟧ a = ⟦Γ⟧(y, a) (Section 2.2.2 of Monoidal Computer)
 */
RUN_REPRODUCIBLE
static inline run_obj_t partial_step(run_obj_t self, run_obj_t a) {
  run_obj_t *p = (run_obj_t *)self;
  return eval(p[1], run_data_va(2, p[2], a));
}

/*
 * partial(f, y) - Partial evaluator (pev)
 *
 * Creates a program p such that eval(p, a) = eval(f, pair(y, a))
 */
RUN_REPRODUCIBLE static inline run_obj_t(partial)(run_obj_t f, run_obj_t y) {
  run_obj_t *closure = malloc(3 * sizeof(run_obj_t));
  closure[0] = (run_obj_t)partial_step;
  closure[1] = f;
  closure[2] = y;
  return (run_obj_t)closure;
}
RUN_UNSEQUENCED static inline run_obj_t(fixpoint)(run_obj_t e) {
  (void)e;
  return 0;
}

/*
 * Parallel morphism (tensor product of morphisms)
 *
 * In Pavlovic's symmetric monoidal category:
 *   f ⊗ g : A × U → B × V
 *   where f: A → B and g: U → V
 *
 * Implementation uses the symmetric swap to rearrange (f, g, a, u)
 * into ((f, a), (g, u)) then applies eval to each component.
 *
 * parallel(f, g, a, u) = (eval(f, a), eval(g, u))
 */
RUN_REPRODUCIBLE
static inline run_obj_t(parallel)(run_obj_t f, run_obj_t g, run_obj_t a,
                                  run_obj_t u) {
  /* Conceptually: swap middle elements (f, g, a, u) -> (f, a, g, u)
   * Then apply eval to (f, a) and (g, u) */
  run_obj_t b = eval(f, a);
  run_obj_t v = eval(g, u);
  return run_data_va(2, b, v);
}
#else
#ifndef RUN_RUNTIME_DATA_DEFINED
#define RUN_RUNTIME_DATA_DEFINED
RUN_UNSEQUENCED static inline run_obj_t(data)(run_obj_t x) { return x; }
#endif
#endif

/* Internal step function morphisms - call with (self, args) */
RUN_REPRODUCIBLE
static inline run_obj_t run_step(run_obj_t morphism, run_obj_t step,
                                 run_obj_t args) {
  union {
    run_obj_t (*f)(run_obj_t, run_obj_t);
    run_obj_t v;
  } cast;
  cast.v = morphism;
  return cast.f(step, args);
}

RUN_REPRODUCIBLE
static inline run_obj_t program_step(run_obj_t step, run_obj_t args) {
  union {
    run_obj_t (*fn)(run_obj_t, run_obj_t);
    run_obj_t v;
  } cast;
  cast.v = step;
  return cast.fn(step, args);
}

RUN_REPRODUCIBLE
static inline run_obj_t kleene_step(run_obj_t step, run_obj_t args) {
  union {
    run_obj_t (*f)(run_obj_t, run_obj_t);
    run_obj_t v;
  } cast;
  cast.v = step;
  return cast.f(step, args);
}

#define run_cc_constant(x) (x)

#ifdef __cplusplus
}
#endif

#endif /* RUN_RUNTIME_H */

/* END OF run_runtime.h */

/* START OF run_bool.h */
#ifndef RUN_BOOL_H
#define RUN_BOOL_H


/* Boolean constants for categorical encodings */
/* true is p1 (first projection), false is p2 (second projection) */
/* We use the numeric values 1 and 0 which eval(p, a) now interprets as p1 and
 * p2 */
#define RUN_BOOL_TRUE ((run_obj_t)1)
#define RUN_BOOL_FALSE ((run_obj_t)0)

RUN_UNSEQUENCED static inline run_obj_t run_bool_true(void) {
  return RUN_BOOL_TRUE;
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_false(void) {
  return RUN_BOOL_FALSE;
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_not(run_obj_t b) {
  /* not(b) = iif(b, false, true) = eval(b, (false, true)) */
  return eval(b, run_data_va(2, RUN_BOOL_FALSE, RUN_BOOL_TRUE));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_and(run_obj_t a, run_obj_t b) {
  /* and(a, b) = iif(a, b, false) = eval(a, (b, false)) */
  return eval(a, run_data_va(2, b, RUN_BOOL_FALSE));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_or(run_obj_t a, run_obj_t b) {
  /* or(a, b) = iif(a, true, b) = eval(a, (true, b)) */
  return eval(a, run_data_va(2, RUN_BOOL_TRUE, b));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool_value(run_obj_t b) {
  /* Convert projection-based bool back to C-style 0/1 for control flow */
  return (run_obj_t)eval(b, run_data_va(2, (run_obj_t)1, (run_obj_t)0));
}

RUN_UNSEQUENCED static inline run_obj_t run_bool(run_obj_t b) {
  return b ? RUN_BOOL_TRUE : RUN_BOOL_FALSE;
}

/* rho(x) = iif(iseq(x, true), true, false) */
RUN_REPRODUCIBLE static inline run_obj_t run_rho(run_obj_t x) {
  return eval(run_iseq(x, RUN_BOOL_TRUE),
              run_data_va(2, RUN_BOOL_TRUE, RUN_BOOL_FALSE));
}

/* Macros for cleaner syntax */
#define bool_true() run_bool_true()
#define bool_false() run_bool_false()
#define bool_not(x) run_bool_not((run_obj_t)(uintptr_t)(x))
#define bool_and(a, b)                                                         \
  run_bool_and((run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(b))
#define bool_or(a, b)                                                          \
  run_bool_or((run_obj_t)(uintptr_t)(a), (run_obj_t)(uintptr_t)(b))
#define bool_value(x) run_bool_value((run_obj_t)(uintptr_t)(x))
#define iseq(p, q)                                                             \
  run_iseq((run_obj_t)(uintptr_t)(p), (run_obj_t)(uintptr_t)(q))
#define rho(x) run_rho((run_obj_t)(uintptr_t)(x))

#endif /* RUN_BOOL_H */

/* END OF run_bool.h */

/* START OF run_nat.h */
#ifndef RUN_NAT_H
#define RUN_NAT_H


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

/* END OF run_nat.h */

/* START OF expr.h */
#ifndef RUN_CC_EXPR_H
#define RUN_CC_EXPR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ExprInfo {
  char *text;
  int is_call;
  int is_morphism;
  int is_printf;
  int is_self_call;
  char *func_name;
  char *args;
} ExprInfo;

void free_expr_info(ExprInfo *e);
ExprInfo *new_expr_info(const char *text);
ExprInfo *new_recursive_call_info(const char *func, const char *args);

ExprInfo *make_op_1(const char *op, const char *axiom, ExprInfo *e1);
ExprInfo *make_op_2(const char *op, const char *axiom, int needs_nat,
                    int needs_bool, ExprInfo *e1, ExprInfo *e2);

#endif

/* END OF expr.h */

/* START OF context.h */
#ifndef RUN_CC_CONTEXT_H
#define RUN_CC_CONTEXT_H

typedef struct RunCCContext {
  char *func_name;
  int is_recursive;
  int uses_aggregate; /* Set if return type or params are struct/union */
  int ret_is_void;

  char **params;
  char **param_decls;
  char **param_types;
  int param_count;
  int param_cap;

  char *ret_type;
  char *attributes;
  int tco_arg_idx;

  struct RunCCContext *prev;
} RunCCContext;

void push_context(const char *func_name);
void push_context_from_staging(const char *func_name);
void set_context_ret_info(const char *type, int ret_is_void,
                          int ret_is_aggregate);
void set_context_attributes(const char *attrs);
void pop_context();
/* Helpers for grammar */
int is_current_func(const char *name);
void mark_recursive();
RunCCContext *get_current_context();

#endif

/* END OF context.h */

/* START OF val.h */
#ifndef VAL_H
#define VAL_H


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

/* END OF val.h */

/* START OF cc.h */
#ifndef RUN_CC_H
#define RUN_CC_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static inline int streq(const char *a, const char *b) {
  if (!a || !b)
    return 0;
  while (*a && *b) {
    if (*a != *b)
      return 0;
    a++;
    b++;
  }
  return *a == *b;
}

#ifndef MODULAR_PARSER
#include "parser.tab.h"
#define top_debug real_debug
extern int real_debug;
#endif

/* Include lexer header except when compiling the lexer itself */
#ifndef TOP_LEXER_SOURCE
#define YY_HEADER_EXPORT_START_CONDITIONS
#include "cc.yy.h"
#endif

/* Global State */
extern int mode;
#define MODE_DISCOVERY 0
#define MODE_C_TO_RUN 1
#define MODE_RUN_TO_C 2

extern int in_discovery_pass;
extern int verbose;
extern int lineno;
extern char *filename;
extern int val_mode;
extern int run_mode;
extern int needs_run_nat;
extern int needs_run_bool;
extern int suppress_val_errors;

/* Buffering / Suppression */
extern int suppress_print;
void start_buffering(void);
char *stop_buffering(void);
void append_buffer(const char *s);

/* Lexer Helpers */
extern char *current_func;
extern char *last_id;
extern int id_nesting_level;
extern int in_system_header;

/* Staging for Parameters */
extern char **staging_params;
extern char **staging_param_decls;
extern char **staging_param_types;
extern int staging_param_count;
extern int staging_param_cap;
extern int staging_uses_aggregate;
extern char *staging_func_name;

void reset_params(void);
void add_param(const char *name, const char *decl, const char *type,
               int is_aggregate);
void save_func_name(const char *name);
void set_func(const char *name);
void clear_func(void);

/* Lexer State IDs */
extern int STATE_INITIAL;
extern int STATE_PREPROC_LINE;
extern int STATE_PREPROC_SKIP;
extern int STATE_PAREN_SKIP;

/* Function Hooks */
void on_function_header(const char *attrs, TypeSpecInfo spec, const char *decl,
                        const char *ptr_prefix);
void on_run_header(void);
void on_function_start(const char *func_name, const char *ret_type);
void on_function_end(void);
void on_declaration_end(void);
char *on_declaration(const char *attrs, TypeSpecInfo spec,
                     const char *decl_list);
void on_storage_class_typedef(void);
void on_declarator(const char *name);
void on_type_scope_enter(void);
void on_type_scope_exit(void);
void register_function_return_type(const char *name, const char *ret_type,
                                   TypeKind kind);
TypeKind lookup_function_return_kind(const char *name);

struct RunCCContext;
void emit_nested_step_full(struct RunCCContext *ctx, const char *body);
void emit_all_specialized_code(void);
void reset_specialized_code(void);

/* JIT Hooks */
void run_jit_cleanup(void);

#define safe_asprintf(ptr, ...)                                                \
  do {                                                                         \
    if (asprintf(ptr, __VA_ARGS__) == -1) {                                    \
      fprintf(stderr, "asprintf failed\n");                                    \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

/* Type Classification */
int is_type(const char *name);
int register_type(const char *name);
int get_symbol_table_size(void);

ExprInfo *new_expr_info(const char *text);
ExprInfo *new_call_info(const char *func, const char *args);
ExprInfo *new_recursive_call_info(const char *func, const char *args);
void free_expr_info(ExprInfo *e);

/* Morphological Expression Builders */
ExprInfo *make_nat_add(ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_nat_mult(ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_run_iseq(ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_run_bool_not(ExprInfo *e1);
ExprInfo *make_generic_op(const char *op, ExprInfo *e1, ExprInfo *e2);
ExprInfo *make_op_1(const char *op, const char *axiom, ExprInfo *e1);
ExprInfo *make_op_2(const char *op, const char *axiom, int needs_nat,
                    int needs_bool, ExprInfo *e1, ExprInfo *e2);

/* Output redirection */
void print_token(const char *t);
void print_str(const char *s);

/* ArgList for JIT (internal to jit.c) */
#define MAX_ARGS 1024
#define SCRATCH_SIZE 65536

typedef struct ArgList {
  char *args[MAX_ARGS];
  int count;
} ArgList;

/* Missing State */
extern int buffer_owner;
extern int r_paren_depth;
extern int is_typedef;
extern int suppress_recursive_original;

/* Pass-specific functions */
void action_return_empty(void);
void action_return_expr(ExprInfo *e);
int should_emit_run(void);
void reset_buffer(void);

/* Lexer internal API */
void lex_init(void);
void init_states(int initial, int preproc_line, int preproc_skip,
                 int paren_skip);
int handle_line_marker(const char *text);
int handle_identifier(void *lvalp, const char *text);
void error(const char *s);
void push_native_state(yyscan_t yyscanner);
void pop_state(yyscan_t yyscanner);
int is_native_context(void);

/* Diagnostic Helpers */
void diagnostic_report(yyscan_t scanner, const char *type, const char *fmt,
                       ...);

#define DEBUG_PARSER(scanner, ...)                                             \
  if (verbose > 1)                                                             \
  diagnostic_report(scanner, "DEBUG", __VA_ARGS__)

#define PARSER_ERROR(scanner, ...)                                             \
  diagnostic_report(scanner, "error", __VA_ARGS__)

#define LEXER_ERROR(scanner, ...)                                              \
  diagnostic_report(scanner, "lexer error", __VA_ARGS__)

#define PARSER_RECOVER(scanner, ...)                                           \
  if (verbose)                                                                 \
  diagnostic_report(scanner, "recovery", __VA_ARGS__)

/* Reentrant Helpers - use top_* directly from cc.yy.h */
void park_lookahead(int tok, YYSTYPE lval);
int bridging_lex(YYSTYPE *lvalp, yyscan_t yyscanner);
ExprInfo *reduce_axiom_string(const char *text, yyscan_t scanner);
void set_active_scanner(yyscan_t scanner);
yyscan_t get_active_scanner(void);

/* Exported Parser Entry Points */
int top_parse(yyscan_t scanner, val_callback_t callback);
int expr_parse(yyscan_t scanner, val_callback_t callback);
int decl_parse(yyscan_t scanner, val_callback_t callback);
int stmt_parse(yyscan_t scanner, val_callback_t callback);
int nat_parse(yyscan_t scanner, val_callback_t callback);
int bool_parse(yyscan_t scanner, val_callback_t callback);

/* JIT driver */
extern char **environ;
int jit_execute(const char *cc_bin, int argc, char **argv, int arg_start_index);

/* Specialized code */
void print_specialized_preamble(void);

#endif
/* Parser Mode Selection - Implementing Structural Grammar Dispatch
 *
 * This file shows how to implement mode selection at parser initialization
 * to enable structural grammar dispatch without runtime conditionals.
 */


/* END OF cc.h */

}

%code provides {

/* Lexer state for mode token injection */
extern int mode_token_injected;

/* Function to get the mode token to inject */
static inline int get_mode_token(void) {
  if (mode == MODE_C_TO_RUN) {
    if (in_system_header) {
      return MODE_MARKER_PASSTHROUGH;
    } else if (in_discovery_pass) {
      return MODE_MARKER_DISCOVERY;
    } else {
      return MODE_MARKER_C_TO_RUN;
    }
  } else {
    return MODE_MARKER_C_TO_RUN;
  }
}

}

%code {
    #include <ctype.h>
    /* #include "cc.h" */


    
    int real_error(yyscan_t scanner, val_callback_t callback, const char *msg) {
        (void)callback;
        if (val_mode) {
             if (suppress_val_errors) return 0;
             fprintf(stderr, "Val Parser Error: %s at '%s'\n", msg, top_get_text(scanner));
             return 0;
        }
        PARSER_ERROR(scanner, "%s at '%s'", msg, top_get_text(scanner));
        return 0;
    }

    #define real_lex bridging_lex

    static TypeKind merge_type_kind(TypeKind left, TypeKind right) {
        if (left == TYPE_KIND_NONE)
            return right;
        if (right == TYPE_KIND_NONE)
            return left;
        if (left == TYPE_KIND_OTHER || right == TYPE_KIND_OTHER)
            return TYPE_KIND_OTHER;
        if (left == right)
            return left;
        return TYPE_KIND_OTHER;
    }

    static TypeSpecInfo make_type_spec(const char *full, const char *stripped,
                                       TypeKind kind, unsigned int type_count,
                                       unsigned int qualifier_count,
                                       unsigned int has_struct_union) {
        TypeSpecInfo spec;
        spec.full = strdup(full ? full : "");
        spec.stripped = strdup(stripped ? stripped : "");
        spec.kind = kind;
        spec.type_count = type_count;
        spec.qualifier_count = qualifier_count;
        spec.has_struct_union = has_struct_union;
        return spec;
    }

    static TypeSpecInfo merge_type_specs(TypeSpecInfo left, TypeSpecInfo right) {
        TypeSpecInfo merged;
        safe_asprintf(&merged.full, "%s %s", left.full, right.full);

        if (left.stripped && left.stripped[0]) {
            if (right.stripped && right.stripped[0]) {
                safe_asprintf(&merged.stripped, "%s %s", left.stripped, right.stripped);
            } else {
                merged.stripped = strdup(left.stripped);
            }
        } else if (right.stripped && right.stripped[0]) {
            merged.stripped = strdup(right.stripped);
        } else {
            merged.stripped = strdup("");
        }

        merged.kind = merge_type_kind(left.kind, right.kind);
        merged.type_count = left.type_count + right.type_count;
        merged.qualifier_count = left.qualifier_count + right.qualifier_count;
        merged.has_struct_union =
            left.has_struct_union || right.has_struct_union;

        free(left.full);
        free(left.stripped);
        free(right.full);
        free(right.stripped);
        return merged;
    }

    static SimpleCastKind simple_cast_kind(TypeSpecInfo spec,
                                           int has_abstract_decl) {
        if (has_abstract_decl)
            return SIMPLE_CAST_NONE;
        if (spec.type_count != 1 || spec.qualifier_count != 0)
            return SIMPLE_CAST_NONE;
        switch (spec.kind) {
            case TYPE_KIND_INT:
                return SIMPLE_CAST_INT;
            case TYPE_KIND_LONG:
                return SIMPLE_CAST_LONG;
            case TYPE_KIND_RUN_OBJ_T:
                return SIMPLE_CAST_RUN_OBJ_T;
            default:
                return SIMPLE_CAST_NONE;
        }
    }

    static char *dup_range(const char *start, size_t len) {
        char *s = malloc(len + 1);
        if (!s)
            return NULL;
        memcpy(s, start, len);
        s[len] = '\0';
        return s;
    }

    static size_t find_top_level_comma(const char *text) {
        size_t i = 0;
        int depth = 0;
        int in_string = 0;
        while (text && text[i]) {
            char c = text[i];
            if (in_string) {
                if (c == '\\' && text[i + 1]) {
                    i += 2;
                    continue;
                }
                if (c == '"')
                    in_string = 0;
                i++;
                continue;
            }
            if (c == '"') {
                in_string = 1;
                i++;
                continue;
            }
            if (c == '(' || c == '[' || c == '{') {
                depth++;
            } else if (c == ')' || c == ']' || c == '}') {
                if (depth > 0)
                    depth--;
            } else if (c == ',' && depth == 0) {
                return i;
            }
            i++;
        }
        return (size_t)-1;
    }

    static char *replace_percent_ld(const char *text) {
        if (!text)
            return NULL;
        size_t len = strlen(text);
        char *out = malloc(len + 1);
        if (!out)
            return NULL;
        size_t i = 0;
        size_t j = 0;
        int in_string = 0;
        int changed = 0;
        while (i < len) {
            char c = text[i];
            if (in_string) {
                if (c == '\\' && i + 1 < len) {
                    out[j++] = text[i++];
                    out[j++] = text[i++];
                    continue;
                }
                if (c == '"') {
                    in_string = 0;
                    out[j++] = c;
                    i++;
                    continue;
                }
                if (c == '%' && i + 2 < len && text[i + 1] == 'l' &&
                    text[i + 2] == 'd' && !(i > 0 && text[i - 1] == '%')) {
                    out[j++] = '%';
                    out[j++] = 'd';
                    i += 3;
                    changed = 1;
                    continue;
                }
            } else if (c == '"') {
                in_string = 1;
            }
            out[j++] = c;
            i++;
        }
        out[j] = '\0';
        if (!changed) {
            free(out);
            return NULL;
        }
        return out;
    }

    static char *adjust_printf_args(const char *args_text) {
        if (!args_text)
            return NULL;

        size_t comma_pos = find_top_level_comma(args_text);
        if (comma_pos == (size_t)-1)
            return NULL;

        char *first = dup_range(args_text, comma_pos);
        if (!first)
            return NULL;

        const char *second = args_text + comma_pos + 1;
        while (*second && isspace((unsigned char)*second))
            second++;
        if (!isalpha((unsigned char)*second) && *second != '_') {
            free(first);
            return NULL;
        }

        const char *name_start = second;
        second++;
        while (isalnum((unsigned char)*second) || *second == '_')
            second++;
        char *name = dup_range(name_start, (size_t)(second - name_start));
        if (!name) {
            free(first);
            return NULL;
        }

        while (*second && isspace((unsigned char)*second))
            second++;
        if (*second != '(') {
            free(first);
            free(name);
            return NULL;
        }

        TypeKind ret_kind = lookup_function_return_kind(name);
        if (ret_kind != TYPE_KIND_INT) {
            free(first);
            free(name);
            return NULL;
        }

        char *new_first = replace_percent_ld(first);
        free(first);
        free(name);
        if (!new_first)
            return NULL;

        char *new_args = NULL;
        safe_asprintf(&new_args, "%s%s", new_first, args_text + comma_pos);
        free(new_first);
        return new_args;
    }





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Forward declarations to satisfy pure parser */
int val_lex(YYSTYPE *lvalp, yyscan_t yyscanner);
void val_error(yyscan_t scanner, val_callback_t callback, const char *msg);
extern int top_lex(YYSTYPE *lvalp, yyscan_t yyscanner);
char *top_get_text(yyscan_t yyscanner);

static ExprList *new_expr_list(ExprInfo *e, ExprList *n) {
    ExprList *l = malloc(sizeof(*l));
    l->expr = e;
    l->next = n;
    return l;
}

static void free_expr_list(ExprList *l) {
    while (l) {
        ExprList *next = l->next;
        if (l->expr) free_expr_info(l->expr);
        free(l);
        l = next;
    }
}

static ExprInfo *reduce_identity(ExprList *args) {
    if (!args) return NULL;
    if (!args->next) return args->expr;
    ExprInfo *rest = reduce_identity(args->next);
    char *s; safe_asprintf(&s, "eval ( data ( %s ) , %s )", args->expr->text, rest->text);
    ExprInfo *res = new_expr_info(s); free(s);
    /* We don't free args->expr here because it's owned by the list which we might free later,
       but actually we need to be careful with ownership.
       Let's say this function 'consumes' the list and its expressions. */
    free_expr_info(args->expr);
    free_expr_info(rest);
    free(args);
    return res;
}

static ExprInfo *reduce_idempotent(ExprList *args) {
    if (!args) return NULL;
    if (!args->next) return args->expr;
    ExprInfo *rest = reduce_idempotent(args->next);
    char *s; safe_asprintf(&s, "data ( eval ( %s , %s ) )", args->expr->text, rest->text);
    ExprInfo *res = new_expr_info(s); free(s);
    free_expr_info(args->expr);
    free_expr_info(rest);
    free(args);
    return res;
}

static ExprInfo *reduce_program(ExprInfo *f, ExprList *args) {
    if (!args) return f;
    ExprInfo *current = f;
    ExprList *cur_arg = args;
    while (cur_arg) {
        char *s;
        if (current == f) {
            safe_asprintf(&s, "program ( %s , %s )", current->text, cur_arg->expr->text);
        } else {
            safe_asprintf(&s, "eval ( %s , %s )", current->text, cur_arg->expr->text);
        }
        ExprInfo *next_expr = new_expr_info(s); free(s);
        if (current != f) free_expr_info(current);
        current = next_expr;
        cur_arg = cur_arg->next;
    }
    // Note: this implementation doesn't free the original args.
    // Usually a higher level takes care of that.
    return current;
}

static ExprInfo *reduce_kleene(ExprInfo *g, ExprList *args) {
    if (!args) return g;
    ExprInfo *current = g;
    ExprList *cur_arg = args;
    while (cur_arg) {
        char *s;
        if (current == g) {
            safe_asprintf(&s, "kleene ( %s , %s )", current->text, cur_arg->expr->text);
        } else {
            safe_asprintf(&s, "eval ( %s , %s )", current->text, cur_arg->expr->text);
        }
        ExprInfo *next_expr = new_expr_info(s); free(s);
        if (current != g) free_expr_info(current);
        current = next_expr;
        cur_arg = cur_arg->next;
    }
    return current;
}

static ExprInfo *reduce_eval(ExprInfo *p, ExprList *args) {
    ExprInfo *current = p;
    ExprList *cur_arg = args;
    while (cur_arg) {
        char *s; safe_asprintf(&s, "eval ( %s , %s )", current->text, cur_arg->expr->text);
        ExprInfo *next_expr = new_expr_info(s); free(s);
        if (current != p) free_expr_info(current);
        current = next_expr;
        cur_arg = cur_arg->next;
    }
    return current;
}

typedef enum {
    MORPH_RUN,
    MORPH_EVAL,
    MORPH_COMPUTE,
    MORPH_PROGRAM,
    MORPH_DATA,
    MORPH_IDEMPOTENT,
    MORPH_SWAP,
    MORPH_COPY,
    MORPH_DELETE,
    MORPH_FUNCTION,
    MORPH_PROCESS,
    MORPH_SEQUENTIAL,
    MORPH_PARALLEL,
    MORPH_PARTIAL,
    MORPH_FIXPOINT,
    MORPH_KLEENE,
    MORPH_IDENTITY,
    MORPH_ISEQ,
    MORPH_RHO,
    MORPH_BOOL_VALUE,
} morphism_kind_t;

static ExprInfo *apply_generic_call(const char *name, ExprList *args) {
    char *lower_name = strdup(name);
    for (int i = 0; lower_name[i]; i++) {
        if (lower_name[i] >= 'A' && lower_name[i] <= 'Z')
            lower_name[i] = lower_name[i] + ('a' - 'A');
    }

    char *s = NULL;
    if (!args) {
        safe_asprintf(&s, "%s ( )", lower_name);
    } else {
        ExprList *cur = args;
        while (cur) {
            if (!s) {
                safe_asprintf(&s, "%s ( %s", lower_name, cur->expr->text);
            } else {
                char *old = s;
                safe_asprintf(&s, "%s , %s", old, cur->expr->text);
                free(old);
            }
            cur = cur->next;
        }
        if (s) {
            char *old = s;
            safe_asprintf(&s, "%s )", old);
            free(old);
        }
    }
    free(lower_name);

    ExprInfo *res = new_expr_info(s);
    free(s);
    free_expr_list(args);
    return res;
}

static ExprInfo *apply_morphism_kind(morphism_kind_t kind, ExprList *args) {
    if (!args) {
        return NULL;
    }

    switch (kind) {
        case MORPH_IDENTITY:
            return reduce_identity(args);
        case MORPH_IDEMPOTENT:
            return reduce_idempotent(args);
        case MORPH_PROGRAM: {
            ExprInfo *res = reduce_program(args->expr, args->next);
            free(args);
            return res;
        }
        case MORPH_KLEENE: {
            ExprInfo *res = reduce_kleene(args->expr, args->next);
            free(args);
            return res;
        }
        case MORPH_BOOL_VALUE: {
            char *s;
            safe_asprintf(&s, "run_bool_value ( %s )", args->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_ISEQ: {
            char *s;
            safe_asprintf(&s, "run_iseq ( %s , %s )", args->expr->text,
                          args->next->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_RHO: {
            char *s;
            safe_asprintf(&s, "run_rho ( %s )", args->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_EVAL: {
            ExprInfo *res = reduce_eval(args->expr, args->next);
            free(args);
            return res;
        }
        case MORPH_COMPUTE:
        case MORPH_DATA:
        case MORPH_FUNCTION: {
            ExprInfo *res = new_expr_info(args->expr->text);
            free_expr_list(args);
            return res;
        }
        case MORPH_COPY: {
            char *s;
            safe_asprintf(&s, "run_data_va ( 2 , %s , %s )", args->expr->text,
                          args->expr->text);
            ExprInfo *res = new_expr_info(s);
            free(s);
            free_expr_list(args);
            return res;
        }
        case MORPH_SWAP: {
            if (args && args->next) {
                char *s;
                safe_asprintf(&s, "run_data_va ( 2 , %s , %s )",
                              args->next->expr->text, args->expr->text);
                ExprInfo *res = new_expr_info(s);
                free(s);
                free_expr_list(args);
                return res;
            }
            break;
        }
        case MORPH_PROCESS: {
            ExprInfo *res = new_expr_info(args->expr->text);
            free_expr_list(args);
            return res;
        }
        case MORPH_DELETE: {
            ExprInfo *res = new_expr_info("0");
            free_expr_list(args);
            return res;
        }
        case MORPH_SEQUENTIAL: {
            if (args && args->next && args->next->next) {
                char *s;
                safe_asprintf(&s, "eval ( %s , eval ( %s , %s ) )",
                              args->next->expr->text, args->expr->text,
                              args->next->next->expr->text);
                ExprInfo *res = new_expr_info(s);
                free(s);
                free_expr_list(args);
                return res;
            }
            break;
        }
        case MORPH_PARTIAL: {
            if (args && args->next) {
                char *s;
                safe_asprintf(&s, "partial ( %s , %s )", args->expr->text,
                              args->next->expr->text);
                ExprInfo *res = new_expr_info(s);
                free(s);
                free_expr_list(args);
                return res;
            }
            break;
        }
        case MORPH_RUN:
            return apply_generic_call("run", args);
        case MORPH_PARALLEL:
            return apply_generic_call("parallel", args);
        case MORPH_FIXPOINT:
            return apply_generic_call("fixpoint", args);
        default:
            break;
    }

    free_expr_list(args);
    return NULL;
}

}

%define api.pure full
%define api.prefix {real_}
%debug
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { val_callback_t callback }

%define api.value.type {REAL_STYPE}

%token <str> IDENTIFIER 258
%token <str> CONSTANT 259
%token <str> STRING_LITERAL 260
%token <str> SIZEOF 261
%token <str> TYPE_NAME 262
%token <str> OFFSETOF 263
%token <str> RECURSIVE_ID 264
%token <str> PRINTF
/* RUN_FUNC removed - RUN token serves both morphism and run() definition */
%token <str> RUN 283
%token <str> EVAL 284
%token <str> COMPUTE 285
%token <str> PROGRAM 286
%token <str> DATA 287
%token <str> IDEMPOTENT 288
%token <str> SWAP 290
%token <str> COPY 291
%token <str> DELETE 292
%token <str> FUNCTION 293
%token <str> PROCESS 294
%token <str> SEQUENTIAL 295
%token <str> PARALLEL 296
%token <str> PARTIAL 297
%token <str> FIXPOINT 298
%token <str> KLEENE 299
%token <str> IDENTITY 361
%token <str> ISEQ 362
%token <str> RHO 363
%token <str> BOOL_VALUE 364
%token CAT_PLUS 365
%token CAT_STAR 366
%token CAT_EQ 367
%token CAT_NE 368
%token CAT_BANG 369
%token PTR_OP 300
%token INC_OP 301
%token DEC_OP 302
%token LEFT_OP 303
%token RIGHT_OP 304
%token LE_OP 305
%token GE_OP 306
%token EQ_OP 307
%token NE_OP 308
%token AND_OP 309
%token OR_OP 310
%token MUL_ASSIGN 311
%token DIV_ASSIGN 312
%token MOD_ASSIGN 313
%token ADD_ASSIGN 314
%token SUB_ASSIGN 315
%token LEFT_ASSIGN 316
%token RIGHT_ASSIGN 317
%token AND_ASSIGN 318
%token XOR_ASSIGN 319
%token OR_ASSIGN 320
%token TYPEDEF 321
%token EXTERN 322
%token STATIC 323
%token AUTO 324
%token REGISTER 325
%token TYPEOF 326
%token INLINE 327
%token RESTRICT 328
%token CONST 329
%token VOLATILE 330
%token <str> STD_TYPE 331
%token STRUCT 332
%token UNION 333
%token ENUM 334
%token ELLIPSIS 335
%token CASE 336
%token DEFAULT 337
%token IF 338
%token ELSE 339
%token SWITCH 341
%token WHILE 342
%token DO 343
%token FOR 344
%token GOTO 345
%token CONTINUE 346
%token BREAK 347
%token RETURN 348
%token MODE_MARKER_C_TO_RUN 349
%token MODE_MARKER_PASSTHROUGH 350
%token MODE_MARKER_DISCOVERY 351
%token <str> LBRACE 352 "{"
%token <str> RBRACE 353 "}"

%token START_TOP 1001
%token START_DECL 1002
%token START_STMT 1003
%token START_EXPR 1004
%token START_NAT 1005
%token START_BOOL 1006

%token <str> RUN_CC_ADD RUN_CC_SUB RUN_CC_MUL RUN_CC_DIV RUN_CC_MOD
%token <str> RUN_CC_GT RUN_CC_LT RUN_CC_GE RUN_CC_LE RUN_CC_EQ RUN_CC_NE
%token <str> RUN_CC_AND RUN_CC_OR RUN_CC_NOT RUN_CC_IFTE
%token <str> IFTE 340
%token <str> CONSTEXPR 354
%token <str> STATIC_ASSERT 355
%token <str> THREAD_LOCAL 356
%token <str> ALIGNAS 357
%token <str> ALIGNOF 358
%token LEFT_BRACKET_BRACKET 1024
%token RIGHT_BRACKET_BRACKET 1025
%token <str> RUN_CC_CONSTANT 1023
%token <str> TYPE_INT
%token <str> TYPE_VOID
%token <str> TYPE_LONG
%token <str> TYPE_RUN_OBJ_T

%start entry

%type <type_name> type_name
%type <str> function_header
%type <decl> function_declarator
%type <str> declaration struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration struct_declarator_list_full struct_declarator_full enum_specifier enumerator_list enumerator init_declarator_list_full init_declarator_full declarator_full direct_declarator_full pointer type_qualifier_list parameter_type_list parameter_list parameter_declaration identifier_list initializer initializer_list abstract_declarator direct_abstract_declarator static_assert_declaration block_item block_item_list bracket_static_expression designation designator_list designator
%type <type_spec> declaration_specifiers declaration_specifier storage_class_specifier type_specifier_atomic type_qualifier specifier_qualifier_list specifier_qualifier
%type <val> expression constant_expression assignment_expression conditional_expression logical_or_expression logical_and_expression inclusive_or_expression exclusive_or_expression and_expression equality_expression relational_expression shift_expression additive_expression multiplicative_expression cast_expression unary_expression postfix_expression primary_expression argument_expression_list recursive_call if_prefix while_prefix
%type <str> assignment_operator pavlovic_operator string_literal_sequence generic_identifier any_id attribute_specifier_list attribute_specifier_list_opt attribute_specifier attribute_list attribute attribute_token attribute_scoped_token attribute_argument_clause_opt label statement compound_statement expression_statement selection_statement iteration_statement jump_statement statement_list labeled_statement static_assert_tail


%token START_VAL 1007

/* Val.y definitions */
%type <val> val_axiom arithmetic_axiom logic_axiom categorical_axiom
%type <list> val_list
%type <str> any_val_id
%type <morph> morphism_kind
%%


entry:
  START_TOP translation_unit { YYACCEPT; }
| START_DECL declaration { if (callback) callback((val_ptr)$2); YYACCEPT; }
| START_STMT statement_list { YYACCEPT; }
| START_EXPR expression { if (callback) callback($2); YYACCEPT; }
| START_VAL val_start { YYACCEPT; }
;

/* TOP Level */
translation_unit: translation_unit_inner ;

translation_unit_inner
	: external_declaration
	| dispatcher_marker external_declaration
	| translation_unit_inner external_declaration
	| translation_unit_inner dispatcher_marker external_declaration
	;

dispatcher_marker
	: MODE_MARKER_C_TO_RUN
	| MODE_MARKER_PASSTHROUGH
	| MODE_MARKER_DISCOVERY
	;

external_declaration
	: run_definition
	| function_definition
	| declaration { print_str($1); print_str("\n"); free($1); reset_params(); }
	| ';' { print_str(";\n"); reset_params(); }
	| error ';' { PARSER_RECOVER(scanner, "Recovered at ';'"); yyerrok; }
	| error '}' { PARSER_RECOVER(scanner, "Recovered at '}'"); yyerrok; }
	;

function_definition
    : function_header function_body { on_function_end(); pop_context(); reset_params(); }
    ;

function_header
    : attribute_specifier_list_opt declaration_specifiers function_declarator {
            on_function_header($1, $2, $3.text, $3.ptr_prefix);
            if ($1) free($1);
            if ($2.full) free($2.full);
            if ($2.stripped) free($2.stripped);
            free($3.text);
            free($3.ptr_prefix);
      }
    ;


declaration
    : attribute_specifier_list_opt declaration_specifiers init_declarator_list_full ';' { $$ = on_declaration($1, $2, $3); if (callback) callback((val_ptr)$$); on_declaration_end(); if ($1) free($1); free($2.full); free($2.stripped); free($3); }
	| attribute_specifier_list_opt declaration_specifiers ';' { $$ = on_declaration($1, $2, NULL); if (callback) callback((val_ptr)$$); on_declaration_end(); if ($1) free($1); free($2.full); free($2.stripped); }
	| static_assert_declaration { $$ = $1; if (callback) callback((val_ptr)$$); on_declaration_end(); }
    ;

static_assert_declaration
	: static_assert_prefix constant_expression static_assert_tail ')' ';' { pop_state(scanner); safe_asprintf(&$$, "static_assert ( %s %s ) ;", $2->text, $3); free_expr_info($2); free($3); }
	;

static_assert_prefix
	: STATIC_ASSERT { push_native_state(scanner); } '('
	;

static_assert_tail
	: ',' STRING_LITERAL { safe_asprintf(&$$, ", %s", $2); free($2); }
	| %empty { $$ = strdup(""); }
	;

run_definition
       : RUN '(' ')' {
               on_run_header();
               free($1);
       } function_body {
               on_function_end();
               pop_context();
               reset_params();
       }
       ;

function_body
	: LBRACE {
		RunCCContext *ctx = get_current_context();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			push_native_state(scanner);
		}
	} block_item_list RBRACE {
		RunCCContext *ctx = get_current_context();
		char *body = stop_buffering();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			pop_state(scanner);
		}
		if (should_emit_run() && ctx && !ctx->uses_aggregate) {
			emit_nested_step_full(ctx, body);
			print_str("}\n");
		} else {
			/* Passthrough: output body directly */
			print_str(" { "); if (body) print_str(body); print_str(" }\n");
		}
		if (body) free(body);
	  }
    | LBRACE {
		RunCCContext *ctx = get_current_context();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			push_native_state(scanner);
		}
	} RBRACE {
		RunCCContext *ctx = get_current_context();
		if (run_mode && should_emit_run() && ctx && !ctx->uses_aggregate &&
		    !needs_run_nat && !needs_run_bool) {
			pop_state(scanner);
		}
		if (should_emit_run() && ctx && !ctx->uses_aggregate) {
			emit_nested_step_full(ctx, "");
			print_str("}\n");
		} else {
			/* Passthrough: empty body */
			print_str(" { }\n");
		}
    }
	;

/* Block Items */
block_item_list
    : block_item
    | block_item_list block_item
    ;

block_item
    : statement
    | declaration_specifiers init_declarator_list_full ';' { print_str($1.full); print_str(" "); print_str($2); print_str(" ; "); free($1.full); free($1.stripped); free($2); }
    | attribute_specifier_list declaration_specifiers init_declarator_list_full ';' { print_str($1); print_str(" "); print_str($2.full); print_str(" "); print_str($3); print_str(" ; "); free($1); free($2.full); free($2.stripped); free($3); }
    | error ';' { PARSER_RECOVER(scanner, "Recovered at ';'"); yyerrok; }
    ;

/* Declarations */
declaration_specifiers
	: declaration_specifier { $$ = $1; }
	| declaration_specifiers declaration_specifier { $$ = merge_type_specs($1, $2); }
	;

declaration_specifier
	: storage_class_specifier { $$ = $1; }
	| type_specifier_atomic { $$ = $1; }
	| type_qualifier { $$ = $1; }
	;

storage_class_specifier
	: TYPEDEF { on_storage_class_typedef(); $$ = make_type_spec("typedef", "", TYPE_KIND_NONE, 0, 0, 0); }
	| EXTERN { $$ = make_type_spec("extern", "", TYPE_KIND_NONE, 0, 0, 0); }
	| STATIC { $$ = make_type_spec("static", "", TYPE_KIND_NONE, 0, 0, 0); }
	| THREAD_LOCAL { $$ = make_type_spec("thread_local", "", TYPE_KIND_NONE, 0, 0, 0); }
	| AUTO { $$ = make_type_spec("auto", "", TYPE_KIND_NONE, 0, 0, 0); }
	| REGISTER { $$ = make_type_spec("register", "", TYPE_KIND_NONE, 0, 0, 0); }
	| CONSTEXPR { $$ = make_type_spec("constexpr", "", TYPE_KIND_NONE, 0, 0, 0); }
	| alignas_prefix constant_expression ')' {
		char *s;
		pop_state(scanner);
		safe_asprintf(&s, "alignas ( %s )", $2->text);
		$$ = make_type_spec(s, "", TYPE_KIND_NONE, 0, 0, 0);
		free(s);
		free_expr_info($2);
	}
	| alignas_prefix type_name ')' {
		char *s;
		pop_state(scanner);
		safe_asprintf(&s, "alignas ( %s )", $2.text);
		$$ = make_type_spec(s, "", TYPE_KIND_NONE, 0, 0, 0);
		free(s);
		free($2.text);
	}
	;

alignas_prefix
	: ALIGNAS { push_native_state(scanner); } '('
	;

type_name
	: specifier_qualifier_list {
		$$.simple_kind = simple_cast_kind($1, 0);
		$$.text = $1.full;
		free($1.stripped);
	}
	| specifier_qualifier_list abstract_declarator {
		$$.simple_kind = simple_cast_kind($1, 1);
		safe_asprintf(&$$.text, "%s %s", $1.full, $2);
		free($1.full);
		free($1.stripped);
		free($2);
	}
	;

type_specifier_atomic
	: TYPE_INT {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_INT, 1, 0, 0);
		free($1);
	}
	| TYPE_VOID {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_VOID, 1, 0, 0);
		free($1);
	}
	| TYPE_LONG {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_LONG, 1, 0, 0);
		free($1);
	}
	| TYPE_RUN_OBJ_T {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_RUN_OBJ_T, 1, 0, 0);
		free($1);
	}
	| STD_TYPE {
		register_type($1);
		$$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 0);
		free($1);
	}
	| TYPE_NAME { $$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 0); free($1); }
	| struct_or_union_specifier { $$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 1); free($1); }
	| enum_specifier { $$ = make_type_spec($1, $1, TYPE_KIND_OTHER, 1, 0, 0); free($1); }
	| TYPEOF '(' expression ')' {
		char *s;
		safe_asprintf(&s, "typeof ( %s )", $3->text);
		$$ = make_type_spec(s, s, TYPE_KIND_OTHER, 1, 0, 0);
		free(s);
		free_expr_info($3);
	}
	| TYPEOF '(' type_name ')' {
		char *s;
		safe_asprintf(&s, "typeof ( %s )", $3.text);
		$$ = make_type_spec(s, s, TYPE_KIND_OTHER, 1, 0, 0);
		free(s);
		free($3.text);
	}
	;

struct_or_union_specifier
	: struct_or_union any_id LBRACE { on_type_scope_enter(); } struct_declaration_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "%s %s { %s }", $1, $2, $5); free($1); free($2); free($5); }
	| struct_or_union LBRACE { on_type_scope_enter(); } struct_declaration_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "%s { %s }", $1, $4); free($1); free($4); }
	| struct_or_union any_id LBRACE { on_type_scope_enter(); on_type_scope_exit(); safe_asprintf(&$$, "%s %s { }", $1, $2); free($1); free($2); }
	| struct_or_union LBRACE { on_type_scope_enter(); on_type_scope_exit(); safe_asprintf(&$$, "%s { }", $1); free($1); }
	| struct_or_union any_id { register_type($2); safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

any_id
	: IDENTIFIER { $$ = $1; }
	| TYPE_NAME { $$ = $1; }
	| RECURSIVE_ID { $$ = $1; }
	| PRINTF { $$ = $1; }
	;

struct_or_union
	: STRUCT { $$ = strdup("struct"); }
	| UNION { $$ = strdup("union"); }
	;

struct_declaration_list
	: struct_declaration { $$ = $1; }
	| struct_declaration_list struct_declaration { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list_full ';' { safe_asprintf(&$$, "%s %s ;", $1.full, $2); free($1.full); free($1.stripped); free($2); }
	;

specifier_qualifier_list
	: specifier_qualifier { $$ = $1; }
	| specifier_qualifier_list specifier_qualifier { $$ = merge_type_specs($1, $2); }
	;

specifier_qualifier
	: type_specifier_atomic { $$ = $1; }
	| type_qualifier { $$ = $1; }
	;

struct_declarator_list_full
	: struct_declarator_full { $$ = $1; }
	| struct_declarator_list_full ',' struct_declarator_full { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

struct_declarator_full
	: declarator_full { $$ = $1; }
	| ':' { push_native_state(scanner); } constant_expression { pop_state(scanner); safe_asprintf(&$$, " : %s", $3->text); free_expr_info($3); }
	| declarator_full ':' { push_native_state(scanner); } constant_expression { pop_state(scanner); safe_asprintf(&$$, "%s : %s", $1, $4->text); free($1); free_expr_info($4); }
	;

enum_specifier
	: ENUM LBRACE { on_type_scope_enter(); } enumerator_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "enum { ... }"); free($4); }
	| ENUM any_id LBRACE { on_type_scope_enter(); } enumerator_list RBRACE { on_type_scope_exit(); safe_asprintf(&$$, "enum %s { ... }", $2); free($2); free($5); }
	| ENUM any_id { register_type($2); safe_asprintf(&$$, "enum %s", $2); free($2); }
	;

enumerator_list
	: enumerator { $$ = $1; }
	| enumerator_list ',' enumerator { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	| enumerator_list ',' { $$ = $1; }
	;

enumerator
	: any_id { $$ = $1; }
	| any_id { push_native_state(scanner); } '=' constant_expression { pop_state(scanner); safe_asprintf(&$$, "%s = %s", $1, $4->text); free($1); free_expr_info($4); }
	;

type_qualifier
	: CONST { $$ = make_type_spec("const", "const", TYPE_KIND_NONE, 0, 1, 0); }
	| VOLATILE { $$ = make_type_spec("volatile", "volatile", TYPE_KIND_NONE, 0, 1, 0); }
	| RESTRICT { $$ = make_type_spec("restrict", "restrict", TYPE_KIND_NONE, 0, 1, 0); }
	| INLINE { $$ = make_type_spec("inline", "", TYPE_KIND_NONE, 0, 0, 0); }
	;

init_declarator_list_full
	: init_declarator_full { $$ = $1; }
	| init_declarator_list_full ',' init_declarator_full { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

init_declarator_full
	: declarator_full { $$ = $1; }
	| declarator_full '=' initializer { safe_asprintf(&$$, "%s = %s", $1, $3); free($1); free($3); }
	;

function_declarator
	: pointer direct_declarator_full {
		safe_asprintf(&$$.text, "%s %s", $1, $2);
		$$.ptr_prefix = $1;
		free($2);
	}
	| direct_declarator_full {
		$$.text = $1;
		$$.ptr_prefix = strdup("");
	}
	;

declarator_full
	: pointer direct_declarator_full { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	| direct_declarator_full { $$ = $1; }
	;



direct_declarator_full
	: any_id { on_declarator($1); $$ = $1; }
	| '(' declarator_full ')' { safe_asprintf(&$$, "( %s )", $2); free($2); }
	| direct_declarator_full '[' bracket_static_expression ']' { safe_asprintf(&$$, "%s [ %s ]", $1, $3); free($1); free($3); }
	| direct_declarator_full '[' ']' { safe_asprintf(&$$, "%s [ ]", $1); free($1); }
	| direct_declarator_full '(' { save_func_name($1); } parameter_type_list ')' { safe_asprintf(&$$, "%s ( %s )", $1, $4); free($1); free($4); }
	| direct_declarator_full '(' { save_func_name($1); } identifier_list ')' { safe_asprintf(&$$, "%s ( %s )", $1, $4); free($1); free($4); }
	| direct_declarator_full '(' ')' { save_func_name($1); safe_asprintf(&$$, "%s ( )", $1); free($1); }
	;

bracket_static_expression
	: { push_native_state(scanner); } assignment_expression { pop_state(scanner); $$ = strdup($2->text); free_expr_info($2); }
	;


pointer
	: '*' { $$ = strdup("*"); }
	| RUN_CC_MUL { $$ = strdup("*"); }
	| '*' type_qualifier_list { safe_asprintf(&$$, "* %s", $2); free($2); }
	| RUN_CC_MUL type_qualifier_list { safe_asprintf(&$$, "* %s", $2); free($2); }
	| '*' pointer { safe_asprintf(&$$, "* %s", $2); free($2); }
	| RUN_CC_MUL pointer { safe_asprintf(&$$, "* %s", $2); free($2); }
	| '*' type_qualifier_list pointer { safe_asprintf(&$$, "* %s %s", $2, $3); free($2); free($3); }
	| RUN_CC_MUL type_qualifier_list pointer { safe_asprintf(&$$, "* %s %s", $2, $3); free($2); free($3); }
	;

type_qualifier_list
	: type_qualifier { $$ = $1.full; free($1.stripped); }
	| type_qualifier_list type_qualifier { safe_asprintf(&$$, "%s %s", $1, $2.full); free($1); free($2.full); free($2.stripped); }
	;

parameter_type_list
	: parameter_list { $$ = $1; }
	| parameter_list ',' ELLIPSIS { safe_asprintf(&$$, "%s , ...", $1); free($1); }
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list ',' parameter_declaration { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

parameter_declaration
	: declaration_specifiers declarator_full { safe_asprintf(&$$, "%s %s", $1.full, $2); add_param(last_id, $$, $1.stripped, $1.has_struct_union); free($1.full); free($1.stripped); free($2); }
	| declaration_specifiers abstract_declarator { safe_asprintf(&$$, "%s %s", $1.full, $2); free($1.full); free($1.stripped); free($2); }
	| declaration_specifiers { $$ = $1.full; free($1.stripped); }
	;

identifier_list
	: any_id { $$ = $1; }
	| identifier_list ',' any_id { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	;

initializer
	: assignment_expression { $$ = strdup($1->text); free_expr_info($1); }
	| LBRACE RBRACE { $$ = strdup("{ }"); }
	| LBRACE initializer_list RBRACE { safe_asprintf(&$$, "{ %s }", $2); free($2); }
	| LBRACE initializer_list ',' RBRACE { safe_asprintf(&$$, "{ %s , }", $2); free($2); }
	;

initializer_list
	: initializer { $$ = $1; }
	| designation initializer { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	| initializer_list ',' initializer { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	| initializer_list ',' designation initializer { safe_asprintf(&$$, "%s , %s %s", $1, $3, $4); free($1); free($3); free($4); }
	;

designation
	: designator_list '=' { $$ = $1; }
	;

designator_list
	: designator { $$ = $1; }
	| designator_list designator { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

designator
	: { push_native_state(scanner); } '[' constant_expression { pop_state(scanner); } ']' { safe_asprintf(&$$, "[ %s ]", $3->text); free_expr_info($3); }
	| '.' any_id { safe_asprintf(&$$, ". %s", $2); free($2); }
	;

abstract_declarator
	: pointer { $$ = $1; }
	| direct_abstract_declarator { $$ = $1; }
	| pointer direct_abstract_declarator { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { safe_asprintf(&$$, "( %s )", $2); free($2); }
	| '[' ']' { $$ = strdup("[ ]"); }
	| '[' constant_expression ']' { safe_asprintf(&$$, "[ %s ]", $2->text); free_expr_info($2); }
	| direct_abstract_declarator '[' ']' { safe_asprintf(&$$, "%s [ ]", $1); free($1); }
	| direct_abstract_declarator '[' constant_expression ']' { safe_asprintf(&$$, "%s [ %s ]", $1, $3->text); free($1); free_expr_info($3); }
	| '(' ')' { $$ = strdup("( )"); }
	| '(' parameter_type_list ')' { safe_asprintf(&$$, "( %s )", $2); free($2); }
	| direct_abstract_declarator '(' ')' { safe_asprintf(&$$, "%s ( )", $1); free($1); }
	| direct_abstract_declarator '(' parameter_type_list ')' { safe_asprintf(&$$, "%s ( %s )", $1, $3); free($1); free($3); }
	;

/* Statements */
statement_list
	: statement
	| statement_list statement
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: label statement
	| label
	;

label
	: attribute_specifier_list IDENTIFIER ':' { safe_asprintf(&$$, "%s %s :", $1, $2); print_str($$); print_str(" "); free($1); free($2); }
	| IDENTIFIER ':' { safe_asprintf(&$$, "%s :", $1); print_str($$); print_str(" "); free($1); }
	| attribute_specifier_list CASE { push_native_state(scanner); } constant_expression { pop_state(scanner); } ':' { safe_asprintf(&$$, "%s case %s :", $1, $4->text); print_str($$); print_str(" "); free($1); free_expr_info($4); }
	| CASE { push_native_state(scanner); } constant_expression { pop_state(scanner); } ':' { safe_asprintf(&$$, "case %s :", $3->text); print_str($$); print_str(" "); free_expr_info($3); }
	| attribute_specifier_list DEFAULT ':' { safe_asprintf(&$$, "%s default :", $1); print_str($$); print_str(" "); free($1); }
	| DEFAULT ':' { print_str("default : "); $$ = strdup("default :"); }
	;

compound_statement
	: LBRACE RBRACE { print_str("{ }"); }
	| LBRACE { print_str("{ "); } block_item_list RBRACE { print_str(" }"); }
	;

expression_statement
	: ';' { print_str("; "); }
	| expression ';' { print_str($1->text); print_str(" ; "); free_expr_info($1); }
	;

for_expression_opt
	: %empty { print_str(" "); }
	| expression { print_str($1->text); print_str(" "); free_expr_info($1); }
	;

for_init_clause
	: for_expression_opt
	| declaration_specifiers init_declarator_list_full { print_str($1.full); print_str(" "); print_str($2); free($1.full); free($1.stripped); free($2); }
	;

if_prefix
	: IF '(' expression ')' { start_buffering(); $$ = $3; }
	;
 
 while_prefix
 	: WHILE '(' expression ')' { start_buffering(); $$ = $3; }
 	;

for_prefix
	: FOR { start_buffering(); }
	;

selection_statement
	: if_prefix statement {
		char *stmt = stop_buffering();
		print_str("if ( "); print_str($1->text); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free_expr_info($1);
	}
	| if_prefix statement ELSE { start_buffering(); } statement {
		char *stmt_else = stop_buffering();
		char *stmt_if = stop_buffering();
		print_str("if ( "); print_str($1->text); print_str(" ) ");
		if (stmt_if) { print_str(stmt_if); free(stmt_if); }
		print_str(" else ");
		if (stmt_else) { print_str(stmt_else); free(stmt_else); }
		free_expr_info($1);
	}
    | IFTE '(' expression ',' expression ',' expression ')' {
        print_str("ifte ( "); print_str($3->text); print_str(" , ");
        print_str($5->text); print_str(" , "); print_str($7->text); print_str(" ) ");
        free_expr_info($3); free_expr_info($5); free_expr_info($7);
    }
    | RUN_CC_IFTE '(' expression ',' expression ',' expression ')' {
        print_str("ifte ( "); print_str($3->text); print_str(" , ");
        print_str($5->text); print_str(" , "); print_str($7->text); print_str(" ) ");
        free_expr_info($3); free_expr_info($5); free_expr_info($7);
    }
	| SWITCH '(' expression ')' { start_buffering(); } statement {
		char *stmt = stop_buffering();
		print_str("switch ( "); print_str($3->text); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free_expr_info($3);
	}
	;

iteration_statement
	: while_prefix statement {
		char *stmt = stop_buffering();
		print_str("while ( "); print_str($1->text); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free_expr_info($1);
	}
	| DO { start_buffering(); } statement WHILE '(' expression ')' ';' {
		char *stmt = stop_buffering();
		print_str("do ");
		if (stmt) { print_str(stmt); free(stmt); }
		print_str(" while ( "); print_str($6->text); print_str(" ) ; ");
		free_expr_info($6);
	}
	| for_prefix '(' for_init_clause ';' { print_str("; "); } for_expression_opt ';' { print_str("; "); } for_expression_opt ')' {
		$<str>$ = stop_buffering();
		start_buffering();
	  } statement {
		char *stmt = stop_buffering();
		print_str("for ( "); print_str($<str>11); print_str(" ) ");
		if (stmt) { print_str(stmt); free(stmt); }
		free($<str>11);
	}
	;

jump_statement
	: GOTO IDENTIFIER ';' { print_str("goto "); print_str($2); print_str(" ; "); free($2); }
	| CONTINUE ';' { print_str("continue ; "); }
	| BREAK ';' { print_str("break ; "); }
	| RETURN ';' { if (!should_emit_run()) print_str("return ; "); action_return_empty(); }
	| RETURN expression ';' { if (!should_emit_run()) { print_str("return "); print_str($2->text); print_str(" ; "); } action_return_expr($2); }
	;

/* Expressions */
generic_identifier
	: IDENTIFIER { $$ = $1; }
	| RECURSIVE_ID { $$ = $1; }
	;

recursive_call
	: RECURSIVE_ID '(' argument_expression_list ')' {
        suppress_recursive_original = 1;
		ExprInfo *e = new_recursive_call_info($1, $3->text);
		$$ = e;
		free($1); free_expr_info($3);
	}
	| RECURSIVE_ID '(' ')' {
        suppress_recursive_original = 1;
		ExprInfo *e = new_recursive_call_info($1, "");
		$$ = e;
		free($1);
	}
	;

primary_expression
	: recursive_call { $$ = $1; }
	| generic_identifier { $$ = new_expr_info($1); free($1); }
	| PRINTF {
		ExprInfo *e = new_expr_info($1);
		e->is_printf = 1;
		$$ = e;
		free($1);
	}
	| CONSTANT {
		if (run_mode && is_native_context() && !needs_run_nat && !needs_run_bool) {
			char *s;
			safe_asprintf(&s, "( %s )", $1);
			$$ = new_expr_info(s);
			free(s);
		} else {
			$$ = new_expr_info($1);
		}
		free($1);
	}
	| string_literal_sequence { $$ = new_expr_info($1); free($1); }
	| '(' expression ')' { 
		char *s; safe_asprintf(&s, "( %s )", $2->text); 
		$$ = new_expr_info(s); free(s); 
		free_expr_info($2); 
	}
	| pavlovic_operator {
			ExprInfo *e = new_expr_info($1);
			e->is_morphism = 1;
			$$ = e;
			free($1);
		}
    | OFFSETOF '(' TYPE_NAME ',' IDENTIFIER ')' {
        char *s; safe_asprintf(&s, "__builtin_offsetof ( %s , %s )", $3, $5);
        $$ = new_expr_info(s); free(s); free($3); free($5);
    }
	;

pavlovic_operator
	: RUN { $$ = $1; }
	| IDENTITY { $$ = $1; }
	| SWAP { $$ = $1; }
	| COPY { $$ = $1; }
	| DELETE { $$ = $1; }
	| SEQUENTIAL { $$ = $1; }
	| PARALLEL { $$ = $1; }
	| PARTIAL { $$ = $1; }
	;

string_literal_sequence
	: STRING_LITERAL { $$ = $1; }
	| string_literal_sequence STRING_LITERAL { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression { push_native_state(scanner); } '[' expression { pop_state(scanner); } ']' { 
		char *s; safe_asprintf(&s, "%s [ %s ]", $1->text, $4->text);
        if (should_emit_run() && $1->is_morphism) {
            $$ = reduce_axiom_string(s, scanner);
            if ($$) {
                free(s); free_expr_info($1); free_expr_info($4);
            } else {
                $$ = new_expr_info(s); free(s);
                free_expr_info($1); free_expr_info($4);
            }
        } else {
		    $$ = new_expr_info(s); free(s);
            free_expr_info($1); free_expr_info($4);
        }
	}
	| postfix_expression '(' ')' { 
		char *s; safe_asprintf(&s, "%s ( )", $1->text);
        if (should_emit_run() && $1->is_morphism) {
            $$ = reduce_axiom_string(s, scanner);
            if ($$) {
                free(s); free_expr_info($1);
            } else {
                ExprInfo *e = new_expr_info(s);
                e->is_call = 1;
                e->is_printf = $1->is_printf;
                e->func_name = strdup($1->text);
                e->args = strdup("");
                $$ = e;
                free(s);
                free_expr_info($1);
            }
        } else {
		    ExprInfo *e = new_expr_info(s);
		    e->is_call = 1;
		    e->is_printf = $1->is_printf;
		    e->func_name = strdup($1->text);
		    e->args = strdup("");
		    $$ = e;
            free(s);
            free_expr_info($1);
        }
	}

	| postfix_expression '(' argument_expression_list ')' { 
		char *args = NULL;
		const char *args_text = $3->text;
		if (should_emit_run() && $1->is_printf) {
			args = adjust_printf_args($3->text);
			if (args)
				args_text = args;
		}
		char *s; safe_asprintf(&s, "%s ( %s )", $1->text, args_text);
        if (should_emit_run() && $1->is_morphism) {
            $$ = reduce_axiom_string(s, scanner);
            if ($$) {
                free(s); free_expr_info($1); free_expr_info($3);
            } else {
                ExprInfo *e = new_expr_info(s);
                e->is_call = 1;
                e->is_printf = $1->is_printf;
                e->func_name = strdup($1->text);
                e->args = strdup(args_text);
                $$ = e;
                free(s);
                free_expr_info($1);
                free_expr_info($3);
            }
        } else {
		    ExprInfo *e = new_expr_info(s);
		    e->is_call = 1;
		    e->is_printf = $1->is_printf;
		    e->func_name = strdup($1->text);
		    e->args = strdup(args_text);
		    $$ = e;
            free(s);
            free_expr_info($1);
            free_expr_info($3);
        }
		if (args)
			free(args);
	}
	| postfix_expression '.' any_id { 
		char *s; safe_asprintf(&s, "%s . %s", $1->text, $3);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free($3);
	}
	| postfix_expression PTR_OP any_id { 
		char *s; safe_asprintf(&s, "%s -> %s", $1->text, $3);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free($3);
	}
	| postfix_expression INC_OP { 
		char *s; safe_asprintf(&s, "%s ++", $1->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1);
	}
	| postfix_expression DEC_OP { 
		char *s; safe_asprintf(&s, "%s --", $1->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1);
	}
	;

argument_expression_list
	: assignment_expression { $$ = $1; }
	| argument_expression_list ',' assignment_expression { 
		char *s; safe_asprintf(&s, "%s , %s", $1->text, $3->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free_expr_info($3);
	}
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { 
		char *s; safe_asprintf(&s, "++ %s", $2->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($2);
	}
	| DEC_OP unary_expression { 
		char *s; safe_asprintf(&s, "-- %s", $2->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($2);
	}
	| '&' cast_expression { $$ = make_op_1("&", NULL, $2); }
	| '*' cast_expression { $$ = make_op_1("*", NULL, $2); }
	| RUN_CC_MUL cast_expression { $$ = make_op_1("*", NULL, $2); }
	| '+' cast_expression { $$ = make_op_1("+", NULL, $2); }
	| RUN_CC_ADD cast_expression { $$ = make_op_1("+", NULL, $2); }
	| '-' cast_expression { $$ = make_op_1("-", "run_cc_neg", $2); }
	| RUN_CC_SUB cast_expression { $$ = make_op_1("-", "run_cc_neg", $2); }
	| '~' cast_expression { $$ = make_op_1("~", NULL, $2); }
	| '!' cast_expression { $$ = make_op_1("!", NULL, $2); }
	| RUN_CC_NOT cast_expression { $$ = make_run_bool_not($2); }
	| SIZEOF unary_expression { 
		char *s; safe_asprintf(&s, "sizeof ( %s )", $2->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($2);
	}
	| SIZEOF '(' type_name ')' { 
		char *s; safe_asprintf(&s, "sizeof ( %s )", $3.text);
		$$ = new_expr_info(s); free(s);
		free($3.text);
	}
	| ALIGNOF '(' type_name ')' { 
		char *s; safe_asprintf(&s, "alignof ( %s )", $3.text);
		$$ = new_expr_info(s); free(s);
		free($3.text);
	}
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression { 
		char *s;
		TypeKind ret_kind = TYPE_KIND_NONE;
		int drop_cast = 0;
		if ($4->is_call && $4->func_name)
			ret_kind = lookup_function_return_kind($4->func_name);
		if (is_native_context() &&
		    ($2.simple_kind == SIMPLE_CAST_INT ||
		     $2.simple_kind == SIMPLE_CAST_LONG) &&
		    (ret_kind == TYPE_KIND_INT || ret_kind == TYPE_KIND_LONG)) {
			drop_cast = 1;
		}

		if (should_emit_run() && $2.simple_kind != SIMPLE_CAST_NONE) {
			if ($2.simple_kind == SIMPLE_CAST_RUN_OBJ_T && run_mode) {
				safe_asprintf(&s, "( %s ) %s", $2.text, $4->text);
			} else if (is_native_context()) {
				if (drop_cast)
					safe_asprintf(&s, "%s", $4->text);
				else
					safe_asprintf(&s, "( %s ) %s", $2.text, $4->text);
			} else {
				if (verbose)
					fprintf(stderr, "DEBUG: Casting %s to nat_to_int\n", $4->text);
				needs_run_nat = 1;
				needs_run_bool = 1;
				safe_asprintf(&s, " nat_to_int ( %s ) ", $4->text);
			}
		} else {
			safe_asprintf(&s, "( %s ) %s", $2.text, $4->text);
		}
		$$ = new_expr_info(s); free(s);
		free($2.text); free_expr_info($4);
	}
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = make_op_2("*", NULL, 0, 0, $1, $3); }
	| multiplicative_expression '/' cast_expression { $$ = make_op_2("/", NULL, 0, 0, $1, $3); }
	| multiplicative_expression '%' cast_expression { $$ = make_op_2("%", NULL, 0, 0, $1, $3); }
	| multiplicative_expression RUN_CC_MUL cast_expression { $$ = make_nat_mult($1, $3); }
	| multiplicative_expression RUN_CC_DIV cast_expression { $$ = make_op_2("/", "run_cc_div", 0, 0, $1, $3); }
	| multiplicative_expression RUN_CC_MOD cast_expression { $$ = make_op_2("%", "run_cc_mod", 0, 0, $1, $3); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = make_op_2("+", NULL, 0, 0, $1, $3); }
	| additive_expression '-' multiplicative_expression { $$ = make_op_2("-", NULL, 0, 0, $1, $3); }
	| additive_expression RUN_CC_ADD multiplicative_expression { $$ = make_nat_add($1, $3); }
	| additive_expression RUN_CC_SUB multiplicative_expression { $$ = make_op_2("-", "run_cc_sub", 0, 0, $1, $3); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = make_op_2("<<", NULL, 0, 0, $1, $3); }
	| shift_expression RIGHT_OP additive_expression { $$ = make_op_2(">>", NULL, 0, 0, $1, $3); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = make_op_2("<", NULL, 0, 0, $1, $3); }
	| relational_expression '>' shift_expression { $$ = make_op_2(">", NULL, 0, 0, $1, $3); }
	| relational_expression LE_OP shift_expression { $$ = make_op_2("<=", NULL, 0, 0, $1, $3); }
	| relational_expression GE_OP shift_expression { $$ = make_op_2(">=", NULL, 0, 0, $1, $3); }
	| relational_expression RUN_CC_LT shift_expression { $$ = make_op_2("<", "run_cc_lt", 0, 0, $1, $3); }
	| relational_expression RUN_CC_GT shift_expression { $$ = make_op_2(">", "run_cc_gt", 0, 0, $1, $3); }
	| relational_expression RUN_CC_LE shift_expression { $$ = make_op_2("<=", "run_cc_le", 0, 0, $1, $3); }
	| relational_expression RUN_CC_GE shift_expression { $$ = make_op_2(">=", "run_cc_ge", 0, 0, $1, $3); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = make_op_2("==", NULL, 0, 0, $1, $3); }
	| equality_expression NE_OP relational_expression { $$ = make_op_2("!=", NULL, 0, 0, $1, $3); }
	| equality_expression RUN_CC_EQ relational_expression { $$ = make_run_iseq($1, $3); }
	| equality_expression RUN_CC_NE relational_expression { 
        ExprInfo *eq = make_run_iseq($1, $3);
        $$ = make_run_bool_not(eq);
    }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = make_op_2("&", NULL, 0, 0, $1, $3); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ = make_op_2("^", NULL, 0, 0, $1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = make_op_2("|", NULL, 0, 0, $1, $3); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression {
		if (run_mode && is_native_context()) {
			$$ = make_op_2("&&", NULL, 0, 0, $1, $3);
		} else {
			$$ = make_op_2("&&", "run_cc_and", 0, 0, $1, $3);
		}
	}
	| logical_and_expression RUN_CC_AND inclusive_or_expression { $$ = make_op_2("&&", "run_cc_and", 0, 0, $1, $3); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression {
		if (run_mode && is_native_context()) {
			$$ = make_op_2("||", NULL, 0, 0, $1, $3);
		} else {
			$$ = make_op_2("||", "run_cc_or", 0, 0, $1, $3);
		}
	}
	| logical_or_expression RUN_CC_OR logical_and_expression { $$ = make_op_2("||", "run_cc_or", 0, 0, $1, $3); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression {
		char *s;
		if (should_emit_run()) {
			safe_asprintf(&s, "(( %s ) ? ( %s ) : ( %s ))", $1->text, $3->text, $5->text);
		} else {
			safe_asprintf(&s, "%s ? %s : %s", $1->text, $3->text, $5->text);
		}
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free_expr_info($3); free_expr_info($5);
	}
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { 
		char *s; safe_asprintf(&s, "%s %s %s", $1->text, $2, $3->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free($2); free_expr_info($3);
	}
	;

assignment_operator
	: '=' { $$ = strdup("="); }
	| MUL_ASSIGN { $$ = strdup("*="); }
	| DIV_ASSIGN { $$ = strdup("/="); }
	| MOD_ASSIGN { $$ = strdup("%="); }
	| ADD_ASSIGN { $$ = strdup("+="); }
	| SUB_ASSIGN { $$ = strdup("-="); }
	| LEFT_ASSIGN { $$ = strdup("<<="); }
	| RIGHT_ASSIGN { $$ = strdup(">>="); }
	| AND_ASSIGN { $$ = strdup("&="); }
	| XOR_ASSIGN { $$ = strdup("^="); }
	| OR_ASSIGN { $$ = strdup("|="); }
	;

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression { 
		char *s; safe_asprintf(&s, "%s , %s", $1->text, $3->text);
		$$ = new_expr_info(s); free(s);
		free_expr_info($1); free_expr_info($3);
	}
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

/* Attributes */
attribute_specifier_list
	: attribute_specifier { $$ = $1; }
	| attribute_specifier_list attribute_specifier { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

attribute_specifier_list_opt
	: %empty { $$ = NULL; }
	| attribute_specifier_list { $$ = $1; }
	;

attribute_specifier
	: LEFT_BRACKET_BRACKET attribute_list RIGHT_BRACKET_BRACKET { safe_asprintf(&$$, "[[ %s ]]", $2); free($2); }
	;

attribute_list
	: attribute { $$ = $1; }
	| attribute_list ',' attribute { safe_asprintf(&$$, "%s , %s", $1, $3); free($1); free($3); }
	| attribute_list ',' { safe_asprintf(&$$, "%s , ", $1); free($1); }
	| %empty { $$ = strdup(""); }
	;

attribute
	: attribute_token attribute_argument_clause_opt { safe_asprintf(&$$, "%s %s", $1, $2); free($1); free($2); }
	;

attribute_token
	: IDENTIFIER { $$ = $1; }
	| attribute_scoped_token { $$ = $1; }
	;

attribute_scoped_token
	: IDENTIFIER ':' ':' IDENTIFIER { safe_asprintf(&$$, "%s :: %s", $1, $4); free($1); free($4); }
	;

attribute_argument_clause_opt
	: %empty { $$ = strdup(""); }
	| '(' argument_expression_list ')' { safe_asprintf(&$$, "( %s )", $2->text); free_expr_info($2); }
	;


/* Val.y rules */


val_start:
    val_axiom { if (callback) callback($1); }
    ;

val_axiom:
    arithmetic_axiom { $$ = $1; }
  | logic_axiom { $$ = $1; }
  | categorical_axiom { $$ = $1; }
  | '(' val_axiom ')' { $$ = $2; }
  ;

arithmetic_axiom:
      '+' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) + (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
      }
    | '-' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) - (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '*' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) * (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '/' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) / (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '%' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) %% (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '&' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) & (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '|' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) | (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '^' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) ^ (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '~' '(' val_axiom ')' {
        char *s; safe_asprintf(&s, "(~(%s))", $3->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3);
    }
    | RUN_CC_CONSTANT '(' val_axiom ')' {
        char *s; safe_asprintf(&s, "(%s)", $3->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3);
    }
    ;

logic_axiom:
      '>' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) > (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
      }
    | '<' '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) < (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | GE_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) >= (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | LE_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) <= (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | EQ_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) == (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | NE_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) != (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | AND_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) && (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | OR_OP '(' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "((%s) || (%s))", $3->text, $5->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5);
    }
    | '!' '(' val_axiom ')' {
        char *s; safe_asprintf(&s, "(!(%s))", $3->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3);
    }
categorical_axiom:
      morphism_kind { $$ = new_expr_info($1.lexeme); free($1.lexeme); }
    | morphism_kind '(' val_list ')' { $$ = apply_morphism_kind($1.kind, $3); free($1.lexeme); }
    | morphism_kind '[' val_list ']' { $$ = apply_morphism_kind($1.kind, $3); free($1.lexeme); }
    | morphism_kind '(' ')' { $$ = new_expr_info($1.lexeme); free($1.lexeme); }
    | morphism_kind '[' ']' { $$ = new_expr_info($1.lexeme); free($1.lexeme); }
    | IFTE '(' val_axiom ',' val_axiom ',' val_axiom ')' {
        char *s; safe_asprintf(&s, "ifte ( %s , %s , %s )", $3->text, $5->text, $7->text);
        $$ = new_expr_info(s); free(s);
        free_expr_info($3); free_expr_info($5); free_expr_info($7);
    }
    | any_val_id '(' val_list ')' { $$ = apply_generic_call($1, $3); free($1); }
    | any_val_id '[' val_list ']' { $$ = apply_generic_call($1, $3); free($1); }
    | any_val_id '(' ')' { $$ = apply_generic_call($1, NULL); free($1); }
    | any_val_id '[' ']' { $$ = apply_generic_call($1, NULL); free($1); }
    | any_val_id { $$ = new_expr_info($1); free($1); }
    | CONSTANT   { $$ = new_expr_info($1); free($1); }
    | STRING_LITERAL { $$ = new_expr_info($1); free($1); }
    ;

any_val_id:
      IDENTIFIER | TYPE_NAME | RECURSIVE_ID
    ;

morphism_kind:
      RUN { $$.kind = MORPH_RUN; $$.lexeme = $1; }
    | EVAL { $$.kind = MORPH_EVAL; $$.lexeme = $1; }
    | COMPUTE { $$.kind = MORPH_COMPUTE; $$.lexeme = $1; }
    | PROGRAM { $$.kind = MORPH_PROGRAM; $$.lexeme = $1; }
    | DATA { $$.kind = MORPH_DATA; $$.lexeme = $1; }
    | IDEMPOTENT { $$.kind = MORPH_IDEMPOTENT; $$.lexeme = $1; }
    | SWAP { $$.kind = MORPH_SWAP; $$.lexeme = $1; }
    | COPY { $$.kind = MORPH_COPY; $$.lexeme = $1; }
    | DELETE { $$.kind = MORPH_DELETE; $$.lexeme = $1; }
    | FUNCTION { $$.kind = MORPH_FUNCTION; $$.lexeme = $1; }
    | PROCESS { $$.kind = MORPH_PROCESS; $$.lexeme = $1; }
    | SEQUENTIAL { $$.kind = MORPH_SEQUENTIAL; $$.lexeme = $1; }
    | PARALLEL { $$.kind = MORPH_PARALLEL; $$.lexeme = $1; }
    | PARTIAL { $$.kind = MORPH_PARTIAL; $$.lexeme = $1; }
    | FIXPOINT { $$.kind = MORPH_FIXPOINT; $$.lexeme = $1; }
    | KLEENE { $$.kind = MORPH_KLEENE; $$.lexeme = $1; }
    | IDENTITY { $$.kind = MORPH_IDENTITY; $$.lexeme = $1; }
    | ISEQ { $$.kind = MORPH_ISEQ; $$.lexeme = $1; }
    | RHO { $$.kind = MORPH_RHO; $$.lexeme = $1; }
    | BOOL_VALUE { $$.kind = MORPH_BOOL_VALUE; $$.lexeme = $1; }
    ;

val_list:
      val_axiom { $$ = new_expr_list($1, NULL); }
    | val_axiom ',' val_list { $$ = new_expr_list($1, $3); }
    ;


%%
