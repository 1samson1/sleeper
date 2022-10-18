set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../resources)

set(UI_FILES
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
)

add_executable(sleeper
    main.cpp
    ${UI_FILES}
    ${RESOURCE_DIR}/resources.qrc
)

set_target_properties(sleeper PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

# Libraties

# FIND QT ###################################

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# link libraries

target_link_libraries(sleeper PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)