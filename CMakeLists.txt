cmake_minimum_required(VERSION 3.16)
project(smooth_motion)

find_package(SFML 2.5 
COMPONENTS 
system window graphics network audio REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
# set(THREADS_PREFER_PTHREAD_FLAG TRUE)
# find_package(Threads REQUIRED)

configure_file("assets/roboto.ttf" ${CMAKE_BINARY_DIR}/assets/roboto.ttf COPYONLY)
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} sfml-graphics)