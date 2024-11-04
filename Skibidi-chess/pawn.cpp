#include "pawn.h"

Pawn::Pawn(int posX, int posY, bool isWhite) : ChessPiece::ChessPiece(posX, posY, isWhite) {
    this->name = "Pawn";
}

possibleMoves Pawn::getPossibleMoves(piecesVector const &pieces) {
    possibleMoves result;

    if(this->isWhite){
        /*for (auto &&piece : pieces){

        }*/
        result.push_back(std::vector<int>() = {posX, posY + 1});
        result.push_back(std::vector<int>() = {posX, posY + 2});
    }

    else{
        /*for (auto &&piece : pieces){

        }*/
        result.push_back(std::vector<int>() = {posX, posY - 1});
        result.push_back(std::vector<int>() = {posX, posY - 2});
    }
    return result;
}
