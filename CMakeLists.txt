cmake_minimum_required(VERSION 3.2)

set(project_name "allocator")

if($ENV{TRAVIS_BUILD_NUMBER})
    project(${project_name} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${project_name} VERSION 0.0.321)
endif()

# find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.hpp.in version.hpp)

add_executable(${project_name}
    main.cpp
    reserve_allocator.cpp
    strange_struct.cpp
)

set_target_properties(${project_name} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${project_name}
    PRIVATE "${CMAKE_BINARY_DIR}"
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



install(TARGETS ${project_name} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dtopcode@gmail.com)

include(CPack)

# enable_testing()

# add_test(test_version test_version)
