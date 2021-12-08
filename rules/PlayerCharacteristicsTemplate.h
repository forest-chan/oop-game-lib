#ifndef BASECREATURETEMPLATE_H
#define BASECREATURETEMPLATE_H

template<typename T>
class PlayerCharacteristicsTemplate{
public:
    PlayerCharacteristicsTemplate(T hp, T dmg, T armor): hp(hp), dmg(dmg), armor(armor){}

    virtual T getHp(){
        return hp;
    }

    virtual T getDmg(){
        return dmg;
    }

    virtual T getArmor(){
        return armor;
    }

private:
    T hp, dmg, armor;
};

#endif //BASECREATURETEMPLATE_H
