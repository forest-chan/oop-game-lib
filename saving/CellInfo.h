#ifndef CELLINFO_H
#define CELLINFO_H

#include "../Field/Cells/BaseCell.h"
#include "../Field/Cells/Cell.h"
#include "../Field/Cells/Exit.h"
#include "../Field/Cells/Entry.h"
#include "../Field/Cells/Wall.h"


class CellInfo{
public:
    bool isWall;
    bool isExit;
    bool isEntry;
    bool isPlayer;
    bool isEnemy;
    bool isHealItem;
    bool isDmgItem;
    bool isArmorItem;
    int hp, dmg, armor;
    int value;

    CellInfo(){}

    CellInfo(BaseCell *cell){
        this->isPlayer = cell->isPlayer();
        this->isEnemy = cell->isEnemy();
        this->isHealItem = cell->isHealItem();
        this->isDmgItem = cell->isDmgItem();
        this->isArmorItem = cell->isArmorItem();

        if(dynamic_cast<Wall*>(cell)){
            this->isWall = true;
            this->isExit = false;
            this->isEntry = false;
        }

        else if(dynamic_cast<Exit*>(cell)){
            this->isWall = false;
            this->isExit = true;
            this->isEntry = false;
        }

        else if(dynamic_cast<Entry*>(cell)){
            this->isWall = false;
            this->isExit = false;
            this->isEntry = true;
        }


        if(this->isPlayer || this->isEnemy){
            this->hp = dynamic_cast<Creature*>(cell->getEntity())->getHp();
            this->dmg = dynamic_cast<Creature*>(cell->getEntity())->getDmg();
            this->armor = dynamic_cast<Creature*>(cell->getEntity())->getArmor();
        }

        else if(this->isHealItem || this->isDmgItem || this->isArmorItem){
            this->value = dynamic_cast<Item*>(cell->getEntity())->getValue();
        }
    }

};

#endif //CELLINFO_H
