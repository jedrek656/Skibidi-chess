#include "pawn.h"

//EN PASSANT IMPLEMENTED NOT IMPLEMENTED YET

Pawn::Pawn(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Pawn";
}

possibleMoves Pawn::getPossibleMoves(piecesVector const &pieces) const {

    if (this->posY==0 && this->isWhite){return {};}
    if (this->posY==7 && !this->isWhite){return {};}
    possibleMoves result;
    int maxReach = 1 + this->isFirstMove;

    //for white pawn
    if(this->isWhite){
        for (auto &&piece : pieces){
            if (piece->getPosY() == this->getPosY() - 2 && piece->getPosX() == this->getPosX()){
                maxReach = std::min(maxReach, 1);
            }
            if (piece->getPosY() == this->getPosY() - 1) {
                if (std::abs(piece->getPosX() - this->getPosX()) == 1 && piece->getIsWhite() != this->getIsWhite()){
                    result.push_back({piece->getPosX(), posY - 1, moveType::capture});
                }
                if(piece->getPosX() == this->getPosX()){
                    maxReach = std::min(maxReach, 0);
                }
            }
        }
        for (int i = 1; i < maxReach + 1; ++i){
            result.push_back({posX, posY - i, moveType::move});
        }
    }

    //for black pawn
    else{
        for (auto &&piece : pieces){
            if (piece->getPosY() == this->getPosY() + 2 && piece->getPosX() == this->getPosX()){
                maxReach = std::min(maxReach, 1);
            }
            if (piece->getPosY() == this->getPosY() + 1) {
                if (std::abs(piece->getPosX() - this->getPosX()) == 1 && piece->getIsWhite() != this->getIsWhite()){
                    result.push_back({piece->getPosX(), posY + 1, moveType::capture});
                }
                if(piece->getPosX() == this->getPosX()){
                    maxReach = std::min(maxReach, 0);
                }
            }
        }
        for (int i = 1; i < maxReach + 1; ++i){
            result.push_back({posX, posY + i, moveType::move});
        }
    }
    return result;
}

void Pawn::moveTo(int newPosX, int newPosY) {
    ChessPiece::moveTo(newPosX, newPosY);
    this->isFirstMove = false;
}
