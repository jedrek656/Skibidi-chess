#include "player.h"
#include <qassert.h>

#define MAX_MANA 10

Player::Player(bool isWhite) {
    this->isWhite = isWhite;
    this->mana = 3;
    this->toNextMana = 0;
}

int Player::getMana() const {
    return this->mana;
}

void Player::subtractMana(int spell_cost) {
    Q_ASSERT(this->mana >= spell_cost);
    this->mana -= spell_cost;
}

void Player::addMana()
{
    if (this->toNextMana == 2){
        this->toNextMana = 0;
        this->mana = std::min(this->mana + 1, MAX_MANA);
        return;
    }
    this->toNextMana++;
}
