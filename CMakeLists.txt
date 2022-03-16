cmake_minimum_required(VERSION 3.11...3.16)
project(MD5Encrypter LANGUAGES CXX)

add_definitions("-std=c++17")

# BUILD_SHARED_LIBS is used by add_library to build STATIC/SHARED lib
option(BUILD_SHARED_LIBS "Build licensing as a shared library." OFF)
option(USE_CONAN "Option if conanbuildinfo should be used" OFF)


if(USE_CONAN)
    include(${CMAKE_SOURCE_DIR}/conanbuildinfo_multi.cmake)
    conan_basic_setup(TARGETS)
    
    add_definitions(-DCONAN)
    add_executable(md5 src/md5.cpp)
    target_link_libraries(md5 CONAN_PKG::poco)
    
else() # USE VCPKG
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_definitions(-DVCPKG)
    # To find and use catch
    find_package(Poco CONFIG REQUIRED Net XML Zip Data)
    add_executable(md5 src/md5.cpp)

    if (MSVC)
        target_compile_options(md5 PUBLIC /MT)
        target_link_options(md5 PUBLIC /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
    endif()

    target_link_libraries(md5 PRIVATE Poco::Net Poco::XML Poco::Zip Poco::Data)
endif()

