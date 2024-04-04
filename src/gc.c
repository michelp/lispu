#include "lisp.h"

x_any c_alloc(x_any type) {
  x_any cell;
  if (!(cell = x_env.cell_pools->free))
    assert(0);
  x_env.cell_pools->free = car(cell);
  set_cdr(cell, NULL);
  set_car(cell, NULL);
  set_type(cell, type);
  return cell;
}

char* new_name(const char* name) {
  char *n;
  n = (char*)GC_malloc(strlen(name) + 1);
  strcpy(n, name);
  return n;
}

x_any new_cell(const char* name, x_any type) {
  x_any cell;
  cell = c_alloc(type);
  if (name == NULL)
    set_val(cell, NULL);
  else
    set_val(cell, new_name(name));
  return cell;
}

x_any new_int(int64_t value) {
  x_any cell;
  cell = new_cell(NULL, x_env.int_);
  set_val(cell, value);
  return cell;
}

x_any new_double(double value) {
  x_any cell;
  double *v;
  cell = new_cell(NULL, x_env.double_);
  v = (double*)GC_malloc(sizeof(double));
  assert(v != NULL);
  *v = value;
  set_val(cell, v);
  return cell;
}

x_cell_pool* new_cell_pool(x_cell_pool* old) {
  x_cell_pool* h;
  x_any cell;
  h = (x_cell_pool*)GC_malloc(sizeof(x_cell_pool));
  h->next = old;
  cell = h->cells + X_YOUNG_CELL_POOL_SIZE - 1;
  do
    free_cell(h, cell);
  while (--cell >= h->cells);
  return h;
}

void init_frames() {
  for (int i = 0; i < X_NUM_FRAMES; i++)
    for (int j = 0; j < X_HASH_TABLE_SIZE; j++)
      x_env.frames[i][j] = x_env.nil;

  x_env.frame_count = 0;
  x_env.max_frame_count = 0;
}
