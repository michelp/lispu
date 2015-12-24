#include "lisp.h"

int inline hash(const char *name) {
  int value = 0;
  while (*name != '\0')
    value = (value * X_HASH_MULTIPLIER + *name++) % X_HASH_TABLE_SIZE;
  return value;
}

x_any inline lookup(const char *name) {
  x_any binding;
  int hashval;

  hashval = hash(name);
  binding = x_env.frames->names[hashval];
  if (binding == x_env.nil)
    return NULL;
  do {
    if (strcmp(name, sval(binding)) == 0)
      return binding;
    binding = cdr(binding);
  } while (binding != NULL);
  return NULL;
}

void bind(const char* name, x_any cell1) {
  int hash_val;
  x_any binding, bucket;
  hash_val = hash(name);
  binding = lookup(name);
  if (binding != NULL) {
    set_car(binding, cell1);
    return;
  }

  bucket = x_env.frames->names[hash_val];
  binding = new_cell(name, x_env.binding);
  set_car(binding, cell1);
  set_cdr(binding, bucket);
  x_env.frames->names[hash_val] = binding;
}

x_any intern(const char *name) {
  x_any cell;
  cell = lookup(name);
  if (cell != NULL)
    return car(cell);

  cell = new_cell(name, x_env.symbol);
  bind(name, cell);
  return cell;
}
