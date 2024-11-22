#ifndef SPELL_H
#define SPELL_H

class Spell
{
public:
    Spell();
    void castSpell();
    bool decreaseDuration();


protected:
    int cost = 0;
    int lifespan = 0;
};

#endif // SPELL_H
