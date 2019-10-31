#include "filedriver.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

FileDriver::FileDriver(QUrl url)
{
    this->url=url;
}

void FileDriver::openModel(Settings *s)
{
    s->bearingPoints.clear();
    s->allPoints.clear();

    QFile file(url.toLocalFile());
    QString str;
    QStringList list;
    int i = 1, rowNum = 0, pointsNum = 0, pointsLim = 1;

    file.open(QIODevice::ReadOnly);

    if (!file.exists()){
        return;
    }

    while (!file.atEnd() && pointsNum != pointsLim){
        str = file.readLine();
        if (str == "\r\n")
            continue;

        list = str.split("\r\n");
        list = list[0].split("//");
        list = list[0].split(" ");

        switch (i) {
        case 1 : {
            if (list.size() != 4){
                QMessageBox b;
                QString s("Incorrect file format.\r\nError line : ");
                s.append(QString::number(i));
                b.setText(s);
                b.exec();
                return;
            } else{
                s->nCurveSplit = list[0].toInt();
                s->angleN = list[1].toInt();
                s->hidingSplane = list[2].toInt();
                s->hidingAngle = list[3].toInt();
            }
            ++i;
            break;
        }
        case 2:
        {
            s->z = list[0].toDouble();
            ++i;
            break;
        }
        case 3 : {
            s->matrix.setRow(rowNum, QVector4D(list[0].toDouble(), list[1].toDouble(), list[2].toDouble(), 1));
            rowNum++;
            if (rowNum == 3){
                ++i;
            }
            break;
        }
        case 4 : {
            s->backgroudColor = QColor(list[0].toInt(), list[1].toInt(), list[2].toInt());
            ++i;
            break;
        }
        case 5 : {
            s->bodyColor = QColor(list[0].toInt(), list[1].toInt(), list[2].toInt());
            ++i;
            break;
        }
        case 6 : {
            pointsLim = list[0].toInt();
            ++i;
            break;
        }
        case 7 : {
            s->bearingPoints.push_back(new QVector2D(list[0].toInt(), list[1].toInt()));
            pointsNum++;
        }
        }
    }
}

void FileDriver::saveModel(Settings s)
{
    int i, j;
    QFile file (url.toLocalFile());

    if (!file.open(QFile::WriteOnly | QFile::Text))
        return;
    QTextStream out(&file);
    out << s.nCurveSplit << " " << s.angleN << " " << s.hidingSplane << " " << s.hidingAngle << endl;
    out << s.z << endl;
    for (i = 0; i < 3; ++i){
        for (j = 0; j < 3; ++j){
            QVector4D v = s.matrix.row(i);
            switch (j) {
            case 0 : {
                out << v.x() << " ";
                break;
            }
            case 1 : {
                out << v.y() << " ";
                break;
            }
            case 2 : {
                out << v.z();
            }
            }
        }
        out << endl;
    }

    out << s.backgroudColor.red() << " " << s.backgroudColor.green() << " " << s.backgroudColor.blue() << endl;
    out << s.bodyColor.red() << " " << s.bodyColor.green() << " " << s.bodyColor.blue() << endl;
    out << s.bearingPoints.size() << endl;
    for (auto p : s.bearingPoints){
        out << p->x() << " " << p->y() << endl;
    }
    file.flush();
    file.close();
}
