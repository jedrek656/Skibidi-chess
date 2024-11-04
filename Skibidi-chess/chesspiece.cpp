#include "chesspiece.h"

ChessPiece::ChessPiece(int posX, int posY, bool isWhite) {
    this->posX = posX;
    this->posY = posY;
    this->isWhite = isWhite;
}

QVariantList ChessPiece::getPieceData(){
    return {this->name, this->posX, this->posY, this->isWhite};
}

possibleMoves ChessPiece::getPossibleMoves(piecesVector const &pieces)
{
    return possibleMoves();
}
