#include <stdio.h>
#include <stdlib.h>

#include <educasort/parser/parser.h>
#include <educasort/visitor/visitor.h>
#include <educasort/visitor/style.h>
#include <educasort/utils/file.h>

/**
 * Apply the coding style on a sort algorithm and dump
 * the result on stdout.
 */

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: ./algo_style algo.sort\n");
    return -1;
  }

  size_t len;
  char *algo_sort = filetobuf(argv[1], &len);
  if (algo_sort == NULL) {
    fprintf(stderr, "Error file: %s.\n", argv[1]);
    return -1;
  }

  struct visitor_style vs;
  struct ast ast;

  if (!parse(&ast, algo_sort, len)) {
    return -1;
  }
  free(algo_sort);

  visitor_style_init(&vs);
  visit(&ast, &vs.visitor);

  printf("%s\n", string_get(vs.algo));

  visitor_style_clean(&vs);
  ast_destroy(&ast);
  return 0;
}
