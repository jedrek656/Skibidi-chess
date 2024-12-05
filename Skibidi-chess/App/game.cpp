#include "game.h"
#include <QCoreApplication>
#include <QDebug>

Game::Game(QObject *parent, ChessBoard *chessboard)
    : QObject{parent}
{
    this->chessboard = chessboard;
    this->player1 = std::make_unique<Player>(Player{true});
    this->player2 = std::make_unique<Player>(Player(false));
    this->turn = true;
}

void Game::closeApp() const {
    QCoreApplication::quit();
}

void Game::setChessboard(ChessBoard *chessboard){
    this->chessboard = chessboard;
}

void Game::changeTurn() {
    this->turn = !this->turn;
}

bool Game::checkTurn() {
    return this->turn;
}

/*Player Game::getCurrentPlayer() {
    if (this->turn == true)
        return this->player1;
    else
        return this->player2;
}*/
