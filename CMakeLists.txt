cmake_minimum_required(VERSION 3.2)

configure_file(doxygen.config.in doxygen.config)

set(project_name "bulk")

set(project_source 
    main.cpp
    InputParser/InputParser.cpp
    InputParser/InputParserBuilder.cpp
    InputParser/ParseStrategy/IParseStrategy.cpp
    InputParser/ParseStrategy/Implementations/CurlyBracesParseStrategy.cpp
    InputParser/States/IParserState.cpp
    InputParser/States/Implementations/BaseParserState.cpp
    InputParser/States/Implementations/ParserStateStatic.cpp
    InputParser/States/Implementations/ParserStateDynamic.cpp
)

set(project_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/InputParser
    ${CMAKE_CURRENT_SOURCE_DIR}/InputParser/ParseStrategy/Implementations
    ${CMAKE_CURRENT_SOURCE_DIR}/InputParser/States/Implementations
)

add_executable(${project_name} ${project_source})

target_include_directories(${project_name} PRIVATE ${project_dirs})

set_target_properties(${project_name} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${project_name} PRIVATE /W4 /WX)
else ()
    target_compile_options(${project_name} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if($ENV{TRAVIS_BUILD_NUMBER})
    project(${project_name} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${project_name} VERSION 0.0.321)
endif()

install(TARGETS ${project_name} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dtopcode@gmail.com)

include(CPack)

# GTESTs
set(project_lib ${project_name}_lib)
add_library(${project_lib} ${project_source})

add_subdirectory(gtest)
enable_testing()

add_executable("bulk_tests" 
    tests/tests.cpp
    tests/StateBaseSuiteTests.cpp
    tests/StaticStateSuiteTests.cpp
    tests/DynamicStateSuiteTests.cpp
)

target_include_directories("bulk_tests" PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${project_dirs}
)

target_link_libraries("bulk_tests" 
    ${project_lib}
    gtest
    gtest_main
)

add_test("bulk_tests" bulk_tests)