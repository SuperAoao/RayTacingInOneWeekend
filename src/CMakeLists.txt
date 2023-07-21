
# 定义项目名称
set(PROJECT_NAME RTIn1WeekendAoPractise)
# 低版本以及policy不允许使用版本号
cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)
# 设置项目版本号
set(PROJECT_VERSION 0.1)
# 设置项目信息
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

add_subdirectory(Chapter1OutputAnImage)
add_subdirectory(Chapter2TheVec3Class)
add_subdirectory(Chapter3RaysASimpleCameraAndBackground)
add_subdirectory(Chapter4AddingASphere)
add_subdirectory(Chapter5SurfaceNormalsAndMultipleObjects)
add_subdirectory(Chapter6Antialiasing)
add_subdirectory(Chapter7DiffuseMaterials)
add_subdirectory(Chapter8Metal)
add_subdirectory(Chapter9Dielectrics)
add_subdirectory(Chapter10PositionableCamera)
add_subdirectory(Chapter11DefocusBlur)
add_subdirectory(Chapter12WhereNext)


