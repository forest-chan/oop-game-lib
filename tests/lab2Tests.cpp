#include <iostream>
#include <memory>
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


int main(){
    Field *f = FieldBuilder().setSize(5, 5).setType(FieldBuilder::BOX).build(); //создали поле, вывели в консоль
    ConsoleFieldView fv(f);
    std::cout << fv << std::endl;


    Entity *player = new Player(100, 100, 100); //создаем игрока, врагов и вещи
    EnemyFactory *LightFactory = new LightEnemyFactory();
    EnemyFactory *MediumFactory = new MediumEnemyFactory();
    Entity *enemy1 = LightFactory->create();
    Entity *enemy2 = MediumFactory->create();


    ItemFactory *HFactory = new HealFactory();
    ItemFactory *DFactory = new DmgFactory();
    ItemFactory *AFactory = new ArmorFactory();
    Entity *Hitem = HFactory->create(100);
    Entity *Ditem = DFactory->create(100);
    Entity *Aitem = AFactory->create(100);

    std::shared_ptr<BaseLogger> logger1 = std::make_shared<ConsoleLogger>();
    std::shared_ptr<BaseLogger> logger2 = std::make_shared<FileLogger>();

    f->addNewLogger(logger1);
    f->addNewLogger(logger2);

    player->addNewLogger(logger1);
    player->addNewLogger(logger2);

    enemy1->addNewLogger(logger1);
    enemy1->addNewLogger(logger2);

    Hitem->addNewLogger(logger1);
    Hitem->addNewLogger(logger2);

    Ditem->addNewLogger(logger1);
    Ditem->addNewLogger(logger2);

    Aitem->addNewLogger(logger1);
    Aitem->addNewLogger(logger2);


    f->getCell(2,1)->putEntity(player); //устанавливаем сущности(игрока, врагов, вещи) на игровое поле
    f->getCell(3,1)->putEntity(enemy1);
    f->getCell(3,2)->putEntity(Hitem);
    std::cout << fv << std::endl;

    f->getCell(3,1)->moveTo(f->getCell(2,1)); //тест передвижения + взаидодействия сущностей на поле
    //std::cout << "player hp = " << dynamic_cast<Player*>(player)->getHp() << "\n" << "enemy hp = " << dynamic_cast<Enemy*>(enemy1)->getHp() << std::endl;
    std::cout << fv << std::endl;

    f->getCell(3,2)->moveTo(f->getCell(3,1));
    //std::cout << "player hp = " << dynamic_cast<Player*>(player)->getHp() << "\n";
    std::cout << fv << std::endl;

    //тест взаимодействия
    /*std::cout << "player hp = " << dynamic_cast<Player*>(player)->getHp() << "\n" << "enemy hp = " << dynamic_cast<Enemy*>(enemy2)->getHp() << std::endl;
    player->interact(enemy2);
    enemy2->interact(player);
    std::cout << "player hp = " << dynamic_cast<Player*>(player)->getHp() << "\n" << "enemy hp = " << dynamic_cast<Enemy*>(enemy2)->getHp() << std::endl;

    player->interact(Hitem);
    player->interact(Aitem);
    player->interact(Ditem);
    std::cout << "player hp = " << dynamic_cast<Player*>(player)->getHp() << " player armor = "<< dynamic_cast<Player*>(player)->getArmor() << " player dmg = "<< dynamic_cast<Player*>(player)->getDmg() << "\n";*/

    f->deleteLogger(logger1);
    f->deleteLogger(logger2);

    player->deleteLogger(logger1);
    player->deleteLogger(logger2);

    enemy1->deleteLogger(logger1);
    enemy1->deleteLogger(logger2);

    Hitem->deleteLogger(logger1);
    Hitem->deleteLogger(logger2);

    Ditem->deleteLogger(logger1);
    Ditem->deleteLogger(logger2);

    Aitem->deleteLogger(logger1);
    Aitem->deleteLogger(logger2);
}