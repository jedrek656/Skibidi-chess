#include "king.h"
#include "rook.h"

King::King(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "King";
    if(isWhite && posY != 7)
    {
        this->isFirstMove = false;
    }
    else if(!isWhite && posY != 0)
    {
        this->isFirstMove = false;
    }
}

possibleMoves King::getPossibleMoves(piecesVector const &pieces, int enPassantX) const {
    possibleMoves result;

    // Offsets for all 8 possible directions
    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    for (const auto& [dx, dy] : directions) {
        int newX = posX + dx;
        int newY = posY + dy;

        // Ensure the position is within the board
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
            continue;
        }

        bool isBlocked = false;
        for (const auto& piece : pieces) {
            if (piece->getPosX() == newX && piece->getPosY() == newY) {
                if (piece->getIsWhite() != this->isWhite) {
                    result.push_back({newX, newY, moveType::capture});
                }
                isBlocked = true;
                break;
            }
        }

        if (!isBlocked) {
            result.push_back({newX, newY, moveType::move});
        }
    }

    if (this->isFirstMove) {
        bool canCastleKingside = true;
        for (const auto &piece : pieces) {
            if ((piece->getPosX() == 5 || piece->getPosX() == 6) && piece->getPosY() == this->posY) {
                canCastleKingside = false;
                break;
            }
            if (piece->getPosX() == 7 && piece->getPosY() == this->posY) {
                if (piece->getName() != "Rook" || !piece->getIsWhite() == this->isWhite || !static_cast<Rook *>(piece.get())->getIsFirstMove()) {
                    canCastleKingside = false;
                }
            }
        }
        if (canCastleKingside) {
            result.push_back({6, posY, moveType::castling});
        }

        bool canCastleQueenside = true;
        for (const auto &piece : pieces) {
            if ((piece->getPosX() == 1 || piece->getPosX() == 2 || piece->getPosX() == 3) && piece->getPosY() == this->posY) {
                canCastleQueenside = false;
                break;
            }
            if (piece->getPosX() == 0 && piece->getPosY() == this->posY) {
                if (piece->getName() != "Rook" || !piece->getIsWhite() == this->isWhite || !static_cast<Rook *>(piece.get())->getIsFirstMove()) {
                    canCastleQueenside = false;
                }
            }
        }
        if (canCastleQueenside) {
            result.push_back({2, posY, moveType::castling});
        }
    }

    return result;
}

void King::moveTo(int newPosX, int newPosY) {
    ChessPiece::moveTo(newPosX, newPosY);
    this->isFirstMove = false;
}
