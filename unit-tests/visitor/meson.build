test_visitor_src = files(
  'visitor.cc',
)

unit_test_visitor = executable(
  'unit-test-visitor',
  test_visitor_src,
  utils_src,
  lexer_src,
  parser_src,
  visitor_src,
  include_directories: [
    test_visitor_inc,
    educasort_inc
  ],
  c_args: unit_test_args,
  cpp_args: unit_test_args + [ '-std=gnu++11' ],
  dependencies: [
    gtest_dep
  ],
)

run_target(
  'unit-test-visitor',
  command: [
    unit_test_visitor.full_path()
  ],
  depends: unit_test_visitor,
)

test('unit-test-visitor', unit_test_visitor)
