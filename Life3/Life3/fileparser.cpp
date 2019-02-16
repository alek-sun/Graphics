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

    file.open(QIODevice::ReadOnly);

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
            QStringList listdigits = digits.split(" ");
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

    string str = to_string(game->m).append(" ").append(to_string(game->n)).append("\r\n")
            .append("1").append("\r\n");
    file.write(str.c_str(), str.length());

    str = to_string(game->k).append("\r\n");
    file.write(str.c_str());

    vector<pair<int, int>> alive;
    for (auto cell : game->curState){
        if (cell.getIsAlive()){
            pair<int, int> p;
            qDebug() << cell.x << " " << cell.y;
            p.first = cell.x;
            p.second = cell.y;
            alive.push_back(p);
        }
    }

    str = to_string(alive.size()).append("\r\n");
    file.write(str.c_str());

    for (auto cell : alive){
        str = to_string(cell.first).append(" ").append(to_string(cell.second)).append("\r\n");
        file.write(str.c_str());
    }

    file.flush();
    file.close();
}
