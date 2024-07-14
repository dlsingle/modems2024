#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"
#include "QIODevice"
#include <QRandomGenerator>
#include <QPainter>
#include <QTimer>
#include <QVector>

QString params[8];
int l=0;
int graphTop;
int graphBottom;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    maxSize(100)
{
    ui->setupUi(this);

    QGridLayout *gridlayout1 = ui->gridLayout_2;

    gridlayout1->setColumnMinimumWidth(1,71);

    ui->widget_2->setMinimumSize(361,174);
    ui->Graphic_2->setMinimumSize(361,174);

    QRegExp regExp("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
                   "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QRegExpValidator *regExpValidator = new QRegExpValidator(regExp,this);
    ui->lineEdit_2->setValidator(regExpValidator);
    ui->lineEdit_3->setValidator(regExpValidator);
    ///////////////////////////////////// график 1

    customPlot1 = new QCustomPlot(this);
    ui->Graphic_1->setLayout(new QVBoxLayout);
    ui->Graphic_1->layout()->addWidget(customPlot1);
    customPlot1->setMinimumHeight(174);

    customPlot1->addGraph();
    customPlot1->xAxis->setRange(0, maxSize);
    customPlot1->yAxis->setRange(0, 150);

    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &MainWindow::updateGraph);
    timer1->start(100);



    ///////////////////////////////////// график 2

        customPlot2 = new QCustomPlot(this);
        ui->Graphic_2->setLayout(new QVBoxLayout);
        ui->Graphic_2->layout()->addWidget(customPlot2);
        customPlot2->setMinimumHeight(174);

        customPlot2->addGraph();
        customPlot2->xAxis->setRange(0, maxSize);
        customPlot2->yAxis->setRange(0, 150);

        timer2 = new QTimer(this);
        connect(timer2, &QTimer::timeout, this, &MainWindow::updateGraph2);
        timer2->start(100);

    /////////////////////////////////////  график 3
        customPlot3 = new QCustomPlot(this);
        ui->Graphic_3->setLayout(new QVBoxLayout);
        ui->Graphic_3->layout()->addWidget(customPlot3);
        customPlot3->setMinimumHeight(174);

        customPlot3->addGraph();
        customPlot3->xAxis->setRange(0, maxSize);
        customPlot3->yAxis->setRange(0, 150);

        timer3 = new QTimer(this);
        connect(timer3, &QTimer::timeout, this, &MainWindow::updateGraph3);
        timer3->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_save_clicked()
{
    params[0]=ui->comboBox_1_1->currentText();
    params[1]=ui->comboBox_1_2->currentText();
    params[2]=ui->comboBox_1_3->currentText();
    saveJsonToFile("save.json");
}

void MainWindow::on_pushButton_2_save_clicked()
{
    params[3]=ui->lineEdit_2->text();
    params[4]=ui->comboBox_2->currentText();
    saveJsonToFile("save.json");
}

void MainWindow::on_pushButton_3_save_clicked()
{
    params[5]=ui->lineEdit_3->text();
    params[6]=ui->comboBox_3_1->currentText();
    params[7]=ui->comboBox_3_2->currentText();
    saveJsonToFile("save.json");
}

void MainWindow::on_pushButton_1_load_clicked()
{
    l=1;
    loadJsonToFile("save.json");
}

void MainWindow::on_pushButton_2_load_clicked()
{
    l=2;
    loadJsonToFile("save.json");
}

void MainWindow::on_pushButton_3_clicked()
{
    l=3;
    loadJsonToFile("save.json");
}

void MainWindow::saveJsonToFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qWarning("Файл не открылся!");
        return;
    }
    QJsonObject json;
    json["СКК 1"]=params[0];
    json["Частота  1"]=params[1];
    json["Мощность 1"]=params[2];
    json["IP-адрес 2"]=params[3];
    json["Мощность 2"]=params[4];
    json["IP-адрес 3"]=params[5];
    json["Частота  3"]=params[6];
    json["Мощность 3"]=params[7];
    QJsonDocument doc(json);
    file.write(doc.toJson());
    file.close();
}

void MainWindow::loadJsonToFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice:: Text))
    {
        qWarning("Файл не открылся!");
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject json = doc.object();
    if(l==1)
    {
    params[0]=json["СКК 1"].toString();
    ui->comboBox_1_1->setCurrentText(params[0]);
    params[1]=json["Частота  1"].toString();
    ui->comboBox_1_2->setCurrentText(params[1]);
    params[2]=json["Мощность 1"].toString();
    ui->comboBox_1_3->setCurrentText(params[2]);
    }
    else if(l==2)
    {
    params[3]=json["IP-адрес 2"].toString();
    ui->lineEdit_2->setText(params[3]);
    params[4]=json["Мощность 2"].toString();
    ui->comboBox_2->setCurrentText(params[4]);
    }
    else if(l==3)
    {
    params[5]=json["IP-адрес 3"].toString();
    ui->lineEdit_3->setText(params[5]);
    params[6]=json["Частота  3"].toString();
    ui->comboBox_3_1->setCurrentText(params[6]);
    params[7]=json["Мощность 3"].toString();
    ui->comboBox_3_2->setCurrentText(params[7]);
    }
    l=0;
}


void MainWindow::updateGraph()
{
    static double t = 0;
        t += 0.5;

        // Добавляем новые точки
        x.append(t);
        y.append(qrand()%150 );

        // Удаляем старые точки, если их больше maxSize
        if (x.size() > maxSize) {
            x.remove(0);
            y.remove(0);
        }

        // Обновляем график
        customPlot1->graph(0)->setData(x, y);
        customPlot1->xAxis->setRange(x.first(), x.last());
        customPlot1->replot();

}

void MainWindow::updateGraph2()
{
    static double t = 0;
        t += 0.5;

        // Добавляем новые точки
        x2.append(t);
        y2.append(qrand()%150 );

        // Удаляем старые точки, если их больше maxSize
        if (x2.size() > maxSize) {
            x2.remove(0);
            y2.remove(0);
        }

        // Обновляем график
        customPlot2->graph(0)->setData(x2, y2);
        customPlot2->xAxis->setRange(x2.first(), x2.last());
        customPlot2->replot();

}

void MainWindow::updateGraph3()
{
    static double t = 0;
        t += 0.5;

        // Добавляем новые точки
        x3.append(t);
        y3.append(qrand()%150 );

        // Удаляем старые точки, если их больше maxSize
        if (x3.size() > maxSize) {
            x3.remove(0);
            y3.remove(0);
        }

        // Обновляем график
        customPlot3->graph(0)->setData(x3, y3);
        customPlot3->xAxis->setRange(x3.first(), x3.last());
        customPlot3->replot();

}


