cmake_minimum_required(VERSION 3.2)

set(project_name "bayan")

if($ENV{TRAVIS_BUILD_NUMBER})
    configure_file(doxygen.config.in doxygen.config)
    project(${project_name} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${project_name} VERSION 0.0.321)
endif()

file(GLOB project_source
    *.cpp
    FileFinder/*.cpp
    FileFinder/Validators/*.cpp
    FileFinder/HashAlgorithms/*.cpp
    FileComparer/*.cpp
)

set(project_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/FileFinder
    ${CMAKE_CURRENT_SOURCE_DIR}/FileFinder/Validators
    ${CMAKE_CURRENT_SOURCE_DIR}/FileFinder/HashAlgorithms
    ${CMAKE_CURRENT_SOURCE_DIR}/FileComparer
)

add_executable(${project_name} ${project_source})

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS program_options filesystem regex)

if(Boost_FOUND)
    target_link_libraries(${project_name} ${Boost_LIBRARIES})
    target_include_directories(${project_name} PRIVATE 
        ${BOOST_INCLUDE_DIR}
    )
endif()

target_include_directories(${project_name} PRIVATE 
        ${project_dirs}
    )
    
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
