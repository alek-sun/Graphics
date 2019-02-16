#include "fileparser.h"

using std::string;
using std::to_string;

FileDriver::FileDriver(GameLogic *game, QUrl filePath)
{
    this->game = game;
    this->filePath = filePath;
}

vector<pair<int, int>> FileDriver::parseState()
{
    QString str, digits;
    QFile file(filePath.toLocalFile());
    QStringList list;
    vector<pair<int, int>> coords;

    qDebug() << file.open(QIODevice::ReadOnly);

    if (!file.exists()){
        return coords;
    }

    int i = 0, countCells = 4;

    while (!file.atEnd() &&  i < countCells){

        str=file.readLine();
        if (str == "\r\n")
            continue;
        list = str.split("//");
        digits = list[0];

        switch (i){
        case 0 :
        {
            //QString::KeepEmptyParts
            QStringList listdigits = digits.split(" ");
            qDebug() << listdigits;
            game->m = listdigits[0].toInt();
            game->n = listdigits[1].toInt();
            break;
        }
        case 1 :
            ++i;
            continue;
        case 2 :
        {
            game->k = digits.toInt();
            break;
        }
        case 3 :
        {
            countCells += digits.toInt();
            break;
        }
        default:
        {
            QStringList listdigits = digits.split(" ");
            int x = listdigits[0].toInt();
            int y = listdigits[1].toInt();
            pair<int, int> p;
            p.first = x;
            p.second = y;
            coords.push_back(p);
        }
        }
        ++i;

    }

    file.close();
    return coords;
}

bool FileDriver::saveState()
{
    QFile file (filePath.toLocalFile());
    if(!file.open(QFile::WriteOnly | QFile::Text))
        return false;
    //char* m = itoa(game->m);
    string str = to_string(game->m).append(" ").append("\r\n");
    //file.write()
    file.flush();
    file.close();
}
