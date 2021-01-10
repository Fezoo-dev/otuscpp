cmake_minimum_required(VERSION 3.2)

configure_file(doxygen.config.in doxygen.config)

set(project_name "bayan")

if($ENV{TRAVIS_BUILD_NUMBER})
    project(${project_name} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${project_name} VERSION 0.0.321)
endif()

file(GLOB project_source
    *.cpp
)

# set(project_dirs
#     ${CMAKE_CURRENT_SOURCE_DIR}/InputParser
#)

add_executable(${project_name} ${project_source})

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS program_options filesystem)

if(Boost_FOUND)
    target_link_libraries(${project_name} ${Boost_LIBRARIES})
    target_include_directories(${project_name} PRIVATE 
        ${BOOST_INCLUDE_DIR}
    )
endif()

set_target_properties(${project_name} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${project_name} PRIVATE /W4 /WX)
else ()
    target_compile_options(${project_name} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ${project_name} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dtopcode@gmail.com)

include(CPack)

# GTESTs
# set(project_lib ${project_name}_lib)
# add_library(${project_lib} ${project_source})

# add_subdirectory(gtest)
# enable_testing()

# set(tests_name "bulk_tests")

# file(GLOB tests_sources
#     "tests/*.cpp"
# )

# add_executable(${tests_name} ${tests_sources})

# target_include_directories(${tests_name} PRIVATE 
#     ${CMAKE_CURRENT_SOURCE_DIR}/tests
#     ${project_dirs}
# )

# target_link_libraries(${tests_name} 
#     ${project_lib}
#     gtest
#     gtest_main
# )

# add_test(${tests_name} bulk_tests)