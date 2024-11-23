#include "chesspiece.h"
#include <iostream>

ChessPiece::ChessPiece(int posX, int posY, bool isWhite)
{
    this->posX = posX;
    this->posY = posY;
    this->isWhite = isWhite;
}

QVariantList ChessPiece::getPieceData() const
{
    return {this->name, this->posX, this->posY, this->isWhite};
}

void ChessPiece::moveTo(int newPosX, int newPosY)
{
    Q_ASSERT(newPosX < 8 && newPosY < 8 && newPosX > -1 && newPosY > -1);
    this->posX = newPosX;
    this->posY = newPosY;
}

possibleMoves ChessPiece::getPossibleMoves(piecesVector const &pieces) const
{
    return possibleMoves();
}

QString ChessPiece::getName() const
{
    return name;
}

int ChessPiece::getPosX() const
{
    return posX;
}

int ChessPiece::getPosY() const
{
    return posY;
}

bool ChessPiece::getIsWhite() const
{
    return isWhite;
}

ChessPiece::operator QString() const
{
    return this->name + ", " + QString::number(this->posX) + ", " + QString::number(this->posY);
}
