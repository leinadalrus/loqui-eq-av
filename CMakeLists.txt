cmake_minimum_required(VERSION 3.0.0)
project(Loqui VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(src
        src/api
        src/components
        src/controllers
        src/layouts
        src/models
        src/pages
        src/processors
        src/services
        src/shared
        src/templates
        src/utils
        src/views
        lib
        includes)

add_executable(Loqui
        src/models/nmt/nmt_ffnn.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
