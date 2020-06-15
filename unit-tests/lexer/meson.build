test_lexer_src = files(
  'lexer.cc',
)

unit_test_lexer = executable(
  'unit-test-lexer',
  test_lexer_src,
  lexer_src,
  include_directories: [
    test_lexer_inc,
    educasort_inc
  ],
  c_args: unit_test_args,
  cpp_args: unit_test_args + [ '-std=gnu++11' ],
  dependencies: [
    gtest_dep
  ],
)

run_target(
  'unit-test-lexer',
  command: [
    unit_test_lexer.full_path()
  ],
  depends: unit_test_lexer,
)

test('unit-test-lexer', unit_test_lexer)
