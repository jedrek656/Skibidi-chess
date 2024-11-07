#include "chessboard.h"
#include "pawn.h"

ChessBoard::ChessBoard(QObject *parent, QString position)
    : QObject{parent}
{
    if (position == "default"){
        loadDefaultPosition();
    }
}

void ChessBoard::loadDefaultPosition() {
    for (int i=0; i<2; ++i){
        for(int j=0; j<8; ++j){
            pieces.push_back(std::make_unique<Pawn>(j, i, false));
        }
    }
}

int ChessBoard::getNumOfPieces(){
    return pieces.size();
}

QVariantList ChessBoard::getPiece(int index){
    return pieces[index]->getPieceData();
}

std::vector<std::vector<int>> ChessBoard::getPossibleMoves(int index){
    return pieces[index]->getPossibleMoves(this->pieces);
}
