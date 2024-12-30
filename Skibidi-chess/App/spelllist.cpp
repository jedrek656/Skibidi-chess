#include "spelllist.h"
#include <QDebug>
#include "game.h"

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

int SpellList::getCurrSpellCost()
{
    Q_ASSERT(this->activeSpell != -1);
    switch(this->activeSpell){
    case Spells::Asbestos:
        return 3;
    case Spells::CheeseDrippy:
        return 3;
    case Spells::HawkTuah:
        return 3;
    }

    return 0;
}

void SpellList::setGame(Game *newGame)
{
    game = newGame;
}

int SpellList::getActiveSpell() const
{
    return activeSpell;
}

void SpellList::castSpell(int posX, int posY)
{
    int cost = this->getCurrSpellCost();

    bool currPlayer = game->checkTurn();
    if (game->getCurrPlayerMana() >= cost){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        this->spells.push_back(std::make_unique<Spell>(posX, posY, this->activeSpell));
        endInsertRows();
        game->decreaseCurrPlayerMana(cost);
        emit game->updateMana();
    }
    this->activeSpell = -1;
    emit hideSpells();
}

void SpellList::addSpellDirectly(const QString &name, int posX, int posY, int lifespan)
{
    int spellIdx = -1;
    if (name == "Hawk Tuah") {
        spellIdx = Spells::HawkTuah;
    } else if (name == "Asbestos") {
        spellIdx = Spells::Asbestos;
    } else if (name == "Cheese Drippy") {
        spellIdx = Spells::CheeseDrippy;
    }

    if (spellIdx == -1) {
        qWarning() << "Invalid spell name provided:" << name;
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    auto spell = std::make_unique<Spell>(posX, posY, spellIdx);
    spell->changeLifespan(lifespan);
    spells.push_back(std::move(spell));
    endInsertRows();
}

std::vector<std::unique_ptr<Spell>>* SpellList::getSpells()
{
    return &(this->spells);
}

void SpellList::setActiveSpell(int newActiveSpell)
{
    if (activeSpell == newActiveSpell)
        return;
    activeSpell = newActiveSpell;
    emit activeSpellChanged(newActiveSpell);
}
