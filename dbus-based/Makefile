CC ?= g++
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4)
GLIB_COMPILE_RESOURCES = $(shell $(PKGCONFIG) --variable=glib_compile_resources gio-2.0)
GLIB_COMPILE_SCHEMAS = $(shell $(PKGCONFIG) --variable=glib_compile_schemas gio-2.0)

SRC = main.cpp
OBJS = $(BUILT_SRC:.c=.o) $(SRC:.c=.o)

PROJ_NAME = dbus-based

all: main.cpp
	${CC} ${CFLAGS} -o ${PROJ_NAME} main.c ${LIBS}


clean:
	rm -rf dbus-based