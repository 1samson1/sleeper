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

# Compiler options

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()


# Libraties

# FIND QT ###################################

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets DBus REQUIRED)

# link libraries

target_link_libraries(sleeper PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
)

if(UNIX)
    target_link_libraries(sleeper PUBLIC Qt::DBus)
endif()
