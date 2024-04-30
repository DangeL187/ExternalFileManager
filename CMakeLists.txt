cmake_minimum_required(VERSION 3.26)
project(ExternalFileManager)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/QT/6.6.2/mingw_64/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
set(QT_LIBS Qt6::Core Qt6::Gui Qt6::Widgets)

include_directories(include)

file(GLOB HEADER_FILES  "include/***/**/*.hpp"
                        "include/**/*.hpp"
                        "include/*.hpp")
file(GLOB SOURCE_FILES  "src/***/**/*.cpp"
                        "src/**/*.cpp"
                        "src/*.cpp")

add_executable(ExternalFileManager WIN32 ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(ExternalFileManager ${QT_LIBS})

# Configure QT6:

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "D:/QT/6.6.2/mingw_64")

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
