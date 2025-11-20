# Sources
sources = []

source_files = files(sources)

inc = include_directories('.')

# Create main executable
executable('mx2d',
    source_files + files([main.cpp]),
	dependencies:        deps,
    include_directories: inc,
	link_args:           linkargs,
    install:             true
)
