# Test sources
tests = []

test_sources = files(tests)

# Build test executable
# doctest provides its own main() if you define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN,
# but it's cleaner to let the subproject handle it via the dependency.
mx2d_tests = executable('mx2d_tests',
    source_files + test_sources + files([test_main.cpp]),
    dependencies:        deps,
    include_directories: inc,
    link_args:           linkargs,
    install:             false
)

# Register test
test('unit-tests', mx2d_tests)
