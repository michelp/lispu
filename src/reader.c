#include "lisp.h"

x_any read_token(FILE *infile) {
  int c;
  static char buf[X_MAX_TOKEN_LEN];
  char *ptr = buf;
  do {
    c = getc(infile);
    if (c == ';')
      do c = getc(infile); while (c != '\n' && c != EOF);
  } while (isspace(c));
  switch (c) {
  case EOF:
    return x_env.eof;
  case '(':
    return x_env.lparen;
  case ')':
    return x_env.rparen;
  case '[':
    return x_env.lbrack;
  case ']':
    return x_env.rbrack;
  case '.':
    return x_env.dot;
  case '\'':
    return x_env.quote;
  default:
    *ptr++ = c;
    while ((c = getc(infile)) != EOF &&
           !isspace(c)          &&
           c != '(' && c != ')' &&
           c != '[' && c!= ']'  &&
           c != '{' && c!= '}')
      *ptr++ = c;
    if (c != EOF)
      ungetc(c, infile);
    *ptr = '\0';
    return new_cell(buf, x_env.symbol);
  }
}

x_any read_cdr(FILE *infile) {
  x_any cdr;
  x_any token;
  cdr = read_sexpr(infile);
  token = read_token(infile);
  if (token == x_env.rparen)
    return cdr;
  else
    assert(0);
  return x_env.nil;
}

x_any read_sexpr_tail(FILE *infile) {
  x_any token;
  x_any temp;
  token = read_token(infile);
  if (is_symbol(token))
    return cons(token, read_sexpr_tail(infile));
  if (token == x_env.lparen) {
    temp = read_sexpr_head(infile);
    return cons(temp, read_sexpr_tail(infile));
  }
  if (token == x_env.dot)
    return read_cdr(infile);
  if (token == x_env.rparen)
    return x_env.nil;
  if (token == x_env.eof)
    assert(0);
  return x_env.nil;
}

x_any read_sexpr_head(FILE *infile) {
  x_any token;
  x_any temp;
  token = read_token(infile);
  if (is_symbol(token))
    return cons(token, read_sexpr_tail(infile));
  else if (token == x_env.lparen) {
    temp = read_sexpr_head(infile);
    return cons(temp, read_sexpr_tail(infile));
  }
  else if (token == x_env.rparen)
    return x_env.nil;
  else if (token == x_env.dot)
    assert(0);
  else if (token == x_env.eof)
    assert(0);
  return x_env.nil;
}

x_any read_sexpr(FILE *infile) {
  x_any token;
  token = read_token(infile);
  if (is_symbol(token))
    return token;
  if (token == x_env.lparen)
    return read_sexpr_head(infile);
  if (token == x_env.rparen)
    assert(0);
  if (token == x_env.dot)
    assert(0);
  if (token == x_env.eof)
    return token;
  return x_env.nil;
}
