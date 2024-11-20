#include "chessboard.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include <QDebug>

ChessBoard::ChessBoard(QObject *parent)
    : QAbstractListModel{parent}
{
}

void ChessBoard::loadDefaultPosition() {
    for (int i=0; i<2; ++i){
        for(int j=0; j<8; ++j){
            //pieces.push_back(std::make_unique<Pawn>(j, i, false));
            addItem<Pawn>(j, i, false);
        }
    }

    //pieces.push_back(std::make_unique<Pawn>(4, 2, true));
    addItem<Pawn>(4, 2, true);

    emit chessboardLoaded();
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
    int toDelIdx = -1;
    int tmpIdx = 0;
    for(auto&& piece: pieces){
        if(piece->getPosX() == newPosX && piece->getPosY() == newPosY){
            toDelIdx = tmpIdx;
            break;
        };
        ++tmpIdx;
    }

    Q_ASSERT(toDelIdx != -1);
    this->pieces[pieceIdx]->moveTo(newPosX, newPosY);
    emit dataChanged(this->index(pieceIdx), this->index(pieceIdx), {ItemRoles::PosXRole, ItemRoles::PosYRole});

    removeItem(toDelIdx);

    emit changePlayer();
    return;
}

void ChessBoard::loadPosition(QString position)
{
    clearList();
    if (position == "default"){
        loadDefaultPosition();
    }
}

void ChessBoard::removeItem(int idx)
{
    Q_ASSERT(idx > 0 && idx < pieces.size());
    beginRemoveRows(QModelIndex(), idx, idx);
    pieces.erase(pieces.begin() + idx);
    endRemoveRows();
}

void ChessBoard::clearList()
{
    beginResetModel();
    pieces.clear();
    endResetModel();
}

template <typename T>
void ChessBoard::addItem(int posX, int posY, bool isWhite)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    pieces.push_back(std::make_unique<T>(T { posX, posY, isWhite }));
    endInsertRows();
}

std::vector<std::vector<int>> ChessBoard::getPossibleMoves(int index) const{
    return pieces[index]->getPossibleMoves(this->pieces);
}






