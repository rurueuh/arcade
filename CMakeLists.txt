cmake_minimum_required(VERSION 3.0.0)
project(arcade VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE helloworld_SRC
     "src/core/*.hpp"
     "src/core/*.cpp"
)

foreach (file ${helloworld_SRC})
    set(MYFILE_DIR)
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()

file(GLOB_RECURSE rb_rpdb_src "src/arcade/")
message(STATUS "headers: ${rb_rpdb_src} ")
add_executable(arcade ${helloworld_SRC})
add_custom_command(
    TARGET arcade
    POST_BUILD
    COMMAND rm -rf games/ && rm -rf lib/ && mkdir lib/ && mkdir games/
)
TARGET_LINK_LIBRARIES(arcade dl)

# LIB
project(sfml VERSION 0.1.0)
file(GLOB_RECURSE SRC_LIB
"src/lib/SFML/*.hpp"
"src/lib/SFML/*.cpp"
)
add_library(sfml SHARED ${SRC_LIB})
target_link_libraries(sfml sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
add_custom_command(
    TARGET sfml
    POST_BUILD
    COMMAND mv libsfml.so lib/arcade_sfml.so
)
execute_process(COMMAND sfml clean_SFML)


project(SDL VERSION 0.1.0)
file(GLOB_RECURSE SRC_LIB
     "src/lib/SDL/*.hpp"
     "src/lib/SDL/*.cpp"
)
add_library(SDL SHARED ${SRC_LIB})
add_custom_command(
    TARGET SDL
    POST_BUILD
    COMMAND mv libSDL.so lib/arcade_sdl2.so
)
target_link_libraries(SDL SDL2 SDL2_image SDL2_ttf)

project(ncruses VERSION 0.1.0)
file(GLOB_RECURSE SRC_LIB
     "src/lib/Ncurses*.hpp"
     "src/lib/Ncurses*.cpp"
)
add_library(ncruses SHARED ${SRC_LIB})
add_custom_command(
    TARGET ncruses
    POST_BUILD
    COMMAND mv libncruses.so lib/arcade_ncurses.so
)
target_link_libraries(ncruses ncurses)

# GAMES
project(snake VERSION 0.1.0)
file(GLOB_RECURSE SRC_SNAKE
     "src/games/Snake/*.hpp"
     "src/games/Snake/*.cpp"
     "src/games/GameCore/*.hpp"
     "src/games/GameCore/*.cpp"
)
add_library(snake SHARED ${SRC_SNAKE})
add_custom_command(
    TARGET snake
    POST_BUILD
    COMMAND mv libsnake.so lib/arcade_snake.so
)
target_link_libraries(snake)

project(centipede VERSION 0.1.0)
file(GLOB_RECURSE SRC_CENTIPEDE
     "src/games/Centipede/*.hpp"
     "src/games/Centipede/*.cpp"
     "src/games/GameCore/*.hpp"
     "src/games/GameCore/*.cpp"
)
add_library(centipede SHARED ${SRC_CENTIPEDE})
target_link_libraries(centipede)
add_custom_command(
    TARGET centipede
    POST_BUILD
    COMMAND mv libcentipede.so lib/arcade_centipede.so &&
    cp -r ./lib ../ && cp ./arcade ../
)
