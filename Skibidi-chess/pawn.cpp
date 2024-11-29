#include "pawn.h"

Pawn::Pawn(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Pawn";
}

possibleMoves Pawn::getPossibleMoves(piecesVector const &pieces, int enPassantX) const{
    possibleMoves result;

    if (this->posY == 0 && this->isWhite || this->posY == 7 && !this->isWhite)
        return result;

    int direction = this->isWhite ? -1 : 1;
    int startRow = this->isWhite ? 6 : 1;

    bool isBlocked = false;
    for (const auto& piece : pieces) {
        if (piece->getPosX() == this->getPosX() && piece->getPosY() == this->getPosY() + direction)
            isBlocked = true;
    }
    if (!isBlocked)
        result.push_back({posX, posY + direction, moveType::move});

    if (this->isFirstMove && posY == startRow) {
        isBlocked = false;
        for (const auto& piece : pieces) {
            if (piece->getPosX() == this->getPosX() &&
                (piece->getPosY() == this->getPosY() + direction ||
                 piece->getPosY() == this->getPosY() + 2 * direction))
                isBlocked = true;
        }
        if (!isBlocked)
            result.push_back({posX, posY + 2 * direction, moveType::move});
    }

    for (const auto& piece : pieces) {
        if (piece->getPosY() == this->getPosY() + direction &&
            std::abs(piece->getPosX() - this->getPosX()) == 1 &&
            piece->getIsWhite() != this->isWhite)
        {
            result.push_back({piece->getPosX(), posY + direction, moveType::capture});
        }
    }

    // En passant
    if (posY == (this->isWhite ? 3 : 4)) {
        for (const auto& piece : pieces) {
            int enPassantY = this->isWhite ? 2 : 5;
            if (piece->getPosX() == enPassantX &&
                piece->getPosY() == posY &&
                piece->getIsWhite() != this->isWhite) {
                result.push_back({enPassantX, enPassantY, moveType::enpassan});
            }
        }
    }

    return result;
}

void Pawn::moveTo(int newPosX, int newPosY) {
    ChessPiece::moveTo(newPosX, newPosY);
    this->isFirstMove = false;
}
