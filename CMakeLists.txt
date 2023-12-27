cmake_minimum_required(VERSION 3.5)

project(QSnake LANGUAGES CXX)

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
message("QRC_SOURCE_FILES = ${QRC_SOURCE_FILES}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
set(QRC_SOURCE_FILES Resources.qrc)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
#qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})


qt6_add_resources(RESOURCE_FILES ${QRC_SOURCE_FILES})
find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)


SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})

if(ANDROID)
  add_library(QSnake SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
	snake.h
	"snake.qrc"
	snake.cpp
        "data.txt"
  )
else()
  add_executable(QSnake
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
	snake.h
	"snake.qrc"
	snake.cpp
  )
endif()

target_link_libraries(QSnake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
