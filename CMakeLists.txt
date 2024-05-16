cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME Lab_19)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11)
set(SOURCE_EXE
    main.c
    matrix.c
    )
    
set(DIRECTORIES 
    ${CMAKE_CURRENT_SOURCE_DIR})


include_directories (${DIRECTORIES})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})
