cmake_minimum_required(VERSION 3.16)
project(problem_2_simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(problem_2 main.cc ${sources} ${headers})
target_link_libraries(problem_2 ${Geant4_LIBRARIES})
