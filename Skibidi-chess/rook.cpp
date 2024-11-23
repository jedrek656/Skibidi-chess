#include "rook.h"

Rook::Rook(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Rook";
}

possibleMoves Rook::checkHorizontal(int x, int y, bool is_white, std::vector<std::unique_ptr<ChessPiece>> const &pieces) {
    std::vector<std::pair<int, bool>> maxReach(4, {0, false}); // first element: +x, -x, +y, -y, second element: is_capture
    maxReach[0].first = 8 - x;
    maxReach[1].first = x + 1;
    maxReach[2].first = 8 - y;
    maxReach[3].first = y + 1;
    possibleMoves result;

    for (auto &&piece : pieces) {
        for (int i = 1; i < maxReach[0].first + 1; ++i) {
            if (piece->getPosY() == y && piece->getPosX() == x + i){
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
            if (piece->getPosY() == y && piece->getPosX() == x - i){
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
            if (piece->getPosY() == y + i && piece->getPosX() == x){
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
            if (piece->getPosY() == y - i && piece->getPosX() == x){
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
            result.push_back({x + i, y, moveType::capture});
        else
            result.push_back({x + i, y, moveType::move});
    }
    for (int i = 1; i < maxReach[1].first; ++i) {
        if (i == maxReach[1].first - 1 && maxReach[1].second == true)
            result.push_back({x - i, y, moveType::capture});
        else
            result.push_back({x - i, y, moveType::move});
    }
    for (int i = 1; i < maxReach[2].first; ++i) {
        if (i == maxReach[2].first - 1 && maxReach[2].second == true)
            result.push_back({x, y + i, moveType::capture});
        else
            result.push_back({x, y + i, moveType::move});
    }
    for (int i = 1; i < maxReach[3].first; ++i) {
        if (i == maxReach[3].first - 1 && maxReach[3].second == true)
            result.push_back({x, y - i, moveType::capture});
        else
            result.push_back({x, y - i, moveType::move});
    }
    return result;
}

possibleMoves Rook::getPossibleMoves(piecesVector const &pieces) const {
    possibleMoves result = checkHorizontal(this->getPosX(), this->getPosY(), this->getIsWhite(), pieces);
    return result;
}

