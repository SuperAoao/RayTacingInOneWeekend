# 获取当前源码目录
message("当前源码目录: ${CMAKE_CURRENT_SOURCE_DIR}")

# 获取当前构建目录
message("当前构建目录: ${CMAKE_CURRENT_BINARY_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Common)

add_executable(Chapter12 main.cpp)

