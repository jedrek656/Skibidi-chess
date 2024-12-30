#include <gtest/gtest.h>
#include "spell.h"
#include "App/spelllist.h"

TEST(spelllist, decrease_duration)
{
    SpellList list;
    list.setActiveSpell(1);
    list.castSpell(2, 3);
    list.castSpell(4, 6);
    list.castSpell(7, 1);
    list.updateLifespans();
    for (auto &spell: *list.getSpells()){
        EXPECT_EQ(spell->getSpell()[3], 2);
        EXPECT_EQ(spell->getSpell()[3], 2);
        EXPECT_EQ(spell->getSpell()[3], 2);
    }
}
