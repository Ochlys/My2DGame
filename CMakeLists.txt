cmake_minimum_required(VERSION 3.10)

project(SFML_Moving_Circle)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Fichiers sources .cpp à compiler
set(SOURCES 
  src/main.cpp
  src/application.cpp
  src/player.cpp
  src/entity/movingEntity.cpp
)

# Fichiers d'en-tête .hpp, qui ne doivent pas être compilés
set(HEADERS 
  src/defines.hpp
  src/application.hpp
  src/player.hpp
  src/utils/vectors.hpp
  src/tile.hpp
  src/entity/movingEntity.hpp
  src/entity/baseEntity.hpp
  src/geometry/box.hpp

)

add_executable(SFML_Moving_Circle ${SOURCES} ${HEADERS})

target_link_libraries(SFML_Moving_Circle PRIVATE sfml-graphics sfml-window sfml-system)
