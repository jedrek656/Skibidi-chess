#include "spelllist.h"

SpellList::SpellList(QObject *parent)
    : QAbstractListModel{parent}
{}

int SpellList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return spells.size();
}

QVariant SpellList::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid() || idx.row() >= spells.size())
        return QVariant();

    return QVariant();
}

QHash<int, QByteArray> SpellList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemRoles::NameRole] = "nameProperty";
    roles[ItemRoles::PosXRole] = "posX";
    roles[ItemRoles::PosYRole] = "posY";
    roles[ItemRoles::LifespanRole] = "lifespan";
    roles[ItemRoles::IsWhiteRole] = "isWhiteProperty";
    return roles;
}

void SpellList::updateLifespans()
{
    std::vector<std::unique_ptr<Spell>>::iterator iter;
    for (iter = spells.begin(); iter != spells.end(); ) {
        if ((*iter)->decreaseDuration())
            iter = removeItem(iter);
        else
            ++iter;
    }
}

vecIterator SpellList::removeItem(vecIterator currIterator)
{
    int idx = currIterator - spells.begin();
    Q_ASSERT(idx >= 0 && idx < spells.size());
    beginRemoveRows(QModelIndex(), idx, idx);
    vecIterator newIterator = spells.erase(currIterator);
    endRemoveRows();
    return newIterator;
}

void SpellList::clearList()
{
    beginResetModel();
    spells.clear();
    endResetModel();
}

template <typename T>
void SpellList::addItem(int posX, int posY, bool isWhite)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    /*spells.push_back(std::make_unique<T>(T { ... }));*/
    endInsertRows();
}
