set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../resources)


set(APP_FILES
    app/application.h
    app/application.cpp
)

set(UI_FILES
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
)

set(UTILS_FIlES
    utils/misc.cpp
    utils/misc.h
)

add_executable(sleeper
    main.cpp
    ${APP_FILES}
    ${UI_FILES}
    ${UTILS_FIlES}
    ${RESOURCE_DIR}/resources.qrc
)

set_target_properties(sleeper PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Libraties

# FIND QT ###################################

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets DBus REQUIRED)

# link libraries

target_link_libraries(sleeper PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt::DBus
)
