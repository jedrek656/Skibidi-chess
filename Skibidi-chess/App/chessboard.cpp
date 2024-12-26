#include "chessboard.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "dummypiece.h"
#include <QDebug>
#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QDir>
#include <QFile>

#include <algorithm>

ChessBoard::ChessBoard(QObject *parent)
    : QAbstractListModel{parent}
{
}

void ChessBoard::loadDefaultPosition() {
    for(int j=0; j<8; ++j){
        addItem<Pawn>(j, 1, false);
    }
    for(int j=0; j<8; ++j){
        addItem<Pawn>(j, 6, true);
    }

    for(int i = 0; i < 2; ++i){
        addItem<Rook>(0, i * 7, i);
        addItem<Rook>(7, i * 7, i);

        addItem<Knight>(1, i * 7, i);
        addItem<Knight>(6, i * 7, i);

        addItem<Bishop>(2, i * 7, i);
        addItem<Bishop>(5, i * 7, i);

        addItem<Queen>(3, i * 7, i);
        addItem<King>(4, i * 7, i);
    }

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

void ChessBoard::setSpellList(SpellList *spellList)
{
    this->spellList = spellList;
    QObject::connect(this, &ChessBoard::changePlayer, spellList, &SpellList::updateLifespans);
}

std::ostream &operator<<(std::ostream &out, const ChessBoard &board) {
    for (const auto &piece : board.pieces) {
        out << *piece << "\n";
    }
    return out;
}

std::istream &operator>>(std::istream &in, ChessBoard &board) {
    std::string name;
    int posX, posY;
    std::string color;

    while (in >> name >> posX >> posY >> color) {
        bool isWhite = (color == "White");

        if (name == "Pawn")
            board.addItem<Pawn>(posX, posY, isWhite);
        else if (name == "Rook")
            board.addItem<Rook>(posX, posY, isWhite);
        else if (name == "Bishop")
            board.addItem<Bishop>(posX, posY, isWhite);
        else if (name == "Knight")
            board.addItem<Knight>(posX, posY, isWhite);
        else if (name == "Queen")
            board.addItem<Queen>(posX, posY, isWhite);
        else if (name == "King")
            board.addItem<King>(posX, posY, isWhite);
        else
            throw std::runtime_error("Save file incorrect");
    }

    return in;
}

void ChessBoard::movePiece(int pieceIdx, int newPosX, int newPosY)
{
    Q_ASSERT(pieceIdx >= 0 && pieceIdx < pieces.size());
    enPassantX = -1;
    if (pieces[pieceIdx]->getName() == "Pawn") {
        int oldY = pieces[pieceIdx]->getPosY();
        if (std::abs(newPosY - oldY) == 2) {
            enPassantX = newPosX;
        }
    }
    this->pieces[pieceIdx]->moveTo(newPosX, newPosY);
    emit dataChanged(this->index(pieceIdx), this->index(pieceIdx), {ItemRoles::PosXRole, ItemRoles::PosYRole});
    if (pieces[pieceIdx]->getName() == "Pawn") {
        if (newPosY == 0 && pieces[pieceIdx]->getIsWhite()){
            emit promotionDialog(pieceIdx, true);
            return;
        }
        else if (newPosY == 7 && !pieces[pieceIdx]->getIsWhite()){
            emit promotionDialog(pieceIdx, false);
            return;
        }
    }
    emit changePlayer();
    return;
}

void ChessBoard::capturePiece(int pieceIdx, int newPosX, int newPosY)
{
    int toDelIdx = -1;
    int tmpIdx = 0;
    QString toDelName = "";
    bool toDelIsWhite = true;
    for(auto&& piece: pieces){
        if(piece->getPosX() == newPosX && piece->getPosY() == newPosY){
            toDelIdx = tmpIdx;
            toDelName = piece->getName();
            toDelIsWhite = piece->getIsWhite();
            break;
        };
        ++tmpIdx;
    }

    Q_ASSERT(toDelIdx != -1);
    this->pieces[pieceIdx]->moveTo(newPosX, newPosY);
    emit dataChanged(this->index(pieceIdx), this->index(pieceIdx), {ItemRoles::PosXRole, ItemRoles::PosYRole});
    removeItem(toDelIdx);
    if(toDelName == "King"){
        if(toDelIsWhite){
            emit gameEnd("Black");
            return;
        }
        else{
            emit gameEnd("White");
            return;
        }
    }
    if (pieces[pieceIdx]->getName() == "Pawn") {
        if (newPosY == 0 && pieces[pieceIdx]->getIsWhite()){
            emit promotionDialog(pieceIdx, true);
            return;
        }
        else if (newPosY == 7 && !pieces[pieceIdx]->getIsWhite()){
            emit promotionDialog(pieceIdx, false);
            return;
        }
    }
    emit changePlayer();
    return;
}

void ChessBoard::enPassant(int pieceIdx, int newPosX, int newPosY)
{
    int toDelIdx = -1;
    int tmpIdx = 0;
    for(auto&& piece: pieces){
        if(piece->getPosX() == newPosX && (piece->getPosY() + piece->getIsWhite() * 2 - 1) == newPosY){
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

void ChessBoard::promotePiece(int pieceIdx, QString name)
{
    Q_ASSERT(name == "Queen" || name == "Rook" || name == "Bishop" || name == "Knight");
    int PosX = pieces[pieceIdx]->getPosX();
    int PosY = pieces[pieceIdx]->getPosY();
    bool isWhite = pieces[pieceIdx]->getIsWhite();
    if(name == "Queen"){
        pieces[pieceIdx]=std::make_unique<Queen>(Queen { PosX, PosY, isWhite });
    }
    else if(name == "Rook"){
        pieces[pieceIdx]=std::make_unique<Rook>(Rook { PosX, PosY, isWhite });
    }
    else if(name == "Bishop"){
        pieces[pieceIdx]=std::make_unique<Bishop>(Bishop { PosX, PosY, isWhite });
    }
    else if(name == "Knight"){
        pieces[pieceIdx]=std::make_unique<Knight>(Knight { PosX, PosY, isWhite });
    }
    emit dataChanged(this->index(pieceIdx), this->index(pieceIdx), {ItemRoles::NameRole});
    emit changePlayer();
    return;
}

void ChessBoard::castling(int pieceIdx, int newPosX, int newPosY)
{
    ChessPiece *king = pieces[pieceIdx].get();
    Q_ASSERT(king->getName() == "King");

    if (newPosX == 6) {
        // Kingside castling
        for (size_t i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->getName() == "Rook" && pieces[i]->getPosX() == 7 && pieces[i]->getPosY() == king->getPosY()) {
                pieces[i]->moveTo(5, king->getPosY());
                emit dataChanged(index(i), index(i), {ItemRoles::PosXRole, ItemRoles::PosYRole});
                break;
            }
        }
    }
    else if (newPosX == 2) {
        // Queenside castling
        for (size_t i = 0; i < pieces.size(); ++i) {
            if (pieces[i]->getName() == "Rook" && pieces[i]->getPosX() == 0 && pieces[i]->getPosY() == king->getPosY()) {
                pieces[i]->moveTo(3, king->getPosY());
                emit dataChanged(index(i), index(i), {ItemRoles::PosXRole, ItemRoles::PosYRole});
                break;
            }
        }
    }

    king->moveTo(newPosX, newPosY);
    emit dataChanged(index(pieceIdx), index(pieceIdx), {ItemRoles::PosXRole, ItemRoles::PosYRole});
    emit changePlayer();
}

void ChessBoard::loadPosition(QString position)
{
    clearList();
    if (position == "default"){
        loadDefaultPosition();
    }
}

int ChessBoard::getActivePiece() const
{
    return activePiece;
}

void ChessBoard::setActivePiece(int newActivePiece)
{
    if (activePiece == newActivePiece)
        return;
    activePiece = newActivePiece;
    emit activePieceChanged();
}

void ChessBoard::getPossibleSpellFields(int spellIdx, bool isWhite)
{
    std::vector<std::vector<int>>fields;
    if (spellIdx == Spells::HawkTuah){
        for(auto& piece: this->pieces){
            if(piece->getIsWhite() == isWhite){
                fields.push_back({piece->getPosX(), piece->getPosY()});
            }
        }
    }

    else if (spellIdx == Spells::Asbestos){
        for (int i = 1; i < 7; ++i){
            for (int j = 1; j < 7; ++j){
                fields.push_back(std::vector<int> {i, j});
            }
        }
    }

    else{
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 8; ++j){
                fields.push_back(std::vector<int> {i, j});
            }
        }

        std::vector<std::vector<int>> occupied_fields;
        for (auto&& piece: pieces){
            occupied_fields.push_back(std::vector<int>{piece->getPosX(), piece->getPosY()});
        }

        fields.erase(std::remove_if(fields.begin(),
                                    fields.end(),
                                    [&](const std::vector<int>& field) {
                                        return std::find(occupied_fields.begin(),
                                                         occupied_fields.end(),
                                                         field) != occupied_fields.end();
                                    }),
                     fields.end());
    }
    emit spellFieldsGenerated(fields);
}

void ChessBoard::resetPossibleSpellFields()
{
    emit spellFieldsGenerated({});
}

void ChessBoard::removeItem(int idx)
{
    Q_ASSERT(idx >= 0 && idx < pieces.size());
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
    for (auto& spell: *this->spellList->getSpells()){
        auto spellPos = spell->getPos();
    }
    return pieces[index]->getPossibleMoves(this->pieces, enPassantX);
}
