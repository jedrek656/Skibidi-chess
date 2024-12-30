#ifndef SPELL_H
#define SPELL_H

#include <QString>
#include <QVariantList>

class Spell
{
public:
    Spell(int posX, int posY, int spellIdx);
    bool decreaseDuration();
    virtual bool isFieldAffected(int posX, int posY) const;
    QVariantList getSpell() const;
    std::pair<int, int> getPos() const;
    void changeLifespan(int life);


protected:
    int cost;
    int lifespan;
    int posX;
    int posY;
    QString name;
};

#endif // SPELL_H
