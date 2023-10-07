cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(PROJECT_NAME capstone-wrapper)

project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME capstone
  GITHUB_REPOSITORY "capstone-engine/capstone"
  GIT_TAG 5.0.1
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${capstone_SOURCE_DIR}/include)

if (MSVC)
  target_compile_options(${PROJECT_NAME} INTERFACE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -pedantic -Werror)
endif()
# Add -fdiagnostics-color=always at CXXFLAGS
target_compile_options(${PROJECT_NAME} INTERFACE -fdiagnostics-color=always)

add_subdirectory(src)

add_executable(${PROJECT_NAME}-example example.cpp)
target_include_directories(${PROJECT_NAME}-example PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}-example ${PROJECT_NAME} capstone ${PROJECT_NAME}-internal)
