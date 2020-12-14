cmake_minimum_required(VERSION 3.2)

set(project_name "bulk")

configure_file(doxygen.config.in doxygen.config)

add_executable(${project_name}
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

message(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${project_name} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/InputParser
    ${CMAKE_CURRENT_SOURCE_DIR}/InputParser/ParseStrategy/Implementations
    ${CMAKE_CURRENT_SOURCE_DIR}/InputParser/States/Implementations
)

set_target_properties(${project_name} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${project_name} PRIVATE
        /W4 /WX
    )
else ()
    target_compile_options(${project_name} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if($ENV{TRAVIS_BUILD_NUMBER})
    project(${project_name} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${project_name} VERSION 0.0.321)
    target_compile_options(${project_name} PRIVATE
        -Wall -Wextra -pedantic -Werror -g
    )
endif()

install(TARGETS ${project_name} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dtopcode@gmail.com)

include(CPack)