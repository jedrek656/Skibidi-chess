#ifndef SPELL_H
#define SPELL_H

#include <QString>

class Spell
{
public:
    Spell(int posX, int posY);
    void castSpell();
    bool decreaseDuration();
    virtual bool isFieldAffected(int posX, int posY) const;


protected:
    int cost;
    int lifespan;
    int posX;
    int posY;
    QString name;
};

#endif // SPELL_H
