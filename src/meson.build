# Sources
sources = [
    'config.cpp',
    'csv.cpp',
	'file_group_action.cpp',
	'file_group_action_details.cpp',
    'file_to_string.cpp',
    'html.cpp',
    'md.cpp',
	'prepend_file.cpp',
    'string_to_file.cpp',
	'table_formatter_utils.cpp',
]

source_files = files(sources)

inc = include_directories('.')

# Create main executable
executable('rendercsv',
    source_files + files(['main.cpp']),
	dependencies:        deps,
    include_directories: inc,
	link_args:           linkargs,
    install:             true
)
