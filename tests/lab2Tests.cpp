#include <iostream>
#include <memory>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>
#include "../Field/Field.h"
#include "../Field/FieldBuilder.h"
#include "../Viewers/console/ConsoleFieldView.h"
#include "../Viewers/FieldView.h"
#include "../Entities/Creatures/Creature.h"
#include "../Entities/Creatures/Enemies/Enemy.h"
#include "../Entities/Items/Item.h"
#include "../Entities/Items/ItemFactory.h"
#include "../Entities/Creatures/Enemies/EnemyFactory.h"
#include "../logging/loggers/BaseLogger.h"
#include "../logging/loggers/ConsoleLogger.h"
#include "../logging/loggers/FileLogger.h"
#include "../logging/Log.h"
#include "../logging/BasePublisher.h"
#include "../rules/Rules.h"
#include "../rules/EnemyCountTemplate.h"
#include "../rules/ItemsCountTemplate.h"
#include "../rules/PlayerCharacteristicsTemplate.h"
#include "../rules/FieldCharacteristicsTemplate.h"
#include "../game/Game.h"



int main(){
    Rules<EnemyCountTemplate<int>, PlayerCharacteristicsTemplate<int>,
            FieldCharacteristicsTemplate<int>, ItemsCountTemplate<int>> rules(
                    EnemyCountTemplate<int> (1, 1, 1), PlayerCharacteristicsTemplate<int> (100, 100, 100),
                    FieldCharacteristicsTemplate<int> (7, 7, FieldBuilder::RANDOM), ItemsCountTemplate<int> (1, 1, 1)
                    );

    Game <Rules<EnemyCountTemplate<int>, PlayerCharacteristicsTemplate<int>,
            FieldCharacteristicsTemplate<int>, ItemsCountTemplate<int>>> game(
                    rules, nullptr, std::make_shared<FileLogger>()
                            );


    game.start();
}