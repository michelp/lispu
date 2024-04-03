#include "lisp.h"

x_any x_eq(x_any args) {
  x_any a, b;
  a = car(args);
  b = cadr(args);

  if (a == b)
    return x_env.true_;
  else if (are_symbols(a, b)) {
    if (strcmp(sval(a), sval(b)) == 0)
      return x_env.true_;
  }
  else if (are_ints(a, b)) {
    if (ival(a) == ival(b))
      return x_env.true_;
  }
  else if (are_doubles(a, b)) {
    if (dval(a) == dval(b))
      return x_env.true_;
  }
  else if (are_strs(a, b)) {
    if (strcmp(sval(a), sval(b)) == 0)
      return x_env.true_;
  }
  else if (are_pairs(a, b)) {
    do {
      if (x_eq(TWO_ARG(car(a), car(b))) == x_env.nil)
        return x_env.nil;
      a = cdr(a);
      b = cdr(b);
    } while (are_pairs(a, b));
    if (x_eq(TWO_ARG(a, b)) != x_env.nil)
      return x_env.true_;
  }
  return x_env.nil;
}

x_any x_neq(x_any args) {
  x_any a, b;
  a = car(args);
  b = cadr(args);
  if (x_eq(TWO_ARG(a, b)) == x_env.true_)
    return x_env.nil;
  return x_env.true_;
}

x_any x_gt(x_any args) {
  x_any a, b;
  a = car(args);
  b = cadr(args);
  if (are_ints(a, b)) {
    if (ival(a) > ival(b))
      return x_env.true_;
  }
  else if (are_doubles(a, b)) {
    if (dval(a) > dval(b))
      return x_env.true_;
  }
  else if (are_strs(a, b)) {
    if (strcmp(sval(a), sval(b)) > 0)
      return x_env.true_;
  }
  return x_env.nil;
}

x_any x_lt(x_any args) {
  x_any a, b;
  a = car(args);
  b = cadr(args);
  if (are_ints(a, b)) {
    if (ival(a) < ival(b))
      return x_env.true_;
  }
  else if (are_doubles(a, b)) {
    if (dval(a) < dval(b))
      return x_env.true_;
  }
  else if (are_strs(a, b)) {
    if (strcmp(sval(a), sval(b)) < 0)
      return x_env.true_;
  }
  return x_env.nil;
}

x_any x_gte(x_any args) {
  x_any a, b;
  a = car(args);
  b = cadr(args);
  if (are_ints(a, b)) {
    if (ival(a) > ival(b))
      return x_env.true_;
  }
  else if (are_doubles(a, b)) {
    if (dval(a) > dval(b))
      return x_env.true_;
  }
  else if (are_strs(a, b)) {
    if (strcmp(sval(a), sval(b)) > 0)
      return x_env.true_;
  }
  return x_env.nil;
}

x_any x_lte(x_any args) {
  x_any a, b;
  a = car(args);
  b = cadr(args);
  if (are_ints(a, b)) {
    if (ival(a) < ival(b))
      return x_env.true_;
  }
  else if (are_doubles(a, b)) {
    if (dval(a) < dval(b))
      return x_env.true_;
  }
  else if (are_strs(a, b)) {
    if (strcmp(sval(a), sval(b)) < 0)
      return x_env.true_;
  }
  return x_env.nil;
}
