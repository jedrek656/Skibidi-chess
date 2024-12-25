#include "spelllist.h"
#include <QDebug>

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

    const QVariantList spell = spells[idx.row()]->getSpell();

    switch (role) {
    case ItemRoles::NameRole:
        return spell[0];
    case ItemRoles::PosXRole:
        return spell[1];
    case ItemRoles::PosYRole:
        return spell[2];
    case ItemRoles::LifespanRole:
        return spell[3];
    }

    return QVariant();
}

QHash<int, QByteArray> SpellList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemRoles::NameRole] = "nameProperty";
    roles[ItemRoles::PosXRole] = "posX";
    roles[ItemRoles::PosYRole] = "posY";
    roles[ItemRoles::LifespanRole] = "lifespan";
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

int SpellList::getActiveSpell() const
{
    return activeSpell;
}

void SpellList::castSpell(int posX, int posY, int spellIdx)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    this->spells.push_back(std::make_unique<Spell>(posX, posY, spellIdx));
    endInsertRows();
}

void SpellList::setActiveSpell(int newActiveSpell)
{
    if (activeSpell == newActiveSpell)
        return;
    activeSpell = newActiveSpell;
    emit activeSpellChanged(newActiveSpell);
}
