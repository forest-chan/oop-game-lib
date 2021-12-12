cmake_minimum_required(VERSION 3.19)
project(oop_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lncurses")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

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
        Viewers/console/CellView.h
        Viewers/console/ConsoleFieldView.h
        Entities/Entities_Declarations.h
        Entities/Creatures/Creature.h
        Entities/Creatures/Enemies/Enemy.h
        Entities/Items/Item.h Entities/Creatures/Player.h Entities/Items/ItemFactory.h Entities/Creatures/Enemies/EnemyFactory.h Viewers/Viewers_Declarations.h Viewers/console/ConsoleObjectView.h Viewers/console/EntityView.h logging/BasePublisher.h logging/loggers/BaseLogger.h logging/loggers/ConsoleLogger.h logging/loggers/FileLogger.h logging/Log.h rules/PlayerCharacteristicsTemplate.h rules/EnemyCountTemplate.h rules/Rules.h rules/FieldCharacteristicsTemplate.h rules/ItemsCountTemplate.h game/Game.h controllers/BaseController.h controllers/EnemyController.h controllers/PlayerController.h)

set(PROJECT_SOURCES
        Field/Field.cpp
        Field/FieldBuilder.cpp
        tests/lab2Tests.cpp
        Viewers/console/CellView.cpp
        Viewers/console/ConsoleFieldView.cpp Viewers/console/EntityView.cpp logging/loggers/BaseLogger.h)

add_executable(oop_game ${PROJECT_HEADERS} ${PROJECT_SOURCES})
target_link_libraries(oop_game ${CURSES_LIBRARIES})