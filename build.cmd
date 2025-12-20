meson setup build
meson compile -C build
.\build\mx2d --help

meson test -C build -v
