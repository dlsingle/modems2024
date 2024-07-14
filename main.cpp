#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <QRandomGenerator>
#include <QPainter>
QHash<QString, QString> qssVarMap{
    {"$FON", "rgb(34, 40, 49)"},
    {"$Widgetfon", "rgb(57, 62, 70)"},
    {"$ABZ", "rgb(238, 238, 238)"},
    {"$Labelfon","rgb(0, 173, 181)"},
    {"$scrift","75 12pt ""Arimo""" }};

QStringList handlesQSS()
{

    QStringList stringlist;
    QFile file(":/style.css");
    if (!file.exists(":/style.css")){
        QString err = "файла нет";
        stringlist.append(err);
        return stringlist;
    }

    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    QString qssStringNums;
    QString haskmapkey;

    for (auto i = qssVarMap.cbegin(),end = qssVarMap.cend(); i != end; ++i)
    {
        if (i.key()[0] != '$')
        {
            haskmapkey += i.key() + ", ";
        }
        stylesheet.replace(i.key(), i.value());
    }

    for (int32_t i = 0, stringcounter = 1; i < stylesheet.size(); ++i)
    {
        if (stylesheet.at(i) == '\n')
        {
            ++stringcounter;
        }
        if (stylesheet.at(i) == QChar('$'))
        {
            qssStringNums.append(QString::number(stringcounter) + ", ");
        }
    }
    stringlist.append(stylesheet);
    stringlist.append(qssStringNums);
    stringlist.append(haskmapkey);
    return stringlist;

}


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    QStringList zamena = handlesQSS();
    if (!zamena.at(1).isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Номера строк которые небыли заменены их нет в QHash: " + zamena.at(1));
        msgBox.exec();
    }
    if (!zamena.at(2).isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Нет знака $ перед переменной под ключ: " + zamena.at(2));
        msgBox.exec();
    }
    a.setStyleSheet(zamena.at(0));
    MainWindow w; 
    w.show();
    return a.exec();
}
