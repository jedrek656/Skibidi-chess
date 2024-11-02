#include "game.h"
#include <QCoreApplication>
#include <QDebug>

Game::Game(QObject *parent, ChessBoard *chessboard)
    : QObject{parent}
{
    this->chessboard = chessboard;
}

void Game::closeApp() const {
    QCoreApplication::quit();
}

void Game::setChessboard(ChessBoard *chessboard){
    this->chessboard = chessboard;
}
