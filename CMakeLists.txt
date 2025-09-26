cmake_minimum_required(VERSION 3.20)

project(
    emojicpp
    VERSION 3.0.0
    DESCRIPTION "Emoji for C++ developers."
    LANGUAGES CXX
)

find_program(GPERF_EXECUTABLE gperf)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/internal.gperf"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/generated"
    COMMAND "${CMAKE_COMMAND}" -E cat ${CMAKE_CURRENT_SOURCE_DIR}/src/header.gperf  ${CMAKE_CURRENT_SOURCE_DIR}/src/emoji.gperf > ${CMAKE_CURRENT_BINARY_DIR}/generated/internal.gperf
    DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/header.gperf"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/emoji.gperf"
    COMMENT "Genrating main gperf file"
    VERBATIM
)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/internal.hpp"
    COMMAND ${GPERF_EXECUTABLE} --output-file=${CMAKE_CURRENT_BINARY_DIR}/generated/internal.hpp ${CMAKE_CURRENT_BINARY_DIR}/generated/internal.gperf
    DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/generated/internal.gperf"
    COMMENT "Generating gperf header"
    VERBATIM
)

add_library(${PROJECT_NAME} STATIC)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        "src/emoji.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/generated/internal.hpp"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_BINARY_DIR}/generated"
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set_source_files_properties(
    "${CMAKE_CURRENT_BINARY_DIR}/generated/internal.hpp"
    PROPERTIES
        GENERATED TRUE
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        PUBLIC_HEADER "include/emojicpp/emoji.hpp"
        DEBUG_POSTFIX "d"
)

include(GNUInstallDirs)

install(
    TARGETS "${PROJECT_NAME}"
    EXPORT "${PROJECT_NAME}Targets"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION cmake
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake
)

include(CTest)
option(BUILD_TESTING "Build tests" OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
