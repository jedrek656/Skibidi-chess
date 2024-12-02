#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(bool isWhite);
    int get_mana() const;
    void subtract_mana(int spell_cost);
    bool isWhite;
protected:

    int mana;
    int time_left;
};

#endif // PLAYER_H
