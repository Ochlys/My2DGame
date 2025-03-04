cmake_minimum_required(VERSION 3.10)

project(SFML_Moving_Circle)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

set(SOURCES 
  src/main.cpp
  src/application.cpp
  src/player.cpp  # Ajoute ici player.cpp
)

set(HEADERS 
  src/defines.hpp
  src/application.hpp
  src/player.hpp  # Ajoute aussi player.hpp s'il manque
  src/utils/vectors.hpp
  src/utils/tiles.hpp
  src/utils/collisionManager.hpp
)

add_executable(SFML_Moving_Circle ${SOURCES} ${HEADERS})

target_link_libraries(SFML_Moving_Circle PRIVATE sfml-graphics sfml-window sfml-system)
