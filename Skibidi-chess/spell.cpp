#include "spell.h"
#include <qassert.h>
#include <QDebug>

Spell::Spell(int posX, int posY, int spellIdx) {
    this->posX = posX;
    this->posY = posY;
    this->lifespan = 4;
    switch(spellIdx){
    case 0:
        this->name = "Hawk Tuah";
        this->lifespan = 2;
        break;
    case 1:
        this->name = "Asbestos";
        break;
    case 2:
        this->name = "Cheese Drippy";
        break;
    }
}

bool Spell::decreaseDuration()
{
    Q_ASSERT(lifespan >= 0);
    if(this->lifespan == 0){
        return true;
    }
    this->lifespan -= 1;
    return false;
}

bool Spell::isFieldAffected(int posX, int posY) const
{
    return (posX==this->posX && posY==this->posY);
}

QVariantList Spell::getSpell() const
{
    return {this->name, this->posX, this->posY, this->lifespan};
}
