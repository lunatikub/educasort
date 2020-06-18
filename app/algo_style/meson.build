algo_style_src = files(
  'algo_style.c',
)

algo_style = executable(
  'algo_style',
  algo_style_src,
  utils_src,
  lexer_src,
  parser_src,
  visitor_src,
  include_directories: [
    educasort_inc,
  ],
  c_args: common_args,
)
