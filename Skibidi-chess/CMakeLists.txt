
cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(example_test)
add_subdirectory(external)
include(CTest)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Gui Qml Quick Widgets)
qt_standard_project_setup()
qt_add_executable(example_test
    tests.cpp
    App/game.h App/game.cpp
    App/chessboard.h App/chessboard.cpp
    chesspiece.h chesspiece.cpp
    pawn.h pawn.cpp
    rook.h rook.cpp

    queen.h queen.cpp
    bishop.h bishop.cpp

    knight.h knight.cpp
    king.h king.cpp
    App/spelllist.h App/spelllist.cpp
    spell.h spell.cpp

    App/player.h App/player.cpp
    App/dummypiece.h App/dummypiece.cpp
    )

target_link_libraries(example_test PRIVATE GTest::gtest_main)
target_link_libraries(example_test PRIVATE Qt6::Gui)
target_link_libraries(example_test PRIVATE Qt6::Widgets)
include(GoogleTest)

project(SkibidiApp LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Gui Qml Quick Widgets)
qt_standard_project_setup()


qt_add_executable(${CMAKE_PROJECT_NAME}

    App/game.h App/game.cpp
    App/chessboard.h App/chessboard.cpp
    chesspiece.h chesspiece.cpp
    pawn.h pawn.cpp
    rook.h rook.cpp

    queen.h queen.cpp
    bishop.h bishop.cpp

    knight.h knight.cpp
    king.h king.cpp
    App/spelllist.h App/spelllist.cpp
    spell.h spell.cpp

    App/player.h App/player.cpp
    uml2.qmodel
    App/dummypiece.h App/dummypiece.cpp
)

qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf)

include(qds)

if (BUILD_QDS_COMPONENTS)
    include(qmlcomponents OPTIONAL)
endif()

if (LINK_INSIGHT)
    include(insight OPTIONAL)
endif ()

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
