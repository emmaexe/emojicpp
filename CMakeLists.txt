cmake_minimum_required(VERSION 3.17)

project(
    emojicpp
    VERSION 1.0.0
    DESCRIPTION "Emoji for C++ developers."
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_DEBUG_POSTFIX d)

add_library(emojicpp)
add_library(emojicpp::emojicpp ALIAS emojicpp)

set_target_properties(
    emojicpp PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_sources(
    emojicpp
    PRIVATE src/emoji.cpp
)

target_compile_features(
    emojicpp
    PUBLIC cxx_std_17
)

target_include_directories(
    emojicpp
    PRIVATE src
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(GenerateExportHeader)
set_property(
    TARGET emojicpp
    PROPERTY CXX_VISIBILITY_PRESET "hidden"
)
set_property(
    TARGET emojicpp
    PROPERTY VISIBILITY_INLINES_HIDDEN TRUE
)

generate_export_header(
    emojicpp
    EXPORT_FILE_NAME
    export/emojicpp/export_emojicpp.hpp
)

target_include_directories(
    emojicpp
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/export>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(GNUInstallDirs)

install(
    TARGETS emojicpp
    EXPORT emojicppTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/export/emojicpp/export_emojicpp.hpp"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/emojicpp
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "emojicppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/emojicppConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/emojicppConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/emojicpp
)

install(
    EXPORT emojicppTargets
    FILE emojicppTargets.cmake
    NAMESPACE emojicpp::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/emojicpp
)
