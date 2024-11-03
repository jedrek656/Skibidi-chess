#include "chesspiece.h"

ChessPiece::ChessPiece(int posX, int posY, bool isWhite) {
    this->posX = posX;
    this->posY = posY;
    this->isWhite = isWhite;
}

pieceInfo ChessPiece::getPieceDate(){
    return pieceInfo(this->name, this->posX, this->posY, this->isWhite);
}
