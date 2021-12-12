#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

#include "BaseController.h"

class EnemyController: public BaseController{
public:
    EnemyController(Entity *object, Field *field, unsigned startPositionX, unsigned startPositionY):
                                                                    BaseController(object, field, startPositionX, startPositionY){}
};

#endif //ENEMYCONTROLLER_H
