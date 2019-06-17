all: wayland-compositor-demo

format:
	clang-format -i main.c

wayland-compositor-demo: main.c protocols/xdg-shell.c protocols/xdg-shell.h Makefile
	gcc -o wayland-compositor-demo -Wall -Wextra -Wno-unused-parameter main.c protocols/xdg-shell.c -lwayland-server

protocols/xdg-shell.c: protocols/xdg-shell.xml Makefile
	wayland-scanner -c private-code protocols/xdg-shell.xml protocols/xdg-shell.c

protocols/xdg-shell.h: protocols/xdg-shell.xml Makefile
	wayland-scanner -c server-header protocols/xdg-shell.xml protocols/xdg-shell.h

.PHONY: all format
