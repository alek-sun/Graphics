#include "fileparser.h"

FileParser::FileParser(GameLogic *game, QUrl filePath)
{
    this->game = game;
    this->filePath = filePath;
}

bool FileParser::parseState()
{
    QString str;
    QFile file(filePath.toLocalFile());

     qDebug() << file.open(QIODevice::ReadOnly);

    if (!file.exists()){
        return false;
    }

    while (!file.atEnd()){
        str=file.readLine();
        qDebug() << str + "------";
    }
    file.close();
    return true;
}
