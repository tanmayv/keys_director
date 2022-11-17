cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME keys_director)
set(MAIN_EXECUTABLE keys_director_main) 

# set(PROJECT_NAME TEST)
# set(MAIN_EXECUTABLE "${PROJECT_NAME}_main")
project(${PROJECT_NAME})
add_subdirectory(lib/hidapi)
add_subdirectory(lib/plog)
add_executable(${MAIN_EXECUTABLE} src/main.cc)
# set include directory
target_include_directories(${MAIN_EXECUTABLE} PUBLIC include)
target_include_directories(${MAIN_EXECUTABLE} PRIVATE src)
target_link_libraries(${MAIN_EXECUTABLE} hidapi::hidapi plog)