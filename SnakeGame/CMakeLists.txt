cmake_minimum_required(VERSION 3.10)
project(snake_game)

set(SDL2
  /Library/Frameworks/SDL2.framework)
set(SDL2_image
  /Library/Frameworks/SDL2_image.framework)
set(SDL2_ttf
  /Library/Frameworks/SDL2_ttf.framework)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
if (SDL2_FOUND)
    message("Found SDL2")
else()
    message("Not Found SDL2")
endif()

find_package(SDL2_image REQUIRED )
if (SDL2_image_FOUND)
    message("Found SDL2_image")
else()
    message("Not Found SDL2_image")
endif()


set(MY_SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${MY_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image
    ${SDL2}/Versions/A/SDL2
    ${SDL2_image}/Versions/A/SDL2_image
    ${SDL2_ttf}/Versions/A/SDL2_ttf
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${SDL2}/Versions/A/Headers
    ${SDL2_image}/Versions/A/Headers
    ${SDL2_ttf}/Versions/A/Headers
)