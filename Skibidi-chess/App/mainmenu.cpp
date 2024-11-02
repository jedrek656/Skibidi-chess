#include "mainmenu.h"
#include <QDebug>
#include <QCoreApplication>

MainMenu::MainMenu(QObject *parent)
    : QObject{parent}
{}

void MainMenu::exit(){
    qDebug() << "huj";
    QCoreApplication::quit();
}
