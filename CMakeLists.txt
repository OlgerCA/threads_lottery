cmake_minimum_required(VERSION 3.3)
project(threads_lottery)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(GTK3 REQUIRED)
include_directories(${GTK3_INCLUDE_DIRS})

set(SOURCE_FILES main.c threadWork.c threadWork.h Thread.c LoteryScheduler.c)
add_executable(threads_lottery ${SOURCE_FILES})

set(LIBS ${LIBS} ${GTK3_LIBRARIES})
target_link_libraries(threads_lottery ${LIBS})

install(TARGETS threads_lottery DESTINATION bin)
SET(CPACK_GENERATOR "TGZ")
include(CPack)