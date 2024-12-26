#include "dummypiece.h"

DummyPiece::DummyPiece(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite)
{
    this->name = "Dummy";
}

possibleMoves DummyPiece::getPossibleMoves(const piecesVector &pieces, int enPassantX) const
{
    throw std::runtime_error("You should NOT be able to call this method.");
}
