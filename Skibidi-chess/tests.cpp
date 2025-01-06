#include <gtest/gtest.h>
#include "spell.h"
#include "App/game.h"
#include "App/chessboard.h"

Game *prepareGame(){
    auto game = new Game;
    auto chessBoard = new ChessBoard;
    auto spellList = new SpellList;

    game->setChessboard(chessBoard);
    chessBoard->setSpellList(spellList);
    spellList->setGame(game);
    return game;
}

void freeMem(Game *game){
    delete game->getChessboard()->getSpellList();
    delete game->getChessboard();
    delete game;
};

TEST(spell, decrease_duration)
{
    Spell spell(2, 2, 1);
    int spellDuration = spell.getSpell()[3].toInt();
    spell.decreaseDuration();
    ASSERT_EQ(spell.getSpell()[3].toInt(), spellDuration - 1);
}

TEST(spell, decrease_duration_in_list)
{
    Game *game = prepareGame();
    SpellList *spellList = game->getChessboard()->getSpellList();
    spellList->addSpellDirectly("Hawk Tuah", 3, 4, 3);
    spellList->addSpellDirectly("Asbestos", 1, 2, 4);
    spellList->updateLifespans();
    auto spells = spellList->getSpells();
    int duration1 = (*spells)[0]->getSpell()[3].toInt();
    int duration2 = (*spells)[1]->getSpell()[3].toInt();
    ASSERT_EQ(duration1, 2);
    ASSERT_EQ(duration2, 3);
    freeMem(game);
}

TEST(chessboard, possibleMoves1)
{
    Game *game = prepareGame();
    ChessBoard *chessBoard = game->getChessboard();
    chessBoard->loadPosition();
    chessBoard->movePiece(13, 4, 4);
    chessBoard->movePiece(6, 4, 3);     //E4, E5, CHECK IF E4 PAWN CANT MOVE
    ASSERT_EQ(chessBoard->getPossibleMoves(13).size(), 0);
    freeMem(game);
}
