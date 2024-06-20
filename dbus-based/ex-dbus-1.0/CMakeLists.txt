cmake_minimum_required(VERSION 3.10)
project(dbus-based VERSION 1.0)

set(app ${PROJECT_NAME})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(DBus REQUIRED dbus-1)
pkg_check_modules(GLIB-2.0 REQUIRED glib-2.0)
pkg_check_modules(GOBJECT-2.0 REQUIRED gobject-2.0)
pkg_check_modules(GIO-UNIX-2.0 REQUIRED gio-unix-2.0)


set(IDL_DIR ${CMAKE_SOURCE_DIR}/idl)
include_directories(${IDL_DIR})

# # Tool for generate code from xml
# find_program(GDBUS_CODEGEN_EXECUTABLE NAMES gdbus-codegen)
# execute_process(COMMAND ${GDBUS_CODEGEN_EXECUTABLE} --generate-c-code ${IDL_DIR}/dbus.res ${IDL_DIR}/dbus.res.xml)

include_directories(
    ${DBUS_INCLUDE_DIRS}
    ${GTK_INCLUDE_DIRS}
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

link_directories(${GTK_LIBRARY_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})

add_executable( 
    ${app} research-dbus.cpp ${SRC}
)

target_link_libraries(
    ${app} 
    ${GTK_LIBRARIES}
    ${DBUS_LIBRARIES}
    ${GLIB-2.0_LIBRARY_DIRS}
    ${GOBJECT-2.0_LIBRARY_DIRS}
    ${GIO-UNIX-2.0_LIBRARY_DIRS}
)



target_link_libraries(${PROJECT_NAME} ${LIBS})

