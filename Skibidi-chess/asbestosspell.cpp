#include "asbestosspell.h"

AsbestosSpell::AsbestosSpell(int posX, int posY): Spell::Spell(posX, posY) {
    this->lifespan = 3;
    this->cost = 3;
    this->name = "asbestos";
}

bool AsbestosSpell::isFieldAffected(int posX, int posY) const
{
    return (std::max(std::abs(this->posX - posX), std::abs(this->posY - posY)) <= 1);
}
