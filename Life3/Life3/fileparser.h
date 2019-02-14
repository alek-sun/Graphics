#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "cell.h"
#include "gamelogic.h"
#include <iostream>
#include <QFile>
#include <string>
#include <QUrl>
#include <QDebug>


class FileParser
{
public:
    FileParser(GameLogic* game, QUrl filePath);

    bool parseState();
private:
    GameLogic* game;
    QUrl filePath;
};

#endif // FILEPARSER_H
