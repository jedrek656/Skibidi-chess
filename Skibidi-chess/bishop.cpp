#include "bishop.h"

Bishop::Bishop(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Bishop";
}

possibleMoves Bishop::checkDiagonal(int x, int y, bool is_white, std::vector<std::unique_ptr<ChessPiece>> const &pieces) {
    std::vector<std::pair<int, bool>> maxReach(4, {0, false}); // first element: +x +y, +x -y, -x +y, -x -y, second element: is_capture
    maxReach[0].first = std::min(8 - x, 8 - y);
    maxReach[1].first = std::min(8 - x, y + 1);
    maxReach[2].first = std::min(x + 1, 8 - y);
    maxReach[3].first = std::min(x + 1, y + 1);
    possibleMoves result;

    for (auto &&piece : pieces) {
        for (int i = 1; i < maxReach[0].first + 1; ++i) {
            if (piece->getPosY() == y + i && piece->getPosX() == x + i){
                if (piece->getIsWhite() == is_white) {
                    maxReach[0].first = std::min(maxReach[0].first, i);
                    maxReach[0].second = false;
                }
                else {
                    maxReach[0].first = std::min(maxReach[0].first, i + 1);
                    maxReach[0].second = true;
                }
            }
        }
        for (int i = 1; i < maxReach[1].first + 1; ++i) {
            if (piece->getPosY() == y - i && piece->getPosX() == x + i){
                if (piece->getIsWhite() == is_white) {
                    maxReach[1].first = std::min(maxReach[1].first, i);
                    maxReach[1].second = false;
                }
                else {
                    maxReach[1].first = std::min(maxReach[1].first, i + 1);
                    maxReach[1].second = true;
                }
            }
        }
        for (int i = 1; i < maxReach[2].first + 1; ++i) {
            if (piece->getPosY() == y + i && piece->getPosX() == x - i){
                if (piece->getIsWhite() == is_white) {
                    maxReach[2].first = std::min(maxReach[2].first, i);
                    maxReach[2].second = false;
                }
                else {
                    maxReach[2].first = std::min(maxReach[2].first, i + 1);
                    maxReach[2].second = true;
                }
            }
        }
        for (int i = 1; i < maxReach[3].first + 1; ++i) {
            if (piece->getPosY() == y - i && piece->getPosX() == x - i){
                if (piece->getIsWhite() == is_white) {
                    maxReach[3].first = std::min(maxReach[3].first, i);
                    maxReach[3].second = false;
                }
                else {
                    maxReach[3].first = std::min(maxReach[3].first, i + 1);
                    maxReach[3].second = true;
                }
            }
        }
    }
    for (int i = 1; i < maxReach[0].first; ++i) {
        if (i == maxReach[0].first - 1 && maxReach[0].second == true)
            result.push_back({x + i, y + i, moveType::capture});
        else
            result.push_back({x + i, y + i, moveType::move});
    }
    for (int i = 1; i < maxReach[1].first; ++i) {
        if (i == maxReach[1].first - 1 && maxReach[1].second == true)
            result.push_back({x + i, y - i, moveType::capture});
        else
            result.push_back({x + i, y - i, moveType::move});
    }
    for (int i = 1; i < maxReach[2].first; ++i) {
        if (i == maxReach[2].first - 1 && maxReach[2].second == true)
            result.push_back({x - i, y + i, moveType::capture});
        else
            result.push_back({x - i, y + i, moveType::move});
    }
    for (int i = 1; i < maxReach[3].first; ++i) {
        if (i == maxReach[3].first - 1 && maxReach[3].second == true)
            result.push_back({x - i, y - i, moveType::capture});
        else
            result.push_back({x - i, y - i, moveType::move});
    }
    return result;
}

possibleMoves Bishop::getPossibleMoves(piecesVector const &pieces, int enPassantX) const {
    possibleMoves result = checkDiagonal(this->getPosX(), this->getPosY(), this->getIsWhite(), pieces);
    return result;
}
