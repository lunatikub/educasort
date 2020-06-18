###############
## Educasort ##
###############

# Declare the project
project(
  'educasort',
  'c',
)

c_compiler = meson.get_compiler('c')
root_dir = meson.source_root()

thread_dep = dependency('threads')

##############################
## Dependencies/Subprojects ##
##############################

# create subprojects directory
run_command('mkdir', '-p', join_paths(root_dir, 'subprojects'))

wrap_file = {
  'gtest': [ '1.7.0', 'googletest-release-1.7.0' ],
}

foreach name, content : wrap_file
  r = run_command(join_paths(root_dir,
                             'tools',
                             'subproject_prerequisite.sh'),
                  name, content[0], content[1])
  if r.returncode() != 0
    error('subproject_prerequisite.sh')
  endif
endforeach

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')

ncurses_dep = c_compiler.find_library('ncurses')
rt_dep = c_compiler.find_library('rt')

############################
## Flags compilation/link ##
############################

common_args = meson.get_compiler('c').get_supported_arguments([
  '-Wall',
  '-Werror',
  '-D_GNU_SOURCE',
  '-march=native',
  '-Wbool-compare',
  '-Wformat-security',
  '-Winit-self',
  '-Wlogical-op',
  '-Wtrampolines',
  '-Wmissing-format-attribute',
  '-Wno-error=deprecated-declarations',
  '-Wno-format-zero-length',
  '-pipe',
  '-g3',
  '-pthread',
  '-fstack-protector',
  '-funwind-tables',
  '-fasynchronous-unwind-tables',
  '-fstack-protector-strong',
  '-fno-common',
  '-Wshadow',
  '-Wmissing-declarations',
  '-Wpointer-arith',
  '-Wformat=2',
  '-mpclmul',
  '-msse4.1',
])

unit_test_args = c_compiler.get_supported_arguments(
  common_args + ['-DUNIT_TEST_TARGET']
)

#############
## Include ##
#############

# Global namespace: #include <educasort/...>
educasort_inc = include_directories('include', '.')

#############
## Sources ##
#############

# List of modules.
# Order can matter according to dependencies.
modules = [
  'utils',
  'lexer',
  'parser',
  'visitor',
]

# Add sources and unit tests (if exist) for each module.
foreach module : modules
  subdir(join_paths('src', module))
  unit_test_dir = join_paths('unit-tests', module)
  if run_command('[', '-d', unit_test_dir, ']').returncode() == 0
    subdir(unit_test_dir)
  endif
endforeach


#################
## Application ##
#################

applications = [
  'algo_style',
]

foreach app : applications
  subdir(join_paths('app', app))
endforeach
