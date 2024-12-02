#include "player.h"
#include <qassert.h>

Player::Player(bool isWhite) {
    this->isWhite = isWhite;
}

int Player::get_mana() const {
    return this->mana;
}

void Player::subtract_mana(int spell_cost) {
    Q_ASSERT(this->mana >= spell_cost);
    this->mana -= spell_cost;
}
