#include "spell.h"
#include <qassert.h>
#include <QDebug>

Spell::Spell(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
}

void Spell::castSpell()
{

}

bool Spell::decreaseDuration()
{
    Q_ASSERT(lifespan >= 0);
    qDebug() << this->lifespan;
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
