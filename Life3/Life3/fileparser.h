#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "cell.h"
#include "gamelogic.h"
#include <iostream>
#include <QFile>
#include <string>
#include <QUrl>
#include <QDebug>


class FileDriver
{
public:
    FileDriver(GameLogic* game, QUrl filePath);

    vector<pair<int, int> > parseState();
    bool saveState();
private:
    GameLogic* game;
    QUrl filePath;
};

#endif // FILEPARSER_H
