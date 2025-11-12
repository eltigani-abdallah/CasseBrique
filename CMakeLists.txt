cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(CasseBrique)

# Définir la version du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("include")

# Chercher SFML 3
find_package(SFML 3 COMPONENTS System Window Graphics Audio Network REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Ajouter ton fichier source
add_executable(main ${SOURCES})

# Lier SFML aux sources
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)