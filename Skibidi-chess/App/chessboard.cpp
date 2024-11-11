#include "chessboard.h"
#include "pawn.h"
#include <QDebug>

ChessBoard::ChessBoard(QObject *parent, QString position)
    : QAbstractListModel{parent}
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
    pieces.push_back(std::make_unique<Pawn>(4, 2, true));
}

int ChessBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return pieces.size();
}

QVariant ChessBoard::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid() || idx.row() >= pieces.size())
        return QVariant();

    const QVariantList piece = pieces[idx.row()]->getPieceData();

    switch (role) {
        case NameRole:
            return piece[0];
        case ItemRoles::PosXRole:
            return piece[1];
        case ItemRoles::PosYRole:
            return piece[2];
        case ItemRoles::IsWhiteRole:
            return piece[3];
    }

    return QVariant();
}

QHash<int, QByteArray> ChessBoard::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemRoles::NameRole] = "nameProperty";
    roles[ItemRoles::PosXRole] = "posX";
    roles[ItemRoles::PosYRole] = "posY";
    roles[ItemRoles::IsWhiteRole] = "isWhiteProperty";
    return roles;
}

void ChessBoard::movePiece(int pieceIdx, int newPosX, int newPosY)
{
    Q_ASSERT(pieceIdx >= 0 && pieceIdx < pieces.size());
    this->pieces[pieceIdx]->moveTo(newPosX, newPosY);
    emit dataChanged(this->index(pieceIdx), this->index(pieceIdx), {ItemRoles::PosXRole, ItemRoles::PosYRole});
    emit changePlayer();
    return;
}

void ChessBoard::capturePiece(int pieceIdx, int newPosX, int newPosY)
{
    emit changePlayer();
    return;
}

std::vector<std::vector<int>> ChessBoard::getPossibleMoves(int index){
    return pieces[index]->getPossibleMoves(this->pieces);
}






