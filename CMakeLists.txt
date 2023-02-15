#指定Cmake最低版本
cmake_minimum_required(VERSION 3.0)

#编译后执行? 
set(EXECUTE ON)

#vcpkg安装路径
#SET(CMAKE_TOOLCHAIN_FILE "/home/zhao/software/vcpkg/scripts/buildsystems/vcpkg.cmake")
#设置C++标准
set(CMAKE_CXX_STANDARD 20)
#检查编译器是否支持设置的标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#设置为ON表示启动GCC特性，OFF关闭GCC特性,只使用标准C++
set(CMAKE_CXX_EXTENSIONS OFF)

#设置C标准
set(CMAKE_C_STANDARD 17)
#检查编译器是否支持设置的标准
set(CMAKE_C_STANDARD_REQUIRED ON)
#设置为ON表示启动GCC特性，OFF关闭GCC特性,只使用标准C
set(CMAKE_C_EXTENSIONS OFF)

#项目名字,支持的语言,版本号
project(TEMPLATE LANGUAGES C CXX VERSION 0.0.1)

#判断是不是在当前目录下生成的build输出目录
if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(WARNING "The binary directory of CMake cannot be the same as source directory!")
endif()

#生成的可执行文件名字
SET(PROJECTNAME "main")

#设置输出文件为debug版本
set(CMAKE_BUILD_TYPE Debug)
#未设置CMAKE_BUILD_TYPE自动设置为Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
#取消winodws.h里的MIN MAX宏,不然无法使用std::min std::max
if (WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()
#开启ccache windows编译缓存
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("MSCV 编译器")
    find_program(CCACHE_PROGRAM ccache)
    if (CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    endif()
endif()

#设置GCC 编译器选项
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
message("G++ 编译器")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

#cpp文件目录
file(GLOB_RECURSE source 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "{PROJECT_SOURCE_DIR}/src/*.c"
    )
add_executable(${PROJECTNAME} ${source})
#头文件目录
target_include_directories(${PROJECTNAME} PUBLIC "include")

#输出构建信息
message("项目版本: ${PROJECT_VERSION}")
message("编译器: ${CMAKE_CXX_COMPILER_ID}")
message("主版本号: ${PROJECT_VERSION_MAJOR}")
message("次版本号: ${PROJECT_VERSION_MINOR}")
message("补丁版本号: ${PROJECT_VERSION_PATCH}")
message("项目名字: ${PROJECTNAME}")
message("项目源码目录: ${PROJECT_SOURCE_DIR}")
message("当前项目输出路径: ${PROJECT_BINARY_DIR}")
message("根项目源码路径: ${CMAKE_CURRENT_SOURCE_DIR}")
message("根项目的输出路径: ${CMAKE_CURRENT_BINARY_DIR}")
message("Boost库目录: ${Boost_LIBRARIES}")
message("Boost库版本: ${Boost_VERSION}")

if (EXECUTE)
add_custom_command(TARGET ${PROJECTNAME} POST_BUILD COMMAND ${PROJECTNAME} COMMENT ".....开始执行程序.....")
add_custom_target(run ${PROJECTNAME})
endif()

