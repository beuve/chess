cmake_minimum_required(VERSION 3.15)
project(chess_engineCmake C)

# Standard C
set(CMAKE_C_STANDARD 11)  # C23 peut poser problème sur certains GCC/Clang

# Récupérer tous les fichiers sources dans src/ et sous-dossiers
file(GLOB_RECURSE SOURCES "src/*.c")

# Récupérer tous les dossiers sous include/ pour pouvoir inclure directement les headers
file(GLOB HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "include/*")
set(INCLUDE_DIRS "")
foreach(dir ${HEADER_DIRS})
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${dir}")
        list(APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/${dir}")
    endif()
endforeach()
# Ajouter le dossier include principal
list(APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")

# Créer l’exécutable
add_executable(chess_engineCmake ${SOURCES})

# Ajouter tous les include paths à la cible
target_include_directories(chess_engineCmake PRIVATE ${INCLUDE_DIRS})