#指定Cmake最低版本
cmake_minimum_required(VERSION 3.5)

#编译后执行? 
set(EXECUTE ON)
#开启ctest测试
enable_testing()
#设置vcpkg安装路径

SET(CMAKE_TOOLCHAIN_FILE "/home/zhao/Software/vcpkg/scripts/buildsystems/vcpkg.cmake")
#设置输出文件为Debug版本
set(CMAKE_BUILD_TYPE Debug)
#生成的可执行文件名字
SET(PROJECTNAME "main")
#项目名字,支持的语言,版本号
project(TEMPLATE LANGUAGES C CXX VERSION 0.0.1)

#设置Cmake生成器
#set(CMAKE_GENERATOR "ninja")



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
#生成调试配置任务函数
function(GenerateDebugFile)
    #配置VSCode工作区模板
    set(VSCODE_WORKING_TEMPLATE "${PROJECT_SOURCE_DIR}/.config/c_cpp_properties.json.in")
    #设置平台
    #设置头文件目录
    set(INCLUDEDIRS "\${workspaceFolder}/**")
    set(INCLUDEDIRS "${INCLUDEDIRS}\",\n\t\t\t\t\"\${workspaceFolder}/include/**")
    set(INCLUDEDIRS "${INCLUDEDIRS}\",\n\t\t\t\t\"\${vcpkgRoot}/${VCPKG_TARGET_TRIPLET}/include/**")

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(PLATFORM "Linux")
        find_program(CMAKE_CXX_COMPILER NAMES g++ REQUIRED)
        set(COMPILER "${CMAKE_CXX_COMPILER}")
        set(INTELLISENSEMODE "linux-gcc-x64")
        if(CMAKE_CXX_STANDARD EQUAL 11)
        set(CPP_STANDARD "gnu++11")
    elseif(CMAKE_CXX_STANDARD EQUAL 14)
        set(CPP_STANDARD "gnu++14")
    elseif(CMAKE_CXX_STANDARD EQUAL 17)
        set(CPP_STANDARD "gnu++17")
    elseif(CMAKE_CXX_STANDARD EQUAL 20)
        set(CPP_STANDARD "gnu++20")
    elseif(CMAKE_CXX_STANDARD EQUAL 23)
        set(CPP_STANDARD "gnu++23")
    else()
        message(FATAL_ERROR "未知的C++标准")
        return()
    endif()
    if(CMAKE_C_STANDARD EQUAL 11)
        set(C_STANDARD "gnu11")
    elseif(CMAKE_C_STANDARD EQUAL 17)
        set(C_STANDARD "gnu17")
    elseif(CMAKE_C_STANDARD EQUAL 23)
        set(C_STANDARD "gnu23")
    else()
        message(FATAL_ERROR "未知的C标准")
    endif()     
    endif()
    
    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        #set(WINDOWSSKDVERSION ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
        set(PLATFORM "Win32")
        set(COMPILER "cl.exe")
        set(INTELLISENSEMODE "windows-msvc-x64")
        if(CMAKE_CXX_STANDARD EQUAL 11)
            set(CPP_STANDARD "c++11")
        elseif(CMAKE_CXX_STANDARD EQUAL 14)
            set(CPP_STANDARD "c++14")
        elseif(CMAKE_CXX_STANDARD EQUAL 17)
            set(CPP_STANDARD "c++17")
        elseif(CMAKE_CXX_STANDARD EQUAL 20)
            set(CPP_STANDARD "c++20")
        elseif(CMAKE_CXX_STANDARD EQUAL 23)
            set(CPP_STANDARD "c++23")
        else()
            message(FATAL_ERROR "未知的C++标准")
            return()
        endif()
        if(CMAKE_C_STANDARD EQUAL 11)
            set(C_STANDARD "c11")
        elseif(CMAKE_C_STANDARD EQUAL 17)
            set(C_STANDARD "c17")
        else()
            message(FATAL_ERROR "未知的C标准")
        endif()     
    endif()

    configure_file(${VSCODE_WORKING_TEMPLATE} 
    "${PROJECT_SOURCE_DIR}/.vscode/c_cpp_properties.json"
    )

    #配置Vscode调试执行文件
    set(VSCODE_LAUNCH_TEMPLATE "${PROJECT_SOURCE_DIR}/.config/launch.json.in")
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CONFIG_TYPE "cppdbg")
    set(PROGRAM_NAME "\${workspaceFolder}/build/${PROJECTNAME}")
    set(WORKSPACE_FOLDER "\${workspaceFolder}/build")
    endif()

    if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

    set(CONFIG_TYPE "cppvsdbg")
    set(PROGRAM_NAME "\${workspaceFolder}/build/${CMAKE_BUILD_TYPE}/${PROJECTNAME}.exe")
    set(WORKSPACE_FOLDER "\${workspaceFolder}/build")
    endif()

    configure_file(${VSCODE_LAUNCH_TEMPLATE}  "${PROJECT_SOURCE_DIR}/.vscode/launch.json" )
    #配置Vscode调试任务
    set(VSCODE_TASKS_TEMPLATE "${PROJECT_SOURCE_DIR}/.config/tasks.json.in")
    set(WORKSPACE_FOLDER "\${workspaceFolder}")
    configure_file(${VSCODE_TASKS_TEMPLATE}  "${PROJECT_SOURCE_DIR}/.vscode/tasks.json" )

endfunction()
#调试信息函数
function(DebugMsg)
    message("当前操作系统:${CMAKE_SYSTEM_NAME}")
    message("Vcpkg路径: ${CMAKE_TOOLCHAIN_FILE}")
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
    message("Windows SDK 版本: ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION}")
    message("当前生成器: ${CMAKE_GENERATOR}")


endfunction(DebugMsg)

#判断是不是在当前目录下生成的build输出目录
if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(WARNING "CMake 的二进制目录不能与源代码目录相同!")
endif()


#取消winodws.h里的MIN MAX宏,不然无法使用std::min std::max
if (WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

#开启ccache
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    message(STATUS "找到 CCache: ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()


#添加GCC编译器选项
if (CMAKE_CXX_COMPILER_ID MATCHES "GUN")
message("G++ 编译器")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

#cpp文件目录
file(GLOB_RECURSE source 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "{PROJECT_SOURCE_DIR}/src/*.c"
    )


#生成目标
add_executable(${PROJECTNAME} ${source})
#生成ctest
add_test(NAME ${PROJECTNAME}_Test COMMAND ${PROJECTNAME})
#头文件目录
target_include_directories(${PROJECTNAME} PUBLIC "include")

#添加需要的boost包
find_package(Boost)
if (Boost_FOUND)
    #boost库支持
    #静态链接boost库
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_RUNTIME ON)
    #查找不同平台include 目录
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(Boost_INCLUDE_DIR ${_VCPKG_INSTALLED_DIR}/x64-windows/include)
    endif()
    if (CMAKE_CXX_COMPILER_ID MATCHES "GUN")
    set(Boost_INCLUDE_DIR ${_VCPKG_INSTALLED_DIR}/x64-linux/include)
    endif()
    target_include_directories(${PROJECTNAME} PUBLIC ${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(${PROJECTNAME} PRIVATE ${Boost_LIBRARIES})
endif ()

#==============添加要链接的库=========================


#=====================================================




#ctest 支持
include(CTest)
enable_testing()


GenerateDebugFile()
#DebugMsg()

if (EXECUTE)
add_custom_command(TARGET ${PROJECTNAME} POST_BUILD COMMAND ${PROJECTNAME} COMMENT ".....开始执行程序.....")
add_custom_target(run ${PROJECTNAME})
endif()

