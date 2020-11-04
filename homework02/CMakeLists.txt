cmake_minimum_required(VERSION 3.2)

set(project_name "allocator")

if($ENV{TRAVIS_BUILD_NUMBER})
    project(${project_name} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${project_name} VERSION 0.0.321)
endif()

# find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(${project_name}_cli main.cpp)

set_target_properties(${project_name}_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# set_target_properties(test_version PROPERTIES
#     COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#     INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
# )

# target_link_libraries(helloworld_cli PRIVATE
#     helloworld
# )
# target_link_libraries(test_version
#     ${Boost_LIBRARIES}
#     helloworld
# )

if (MSVC)
    target_compile_options(${project_name}_cli PRIVATE
        /W4 /WX
    )
else ()
    target_compile_options(${project_name}_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ${project_name}_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dtopcode@gmail.com)

include(CPack)

# enable_testing()

# add_test(test_version test_version)
