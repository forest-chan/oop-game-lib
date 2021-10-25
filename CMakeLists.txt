cmake_minimum_required(VERSION 3.19)
project(oop_game)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_HEADERS
        Entities/Entity.h
        Field/Cells/BaseCell.h
        Field/Cells/Cell.h
        Field/Cells/Entry.h
        Field/Cells/Exit.h
        Field/Cells/Wall.h
        Field/Field.h
        Field/FieldBuilder.h
        Viewers/FieldView.h
        Viewers/CellView.h Viewers/ConsoleFieldView.h)

set(PROJECT_SOURCES
        Field/Field.cpp
        Field/FieldBuilder.cpp
        main.cpp
        Viewers/CellView.cpp
        Viewers/ConsoleFieldView.cpp)

add_executable(oop_game ${PROJECT_HEADERS} ${PROJECT_SOURCES})