cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(CasseBrique)

# Définir la version du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("include")

# Chercher SFML 3
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Ajouter ton fichier source
add_executable(main ${SOURCES})

# Lier SFML aux sources
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)