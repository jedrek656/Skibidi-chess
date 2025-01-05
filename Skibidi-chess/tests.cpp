#include <gtest/gtest.h>
#include "spell.h"
#include "App/game.h"

std::unique_ptr<Game> prepareGame(){
    auto game = std::make_unique<Game>();
    return game;
}

TEST(spell, decrease_duration)
{
    Spell spell(2, 2, 1);
    int spellDuration = spell.getSpell()[3].toInt();
    spell.decreaseDuration();
    ASSERT_EQ(spell.getSpell()[3].toInt(), spellDuration - 1);
}
