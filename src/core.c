#include <sys/time.h>
#include "lisp.h"

x_any x_is(x_any args) {
  if (car(args) == cadr(args))
    return x_env.true_;
  return x_env.nil;
}

x_any x_isinstance(x_any args) {
  x_any a, b;
  a = car(args);
  b = cadr(args);
  do {
    a = type(a);
    if (a == b)
      return x_env.true_;
  } while(a != x_env.symbol);
  return x_env.nil;
}

x_any x_type(x_any args) {
  return car(args)->type;
}

x_any x_assert(x_any args) {
  x_any cell;
  cell = car(args);
  assert(cell != x_env.nil);
  return cell;
}

x_any x_asserteq(x_any args) {
  assert(x_eq(args) != x_env.nil);
  return x_env.true_;
}

x_any x_car(x_any args) {
  x_any cell;
  cell = car(args);
  assert(is_pair(cell) || is_user(cell));
  return car(cell);
}

x_any x_cdr(x_any args) {
  x_any cell;
  cell = car(args);
  assert(is_pair(cell) || is_user(cell));
  return cdr(cell);
}

x_any cons(x_any a, x_any b) {
  x_any cell;
  cell = new_cell(NULL, x_env.pair);
  set_car(cell, a);
  set_cdr(cell, b);
  return cell;
}

x_any x_cons(x_any args) {
  return cons(car(args), cadr(args));
}

x_any x_list(x_any args) {
  return args;
}

x_any x_apply(x_any args) {
  x_any cell, fargs, expr, result;
  cell = car(args);
  fargs = cdr(args);
  if (is_special(cell))
    return ((x_fn)val(cell))(fargs);

  fargs = eval_list(fargs);
  if (is_fn(cell))
    return ((x_fn)val(cell))(fargs);

  else if (is_user(cell) || is_pair(cell)) {
    expr = car(cell);
    assert(length(fargs) == length(expr));
    push_frame();

    do {
      local(sval(car(expr)), car(fargs));
      expr = cdr(expr);
      fargs = cdr(fargs);
    } while(expr != x_env.nil);

    expr = cdr(cell);
    do {
      result = eval(car(expr));
      expr = cdr(expr);
    } while (expr != x_env.nil);
    pop_frame();
    return result;
  }
  else if (is_symbol(cell) || is_int(cell))
    return cons(cell, fargs);
  else
    assert(0);
  return x_env.nil;
}

x_any x_quote(x_any args) {
  return car(args);
}

x_any eval_symbol(x_any sym) {
  char* name;
  x_any cell;
  name = sval(sym);
  assert(name != NULL);
  if (isdigit(name[0]) || (name[0] == '-' && isdigit(name[1]))) {
    if (strchr(name, '.') == NULL)
      return new_int(strtoll(name, NULL, 0));
    else
      return new_double(strtod(name, NULL));
  }
  cell = lookup(name, -1);
  if (cell == NULL)
    return sym;
  return car(cell);
}

x_any eval_list(x_any cell) {
  if (cell == x_env.nil)
    return x_env.nil;
  else if (is_symbol(cell))
    return eval_symbol(cell);
  else if (is_atom(cell))
    return cell;
  else
    return cons(eval(car(cell)), eval_list(cdr(cell)));
}

x_any x_eval(x_any args) {
  return eval(car(args));
}

x_any eval(x_any cell) {
  x_any temp;
  if (is_symbol(cell))
      return eval_symbol(cell);
  else if (is_atom(cell))
    return cell;
  else if (is_pair(cell)) {
    temp = eval(car(cell));
    if (is_func(temp))
      return x_apply(cons(temp, cdr(cell)));
    else
      return cons(temp, eval_list(cdr(cell)));
  }
  assert(0);
  return x_env.nil;
}

x_any x_not(x_any args) {
  if (car(args) == x_env.nil)
    return x_env.true_;
  return x_env.nil;
}

x_any x_and(x_any args) {
  if (car(args) != x_env.nil && cadr(args) != x_env.nil)
    return x_env.true_;
  return x_env.nil;
}

x_any x_or(x_any args) {
  if (car(args) != x_env.nil || cadr(args) != x_env.nil)
    return x_env.true_;
  return x_env.nil;
}

x_any x_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return new_int((tv.tv_sec * 1000) + tv.tv_usec);
}

x_any x_set(x_any args) {
  return bind(sval(car(args)), eval(cadr(args)));
}

int64_t length(x_any cell) {
  int64_t length = 0;
  while(cell != x_env.nil) {
    length += 1;
    cell = cdr(cell);
  }
  return length;
}

x_any x_len(x_any args) {
  return new_int(length(car(args)));
}

x_any x_range(x_any args) {
  x_any start, stop, step, result;
  start = car(args);
  stop = cadr(args);
  step = caddr(args);

  assert(are_ints(start, stop) && is_int(step));
  assert(ival(step) != 0);
  result = x_env.nil;
  for (int i = ival(stop) - 1; i >= ival(start); i -= ival(step)) {
    result = cons(new_int(i), result);
  }
  return result;
}
