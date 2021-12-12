#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <random>
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
#include "../rules/Rules.h"
#include "../controllers/EnemyController.h"
#include "../controllers/PlayerController.h"


template<class Rules>
class Game: public BasePublisher{
private:
    Rules rules;
    Field *field;
    std::vector<Entity*> enemies;
    std::vector<Entity*> items;
    std::vector<EnemyController*> controllers;
    BaseController *pc;
    ConsoleFieldView fv;


    void initField(){
        field = FieldBuilder().setSize(rules.getFieldCharacteristics().getX(),
                                       rules.getFieldCharacteristics().getY()).
                                               setType(rules.getFieldCharacteristics().getFieldType()).build();
       if(!(this->loggers.empty())){
           for(auto &logger : loggers){
               field->addNewLogger(logger);
           }
       }

    }

    void putEnemies(){
        createEnemies();

        for(auto &enemy: enemies){
            for(auto &logger : loggers){
               enemy->addNewLogger(logger);
            }
        }

        for(int i = 0; i < enemies.size(); ){
            std::random_device rd;
            std::mt19937 mersenne(rd());

            int x = mersenne() % field->getX(),
                y = mersenne() % field->getY();

            if(!(dynamic_cast<Wall*>(field->getCell(x, y))) && !(dynamic_cast<Entry*>(field->getCell(x, y)))
                && !(dynamic_cast<Exit*>(field->getCell(x, y)))  && field->getCell(x, y)->getEntity() == nullptr){

                controllers.push_back(new EnemyController(enemies[i], field, x, y));
                field->getCell(x, y)->putEntity(enemies[i++]);

            }
        }

    }

    void createEnemies(){
        for(int i = 0; i < rules.getEnemyCount().getLightEnemyCount(); i++){
            EnemyFactory *LightFactory = new LightEnemyFactory();
            Entity *lightEnemy = LightFactory->create();
            enemies.push_back(lightEnemy);
        }

        for(int i = 0; i < rules.getEnemyCount().getMediumEnemyCount(); i++){
            EnemyFactory *MediumFactory = new MediumEnemyFactory();
            Entity *mediumEnemy = MediumFactory->create();
            enemies.push_back(mediumEnemy);
        }

        for(int i = 0; i < rules.getEnemyCount().getHeavyEnemyCount(); i++){
            EnemyFactory *HeavyFactory = new HeavyEnemyFactory();
            Entity *heavyEnemy = HeavyFactory->create();
            enemies.push_back(heavyEnemy);
        }
    }

    void putItems(){
        createItems();

        for(auto &item: items){
            for(auto &logger : loggers){
                item->addNewLogger(logger);
            }
        }

        for(int i = 0; i < items.size(); ) {
            std::random_device rd;
            std::mt19937 mersenne(rd());

            int x = mersenne() % field->getX(),
                    y = mersenne() % field->getY();

            if (!(dynamic_cast<Wall *>(field->getCell(x, y))) && !(dynamic_cast<Entry *>(field->getCell(x, y)))
                && !(dynamic_cast<Exit *>(field->getCell(x, y))) && field->getCell(x, y)->getEntity() == nullptr) {
                field->getCell(x, y)->putEntity(items[i++]);
            }
        }
    }

    void createItems(){
        for(int i = 0; i < rules.getItemsCount().getHealItemCount(); i++){
            ItemFactory *HFactory = new HealFactory();
            Entity *Hitem = HFactory->create(10);
            items.push_back(Hitem);
        }

        for(int i = 0; i < rules.getItemsCount().getArmorItemCount(); i++){
            ItemFactory *AFactory = new ArmorFactory();
            Entity *Aitem = AFactory->create(10);
            items.push_back(Aitem);
        }

        for(int i = 0; i < rules.getItemsCount().getDmgItemCount(); i++){
            ItemFactory *DFactory = new DmgFactory();
            Entity *Ditem = DFactory->create(10);
            items.push_back(Ditem);
        }
    }

    void putPlayer(){
        Entity *player = new Player(rules.getPlayerCharacteristics().getHp(),
                                    rules.getPlayerCharacteristics().getDmg(),
                                    rules.getPlayerCharacteristics().getArmor());

        for(auto &logger : loggers){
            player->addNewLogger(logger);
        }

        if(rules.getFieldCharacteristics().getFieldType() == FieldBuilder::DEFAULT){
            field->getCell(0, 0)->putEntity(player);
            pc = new PlayerController(player, field, 0, 0);
        }

        else if(rules.getFieldCharacteristics().getFieldType() == FieldBuilder::BOX
                                                            || rules.getFieldCharacteristics().getFieldType() == FieldBuilder::RANDOM){
            field->getCell(1, 1)->putEntity(player);
            pc = new PlayerController(player, field, 1, 1);
        }

    }

    void addLoggers(std::shared_ptr<BaseLogger> consoleLogger, std::shared_ptr<BaseLogger> fileLogger){
        if(consoleLogger)
            this->addNewLogger(consoleLogger);
        if(fileLogger)
            this->addNewLogger(fileLogger);
    }

    void init(){
        initField();
        putPlayer();
        putEnemies();
        putItems();
    }

    bool getWin(){
        if(dynamic_cast<Exit*>(field->getCell(pc->getX(), pc->getY())))
            return false;
        return true;
    }


    void display(){
        if(!fv.getField())
            fv.setField(field);

        std::cout << fv << std::endl;
    }

public:
    Game(Rules rules, std::shared_ptr<BaseLogger>consoleLogger=nullptr, std::shared_ptr<BaseLogger>fileLogger=nullptr): rules(rules){
        addLoggers(consoleLogger, fileLogger);
        init();
    }

    void start(){
        display();
        do{
            if(pc->move()){
                for(auto controller: controllers)
                    controller->move();
                display();
            }
        }while(getWin());
    }

    ~Game() = default;

};

#endif //GAME_H
