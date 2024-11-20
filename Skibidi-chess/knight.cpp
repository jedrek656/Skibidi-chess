#include "knight.h"

Knight::Knight(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Knight";
}

possibleMoves Knight::getPossibleMoves(piecesVector const &pieces) const {
    possibleMoves result;

    // Offsets for the 8 possible knight moves (2 squares in one direction and 1 square perpendicular)
    const std::vector<std::pair<int, int>> directions = {
        {-2, -1}, {-2,  1}, {-1, -2}, {-1,  2}, { 1, -2}, { 1,  2}, { 2, -1}, { 2,  1}
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
                if (piece->getIsWhite() == this->isWhite) {
                    isBlocked = true; // Blocked by a friendly piece
                } else {
                    result.push_back({newX, newY, moveType::capture}); // Capture opponent piece
                }
                break;
            }
        }

        if (!isBlocked) {
            result.push_back({newX, newY, moveType::move});
        }
    }

    return result;
}