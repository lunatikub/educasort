test_parser_src = files(
  'parser.cc',
)

unit_test_parser = executable(
  'unit-test-parser',
  test_parser_src,
  utils_src,
  parser_src,
  lexer_src,
  include_directories: [
    test_parser_inc,
    educasort_inc
  ],
  c_args: unit_test_args,
  cpp_args: unit_test_args + [ '-std=gnu++11' ],
  dependencies: [
    gtest_dep
  ],
)

run_target(
  'unit-test-parser',
  command: [
    unit_test_parser.full_path()
  ],
  depends: unit_test_parser,
)

test('unit-test-parser', unit_test_parser)
