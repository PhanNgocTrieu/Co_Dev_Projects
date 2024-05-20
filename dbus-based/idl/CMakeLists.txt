cmake_minimum_required(VERSION 3.10)
project(dbus)

add_definitions(
    -std=c++14
)

find_package(PkgConfig REQUIRED)
#find_package(DBUS)
pkg_check_modules(GLIB-2.0 REQUIRED glib-2.0)
pkg_check_modules(GOBJECT-2.0 REQUIRED gobject-2.0)
pkg_check_modules(GIO-UNIX-2.0 REQUIRED gio-unix-2.0)

set(IDL_DIR ${CMAKE_SOURCE_DIR}/idl)
include_directories(${IDL_DIR})

# Tool for generate code from xml
find_program(GDBUS_CODEGEN_EXECUTABLE NAMES gdbus-codegen)

execute_process(COMMAND ${GDBUS_CODEGEN_EXECUTABLE} --generate-c-code ${IDL_DIR}/dbus.res ${IDL_DIR}/dbus.res.xml)

include_directories(
    include
    ${DBUS_INCLUDE_DIRS}
    ${GLIB-2.0_INCLUDE_DIRS}
    ${GOBJECT-2.0_INCLUDE_DIRS}
    ${GIO-UNIX-2.0_INCLUDE_DIRS}
)

set(LIBS
    ${LIBS}
    ${DBUS_LIBRARIES}
    ${GLIB-2.0_LIBRARIES}
    ${GOBJECT-2.0_LIBRARIES}
    ${GIO-UNIX-2.0_LIBRARIES}
    pthread
)

set (SRC
    ${CMAKE_SOURCE_DIR}/idl/dbus.res.c
)


add_executable(client src/cli.cpp ${SRC})
add_executable(server src/srv.cpp ${SRC})

link_directories(
    ${GLIB-2.0_LIBRARY_DIRS}
    ${GOBJECT-2.0_LIBRARY_DIRS}
    ${GIO-UNIX-2.0_LIBRARY_DIRS}
)

target_link_libraries(client ${LIBS})
target_link_libraries(server ${LIBS})
