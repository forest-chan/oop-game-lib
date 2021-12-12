#ifndef ITEMSCOUNTTEMPLATE_H
#define ITEMSCOUNTTEMPLATE_H

template<typename T>
class ItemsCountTemplate{
public:
    ItemsCountTemplate(T healItemCount, T dmgItemCount, T armorItemCount): healItemCount(healItemCount), dmgItemCount(dmgItemCount),
                                                                            armorItemCount(armorItemCount){
        static_assert(std::is_same<T, int>::value, "template instantiation of Class are not int");
    }

    T getHealItemCount(){
        return healItemCount;
    }

    T getArmorItemCount(){
        return armorItemCount;
    }

    T getDmgItemCount(){
        return dmgItemCount;
    }


private:
    T healItemCount, dmgItemCount, armorItemCount;
};

#endif //ITEMSCOUNTTEMPLATE_H
