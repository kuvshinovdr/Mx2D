# Project heading.
project('Mx2D', 'cpp',
        version: '1.0',
        default_options: [
            'cpp_std=c++23',
            'warning_level=everything',
		    'b_ndebug=if-release',
        ]
)

# Dependencies.
doctest_dep   = dependency('doctest',   fallback: ['doctest', 'doctest_dep'])
freetype2_dep = dependency('freetype2', fallback: ['freetype2'])
miniaudio_dep = dependency('miniaudio', fallback: ['miniaudio'])
ogg_dep       = dependency('ogg',       fallback: ['ogg', 'libogg_dep'])
vorbis_dep    = dependency('vorbis',    fallback: ['vorbis', 'vorbis_dep'])
flac_dep      = dependency('flac',      fallback: ['flac', 'flac_dep'])
sfml_dep      = dependency('sfml',      fallback: ['sfml', 'sfml_dep'])
eigen_dep     = dependency('eigen3',	fallback: ['eigen3'])

deps = [
        doctest_dep,
        freetype2_dep, 
        miniaudio_dep,
        ogg_dep,
        vorbis_dep,
        flac_dep,
        sfml_dep,
		eigen_dep		
    ]

# Enforce C++23 support and GCC ≥ 15 for std::println.
cc = meson.get_compiler('cpp')

if cc.get_id() == 'gcc'
    if cc.version().version_compare('<15')
        error('GCC >= 15 is required for std::println (C++23)')
    endif
elif cc.get_id() == 'clang'
    # Clang doesn't yet implement std::println in standard library (as of 2025),
    # so we assume you're using GCC. If you plan to support Clang later,
    # you may need libc++ experimental support or feature guards.
    warning('Clang support for std::println is not guaranteed.')
endif

linkargs = []

# Optional: link libstdc++exp only for GCC.
if cc.get_id() == 'gcc'
    linkargs = ['-lstdc++exp']
endif

subdir('src')
subdir('tests')
