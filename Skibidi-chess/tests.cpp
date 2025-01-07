#include <gtest/gtest.h>
#include "spell.h"
#include "App/game.h"
#include "App/chessboard.h"
#include "queen.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "chesspiece.h"
#include <algorithm>

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

TEST(chessboard, possibleMoves2)
{
    Game *game = prepareGame();
    ChessBoard *chessBoard = game->getChessboard();

    chessBoard->addItem<Queen>(3, 4, true);
    chessBoard->addItem<Pawn>(2, 4, true);
    chessBoard->addItem<Pawn>(3, 5, true);
    chessBoard->addItem<Pawn>(4, 4, true);
    chessBoard->addItem<Knight>(4, 3, true);
    chessBoard->addItem<Bishop>(1, 6, false);
    chessBoard->addItem<Rook>(6, 7, false);
    chessBoard->addItem<King>(3, 1, false);

    auto moves = chessBoard->getPossibleMoves(0);

    std::vector<std::vector<int>> correctMoves = {{0, 1, ChessPiece::moveType::move},
                                                  {1, 2, ChessPiece::moveType::move},
                                                  {2, 3, ChessPiece::moveType::move},

                                                  {1, 6, ChessPiece::moveType::capture},
                                                  {2, 5, ChessPiece::moveType::move},

                                                  {4, 5, ChessPiece::moveType::move},
                                                  {5, 6, ChessPiece::moveType::move},
                                                  {6, 7, ChessPiece::moveType::capture},

                                                  {3, 3, ChessPiece::moveType::move},
                                                  {3, 2, ChessPiece::moveType::move},
                                                  {3, 1, ChessPiece::moveType::capture}};

    for(auto move: moves){
        ASSERT_TRUE(std::find(correctMoves.begin(), correctMoves.end(), move) != correctMoves.end());
    }

    ASSERT_EQ(chessBoard->getPossibleMoves(0).size(), 11);
    freeMem(game);
}
