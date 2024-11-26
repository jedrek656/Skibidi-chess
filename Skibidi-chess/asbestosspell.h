#ifndef ASBESTOSSPELL_H
#define ASBESTOSSPELL_H

#include "spell.h"

class AsbestosSpell: public Spell
{
public:
    AsbestosSpell(int posX, int posY);
    bool isFieldAffected(int posX, int posY) const override;
};

#endif // ASBESTOSSPELL_H
