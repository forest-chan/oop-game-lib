#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <random>
#include <memory>
#include <fstream>
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
#include "../saving/CellInfo.h"
#include "../saving/FieldInfo.h"
#include "../saving/Serialization.h"


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
    Serialization *s;
    CellInfo ***cellsInfo;
    FieldInfo *fieldInfo;
    SuccessfulSave *save;

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
            delete LightFactory;
        }

        for(int i = 0; i < rules.getEnemyCount().getMediumEnemyCount(); i++){
            EnemyFactory *MediumFactory = new MediumEnemyFactory();
            Entity *mediumEnemy = MediumFactory->create();
            enemies.push_back(mediumEnemy);
            delete MediumFactory;
        }

        for(int i = 0; i < rules.getEnemyCount().getHeavyEnemyCount(); i++){
            EnemyFactory *HeavyFactory = new HeavyEnemyFactory();
            Entity *heavyEnemy = HeavyFactory->create();
            enemies.push_back(heavyEnemy);
            delete HeavyFactory;
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
            delete HFactory;
        }

        for(int i = 0; i < rules.getItemsCount().getArmorItemCount(); i++){
            ItemFactory *AFactory = new ArmorFactory();
            Entity *Aitem = AFactory->create(10);
            items.push_back(Aitem);
            delete AFactory;
        }

        for(int i = 0; i < rules.getItemsCount().getDmgItemCount(); i++){
            ItemFactory *DFactory = new DmgFactory();
            Entity *Ditem = DFactory->create(10);
            items.push_back(Ditem);
            delete DFactory;
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
        fv.setField(field);
        std::cout << fv << std::endl;
    }

    void fieldLoader(){
        controllers.clear();
        for(int i = 0; i < field->getY(); i++){
            for(int j = 0; j < field->getX(); j++){
                if(cellsInfo[i][j]->isPlayer){
                    Entity *player = new Player(cellsInfo[i][j]->hp, cellsInfo[i][j]->dmg, cellsInfo[i][j]->armor);
                    pc = new PlayerController(player, field, j, i);
                }
                else if(cellsInfo[i][j]->isEnemy){
                    Entity *enemy = new Enemy(cellsInfo[i][j]->hp, cellsInfo[i][j]->dmg, cellsInfo[i][j]->armor);
                    EnemyController *c = new EnemyController(enemy, field, j, i);
                    controllers.push_back(c);
                }

            }
        }
    }

    bool fieldAnalyzer(Field *f){
        bool ok = false;
        for(int i = 0; i < f->getY(); i++){
            for(int j = 0; j < f->getX(); j++){
                if(dynamic_cast<Entry*>(f->getCell(i, j)))
                    save->en = 1;
                else if(dynamic_cast<Exit*>(f->getCell(i, j)))
                    save->ex = 1;
                if(dynamic_cast<Player*>(f->getCell(i, j)->getEntity()))
                    save->p  = 1;
            }
        }

        if(save->ex == 1 && save->en == 1 && save->ex == 1)
            ok = true;

        save->en = save->ex = save->p = 0;

        if(ok)
            return true;
        return false;
    }

    bool load(){
        if(fieldInfo->x > MAX_FIELD_WIDTH || fieldInfo->x < MIN_FIELD_WIDTH || fieldInfo->y > MAX_FIELD_HEIGHT || fieldInfo->y < MIN_FIELD_HEIGHT){
            throw "the game could not be loaded, the save file may be damaged";
        }

        Field *f1 = FieldBuilder().createFromInfo(cellsInfo, fieldInfo);
        if(fieldAnalyzer(f1)){
            field = f1;

            pc->setField(field);
            for(auto controller: controllers)
                controller->setField(field);
            fieldLoader();
            return true;
        }
        throw "the game could not be loaded, the save file may be damaged";
    }


public:
    Game(Rules rules, std::shared_ptr<BaseLogger>consoleLogger=nullptr, std::shared_ptr<BaseLogger>fileLogger=nullptr): rules(rules){
        addLoggers(consoleLogger, fileLogger);
        init();
        s = new Serialization(field);
        save = new SuccessfulSave{0, 0, 0};
    }

    void start(){
        std::string current_action = "";
        display();
        do{
            current_action = pc->move();

            if(current_action == "success"){
                for(auto controller: controllers)
                    controller->move();
            }
            else if(current_action == "fail"){
                continue;
            }
            else if(current_action == "save"){
                s->writeFieldToFile();
                s->writeCellsToFile();
                std::cout << "game successfully saved" << std::endl;
            }
            else if(current_action == "load"){
                try{
                    fieldInfo = s->readFieldFromFile();
                    cellsInfo = s->readCellsFromFile();
                    load();
                    std::cout << "game successfully loaded"<< std::endl;
                }
                catch(char const *error){
                    std::cerr << error << std::endl;
                    std::cout << "continue the last game" << std::endl;
                }
            }
            display();
        }while(getWin());
        std::cout << "\tGame successfully passed!\t\n\tCONGRATULATIONS!"<< std::endl;
    }

    ~Game(){
        delete pc;
        delete s;
        for(auto &c: controllers){
            delete c;
        }
    }

};

#endif //GAME_H
