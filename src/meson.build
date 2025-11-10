# Sources
sources = []

source_files = files(sources)

inc = include_directories('.')

# Create main executable
executable('rendercsv',
    source_files + files([]),
	dependencies:        deps,
    include_directories: inc,
	link_args:           linkargs,
    install:             true
)
