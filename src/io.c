#include "lisp.h"

char* x_str(x_any args) {
  char *bp;
  size_t size;
  FILE *stream;
  stream = open_memstream (&bp, &size);
  print_cell(car(args), stream);
  fclose(stream);
  return bp;
}

void print_cell(x_any cell, FILE *outfile) {
  if (is_fn(cell) || is_special(cell))
    fprintf(outfile, "<%s at %p>", sval(type(cell)), (void*)val(cell));
  else if (is_binding(cell))
    fprintf(outfile, "%s", sval(cell));
  else if (is_def(cell)) {
    putc('(', outfile);
    print_list(cell, outfile);
  }
  else if (is_int(cell))
    fprintf(outfile, "%" PRIi64, ival(cell));
  else if (is_double(cell))
    fprintf(outfile, "%9.16f", dval(cell));
  else if (is_symbol(cell))
    fprintf(outfile, "%s", sval(cell));
  else if (is_pair(cell)) {
    putc('(', outfile);
    print_list(cell, outfile);
  }
  else
    assert(0);
}

void print_list(x_any cell, FILE *outfile) {
  print_cell(car(cell), outfile);
  if (cdr(cell) == x_env.nil)
    putc(')', outfile);
  else if (!is_pair(cdr(cell)) ) {
    fprintf(outfile, " . ");
    print_cell(cdr(cell), outfile);
    putc(')', outfile);
  }
  else {
    putc(' ', outfile);
    print_list(cdr(cell), outfile);
  }
}

x_any x_print(x_any args) {
  x_any cell;
  cell = car(args);
  print_cell(cell, stdout);
  return cell;
}

x_any x_println(x_any args) {
  x_any cell;
  cell = car(args);
  print_cell(cell, stdout);
  putchar('\n');
  return cell;
}

x_any x_printsp(x_any args) {
  x_any cell;
  cell = car(args);
  print_cell(cell, stdout);
  putchar(' ');
  return cell;
}
