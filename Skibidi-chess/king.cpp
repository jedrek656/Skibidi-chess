#include "king.h"

King::King(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "King";
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

    return result;
}
