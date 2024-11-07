#include "pawn.h"

Pawn::Pawn(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Pawn";
}

possibleMoves Pawn::getPossibleMoves(piecesVector const &pieces) const {
    possibleMoves result;

    if(this->isWhite){
        int maxReach = 2;
        for (auto &&piece : pieces){
            if(piece->getPosY() == this->getPosY() - 2) {maxReach = 1;}
            if(piece->getPosY() == this->getPosY() - 1) {maxReach = 0;}
        }
        for (int i = 1; i < maxReach + 1; ++i){
            result.push_back(std::vector<int>() = {posX, posY - i});
        }
    }

    else{
        int maxReach = 2;
        for (auto &&piece : pieces){
            if(piece->getPosY() == this->getPosY() + 2) {maxReach = 1;}
            if(piece->getPosY() == this->getPosY() + 1) {maxReach = 0;}
        }
        for (int i = 1; i < maxReach + 1; ++i){
            result.push_back(std::vector<int>() = {posX, posY + i});
        }
    }
    return result;
}
