#include "EntityView.h"

EntityView::EntityView() : ConsoleObjectView<Entity>(
        {
                {typeid(Enemy).hash_code(),  'e'},
                {typeid(Player).hash_code(), 'p'},
                {typeid(HealItem).hash_code(),   'h'},
                {typeid(DmgItem).hash_code(),   'd'},
                {typeid(ArmorItem).hash_code(),   'a'}
        }
) {}

char EntityView::getChar(const Entity &c) {
    return chars.at(typeid(c).hash_code());
}