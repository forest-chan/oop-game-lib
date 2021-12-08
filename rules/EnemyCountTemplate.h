#ifndef ENEMYTEMPLATE_H
#define ENEMYTEMPLATE_H

template<typename T>
class EnemyCountTemplate{
public:
    EnemyCountTemplate(T lightEnemyCount, T mediumEnemyCount, T heavyEnemyCount): lightEnemyCount(lightEnemyCount), mediumEnemyCount(mediumEnemyCount), heavyEnemyCount(heavyEnemyCount){
        static_assert(std::is_same<T, int>::value, "template instantiation of Class are not int");
    }

    T getLightEnemyCount(){
        return lightEnemyCount;
    }

    T getMediumEnemyCount(){
        return mediumEnemyCount;
    }

    T getHeavyEnemyCount(){
        return heavyEnemyCount;
    }

private:
    T lightEnemyCount, mediumEnemyCount, heavyEnemyCount;
};

#endif //ENEMYTEMPLATE_H
