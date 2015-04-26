project(ExpressionCpp002)
cmake_minimum_required(VERSION 2.8)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../gmock-1.7.0/include ${CMAKE_CURRENT_SOURCE_DIR}/../gmock-1.7.0/gtest/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gmock-1.7.0-build ${CMAKE_CURRENT_SOURCE_DIR}/../gmock-1.7.0-build/gtest)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(ExpressionCpp002 gmock gtest)

