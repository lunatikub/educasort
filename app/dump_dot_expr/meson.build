dump_dot_expr_src = files(
  'dump_dot_expr.c',
)

dump_dot_expr = executable(
  'dump_dot_expr',
  dump_dot_expr_src,
  utils_src,
  lexer_src,
  parser_src,
  include_directories: [
    test_parser_inc,
    educasort_inc,
  ],
  c_args: common_args,
)
