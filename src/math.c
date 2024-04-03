#include "lisp.h"

x_any _x_add(x_any a, x_any b, bool assign) {
  if (are_ints(a, b)) {
    if (assign) {
      set_val(a, ival(a) + ival(b));
      return a;
    }
    else {
      return new_int(ival(a) + ival(b));
    }
  }
  else if (are_doubles(a, b)) {
    if (assign) {
      dval(a) = dval(a) + dval(b);
      return a;
    }
    else {
      return new_double(dval(a) + dval(b));
    }
  }
  assert(0);
  return x_env.nil;
}

x_any x_add(x_any args) {
  return _x_add(car(args), cadr(args), false);
}

x_any x_addass(x_any args) {
  return _x_add(car(args), cadr(args), true);
}

x_any _x_sub(x_any a, x_any b, bool assign) {
  if (are_ints(a, b)) {
    if (assign) {
      set_val(a, ival(a) - ival(b));
      return a;
    }
    else {
      return new_int(ival(a) - ival(b));
    }
  }
  else if (are_doubles(a, b)) {
    if (assign) {
      dval(a) = dval(a) - dval(b);
      return a;
    }
    else {
      return new_double(dval(a) - dval(b));
    }
  }
  assert(0);
  return x_env.nil;
}


x_any x_sub(x_any args) {
  return _x_sub(car(args), cadr(args), false);
}

x_any x_subass(x_any args) {
  return _x_sub(car(args), cadr(args), true);
}

x_any _x_mul(x_any a, x_any b, bool assign) {
  if (are_ints(a, b)) {
    if (assign) {
      set_val(a, ival(a) * ival(b));
      return a;
    } else {
      return new_int(ival(a) * ival(b));
    }
  }
  else if (are_doubles(a, b)) {
    if (assign) {
      dval(a) = dval(a) * dval(b);
      return a;
    } else {
      return new_double(dval(a) * dval(b));
    }
  }
  assert(0);
  return x_env.nil;
}

x_any x_mul(x_any args) {
  return _x_mul(car(args), cadr(args), false);
}

x_any x_mulass(x_any args) {
  return _x_mul(car(args), cadr(args), true);
}

x_any _x_div(x_any a, x_any b, bool assign) {
  if (are_ints(a, b)) {
    if (assign) {
      set_val(a, ival(a) / ival(b));
      return a;
    } else {
      return new_int(ival(a) / ival(b));
    }
  }
  else if (are_doubles(a, b)) {
    if (assign) {
      dval(a) = dval(a) / dval(b);
      return a;
    } else {
      return new_double(dval(a) / dval(b));
    }
  }
  assert(0);
  return x_env.nil;
}

x_any x_div(x_any args) {
  return _x_div(car(args), cadr(args), false);
}

x_any x_divass(x_any args) {
  return _x_div(car(args), cadr(args), true);
}

x_any _x_fma(x_any a, x_any b, x_any c, bool assign) {
  if (are_ints(a, b)) {
    if (assign) {
      set_val(a, ival(a) * ival(b) + ival(c));
      return a;
    } else {
      return new_int(ival(a) * ival(b) + ival(c));
    }
  }
  else if (are_doubles(a, b)) {
    if (assign) {
      dval(a) = dval(a) * dval(b) + dval(c);
      return a;
    } else {
      return new_double(dval(a) * dval(b) + dval(c));
    }
  }
  assert(0);
  return x_env.nil;
}

x_any x_fma(x_any args) {
  return _x_fma(car(args), cadr(args), caddr(args), false);
}

x_any x_fmaass(x_any args) {
  return _x_fma(car(args), cadr(args), caddr(args), true);
}
