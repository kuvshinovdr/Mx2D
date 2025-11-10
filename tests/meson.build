# Test sources
tests = []

test_sources = files(tests)

# Build test executable
# doctest provides its own main() if you define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN,
# but it's cleaner to let the subproject handle it via the dependency.
rendercsv_tests = executable('rendercsv_tests',
    source_files + test_sources + files([]),
    dependencies:        deps,
    include_directories: inc,
    link_args:           linkargs,
    install:             false
)

# Register test
test('unit-tests', rendercsv_tests)
