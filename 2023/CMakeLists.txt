cmake_minimum_required(VERSION 3.0.0)
project(2023 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(GLOB SRC_FILES
    "lib/*.cpp"
    "*.cpp"
)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.76.0 COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(2023 main.cpp)
    target_sources(2023 PUBLIC
        ${SRC_FILES}
    )
    target_link_libraries(2023 ${Boost_LIBRARIES})
endif()