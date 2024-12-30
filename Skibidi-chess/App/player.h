#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(bool isWhite);
    int getMana() const;
    void assignMana(int new_mana);
    void subtractMana(int spell_cost);
    void addMana();
    bool isWhite;
private:
    int mana;
    int toNextMana;
};

#endif // PLAYER_H
