#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <fstream>
#include <string>
#include <iostream>
#include "CellInfo.h"
#include "FieldInfo.h"
#include "../Field/Field.h"



struct SuccessfulSave{
    int p, ex, en;
};


class Serialization{
private:
    Field *field;
    CellInfo ***cellsInfo;
    FieldInfo *fieldInfo;
    std::string ci = "saving/cellInf.txt";
    std::string fi = "saving/fieldInfo.txt";

public:
    Serialization(Field* field): field(field){}

    void writeCellsToFile(){
        std::ofstream f(ci, std::ios::binary);
        if(!f.is_open())
            throw "an error during opening the preservation file! please, reload game and try again";

        cellsInfo = new CellInfo **[field->getY()];
        for(int i = 0; i < field->getY(); i++){
            cellsInfo[i] = new CellInfo *[field->getX()];
            for(int j = 0; j < field->getX(); j++){
                cellsInfo[i][j] = new CellInfo(field->getCell(i, j));
            }
        }
        bool p, e, hit, dit, ait;
        int hp, dmg, armor, value;
        bool w, ex, en;

        for(int i = 0; i < field->getX(); i++){
            for(int j = 0; j < field->getY(); j++){
                p = cellsInfo[j][i]->isPlayer;
                e = cellsInfo[j][i]->isEnemy;
                hit = cellsInfo[j][i]->isHealItem;
                ait = cellsInfo[j][i]->isArmorItem;
                dit = cellsInfo[j][i]->isDmgItem;
                hp = cellsInfo[j][i]->hp;
                dmg = cellsInfo[j][i]->dmg;
                armor = cellsInfo[j][i]->armor;
                value = cellsInfo[j][i]->value;
                w = cellsInfo[j][i]->isWall;
                ex = cellsInfo[j][i]->isExit;
                en = cellsInfo[j][i]->isEntry;
                f.write(reinterpret_cast<const char *>(&w), sizeof(w));
                f.write(reinterpret_cast<const char *>(&ex), sizeof(ex));
                f.write(reinterpret_cast<const char *>(&en), sizeof(en));
                f.write(reinterpret_cast<const char *>(&p), sizeof(p));
                f.write(reinterpret_cast<const char *>(&e), sizeof(e));
                f.write(reinterpret_cast<const char *>(&hit), sizeof(hit));
                f.write(reinterpret_cast<const char *>(&dit), sizeof(dit));
                f.write(reinterpret_cast<const char *>(&ait), sizeof(ait));
                f.write(reinterpret_cast<const char *>(&hp), sizeof(hp));
                f.write(reinterpret_cast<const char *>(&dmg), sizeof(dmg));
                f.write(reinterpret_cast<const char *>(&armor), sizeof(armor));
                f.write(reinterpret_cast<const char *>(&value), sizeof(value));
            }
        }

        f.close();
    }

    CellInfo ***readCellsFromFile(){
        std::ifstream f;
        f.open(ci, std::ios::binary);
        if(!f.is_open())
            throw "file could not be opened! please, create new preservation";

        cellsInfo = new CellInfo **[field->getY()];
        for(int i = 0; i < field->getY(); i++){
            cellsInfo[i] = new CellInfo *[field->getX()];
            for(int j = 0; j < field->getX(); j++){
                cellsInfo[i][j] = new CellInfo();
            }
        }

        for(int i = 0; i < field->getY(); i++){
            for(int j = 0; j < field->getX(); j++){
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isWall)), sizeof(cellsInfo[i][j]->isWall));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isExit)), sizeof(cellsInfo[i][j]->isExit));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isEntry)), sizeof(cellsInfo[i][j]->isEntry));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isPlayer)), sizeof(cellsInfo[i][j]->isPlayer));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isEnemy)), sizeof(cellsInfo[i][j]->isEnemy));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isHealItem)), sizeof(cellsInfo[i][j]->isHealItem));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isDmgItem)), sizeof(cellsInfo[i][j]->isDmgItem));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->isArmorItem)), sizeof(cellsInfo[i][j]->isArmorItem));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->hp)), sizeof(cellsInfo[i][j]->hp));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->dmg)), sizeof(cellsInfo[i][j]->dmg));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->armor)), sizeof(cellsInfo[i][j]->armor));
                f.read(const_cast<char *>(reinterpret_cast<const char *>(&cellsInfo[i][j]->value)), sizeof(cellsInfo[i][j]->value));
            }

        }

        f.close();
        return cellsInfo;
    }

    void writeFieldToFile(){
        std::ofstream f;
        f.open(fi, std::ios::binary);
        if(!f.is_open())
            throw "an error during opening the preservation file! please, reload game and try again";

        fieldInfo = new FieldInfo(field->getX(), field->getY());

        int x, y;
        x = fieldInfo->x;
        y = fieldInfo->y;

        f.write(reinterpret_cast<const char *>(&x), sizeof(x));
        f.write(reinterpret_cast<const char *>(&y), sizeof(y));

        f.close();
    }

    FieldInfo *readFieldFromFile(){
        std::ifstream f(fi, std::ios::binary);
        if(!f.is_open())
            throw "file could not be opened! please, create new preservation";

        fieldInfo = new FieldInfo();

        f.read(const_cast<char *>(reinterpret_cast<const char *>(&fieldInfo->x)), sizeof(fieldInfo->x));
        f.read(const_cast<char *>(reinterpret_cast<const char *>(&fieldInfo->y)), sizeof(fieldInfo->y));

        f.close();
        return fieldInfo;
    }
};

#endif //SERIALIZATION_H
