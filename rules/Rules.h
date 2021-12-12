#ifndef RULES_H
#define RULES_H



template<class Enemy, class Player, class Field, class Item>
class Rules{
public:
    Rules(Enemy enemyCount, Player playerCharacteristics, Field fieldCharacteristics, Item itemsCount): enemyCount(enemyCount), playerCharacteristics(playerCharacteristics),
                                fieldCharacteristics(fieldCharacteristics), itemsCount(itemsCount){}

    Enemy &getEnemyCount(){
        return enemyCount;
    }

    Player &getPlayerCharacteristics(){
        return playerCharacteristics;
    }

    Field &getFieldCharacteristics(){
        return fieldCharacteristics;
    }

    Item &getItemsCount(){
        return itemsCount;
    }

private:
    Enemy   enemyCount;
    Player  playerCharacteristics;
    Field   fieldCharacteristics;
    Item    itemsCount;

};


#endif //RULES_H
