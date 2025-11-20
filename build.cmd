meson setup build
meson compile -C build
.\build\rendercsv --help

meson test -C build -v
