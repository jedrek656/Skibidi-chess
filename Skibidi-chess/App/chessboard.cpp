#include "chessboard.h"
#include "pawn.h"
#include <QDebug>

ChessBoard::ChessBoard(QObject *parent, QString position)
    : QObject{parent}
{
    if (position == "default"){
        loadDefaultPosition();
    }
}

void ChessBoard::loadDefaultPosition() {
    for (int i=0; i<2; ++i){
        for(int j=0; j<8; ++j){
            pieces.push_back(std::make_unique<Pawn>(j, i, false));
        }
    }
    pieces.push_back(std::make_unique<Pawn>(4, 2, true));
}

int ChessBoard::getNumOfPieces(){
    return pieces.size();
}

QVariantList ChessBoard::getPiece(int index){
    return pieces[index]->getPieceData();
}

std::vector<std::vector<int>> ChessBoard::getPossibleMoves(int index){
    return pieces[index]->getPossibleMoves(this->pieces);
}

void ChessBoard::movePiece(int pieceIdx, int newPosX, int newPosY)
{
    qDebug() << this->getPiece(pieceIdx);
    this->pieces[pieceIdx]->moveTo(newPosX, newPosY);
    qDebug() << this->getPiece(pieceIdx);
    emit changePlayer();
    return;
}

void ChessBoard::capturePiece(int pieceIdx, int newPosX, int newPosY)
{
    emit changePlayer();
    return;
}
