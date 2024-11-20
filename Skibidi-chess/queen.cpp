#include "queen.h"
#include "rook.h"
#include "bishop.h"


Queen::Queen(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Queen";
}

possibleMoves Queen::getPossibleMoves(piecesVector const &pieces) const {
    possibleMoves resultH, resultD;
    resultH = Rook::checkHorizontal(this->getPosX(), this->getPosY(), this->getIsWhite(), pieces);
    resultD = Bishop::checkDiagonal(this->getPosX(), this->getPosY(), this->getIsWhite(), pieces);

    resultH.insert(resultH.end(), resultD.begin(), resultD.end());
    return resultH;
}

