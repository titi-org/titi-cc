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
#include <x86intrin.h>
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
