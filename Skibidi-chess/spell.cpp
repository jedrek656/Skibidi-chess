#include "spell.h"
#include <qassert.h>

Spell::Spell() {}

void Spell::castSpell()
{

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
