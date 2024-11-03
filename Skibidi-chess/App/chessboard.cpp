#include "chessboard.h"

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
            pieces.append(std::make_unique<ChessPiece>(j, i, true));
        }
    }
}

int ChessBoard::getNumOfPieces(){
    return pieces.length();
}

pieceInfo ChessBoard::getPiece(int index){
    return pieces[index]->getPieceDate();
}
