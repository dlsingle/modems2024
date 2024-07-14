#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QJsonObject"
#include "QJsonArray"
#include "QTimer"
#include "QVector"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_1_save_clicked();

    void on_pushButton_2_save_clicked();

    void on_pushButton_3_save_clicked();

    void on_pushButton_1_load_clicked();

    void on_pushButton_2_load_clicked();

    void on_pushButton_3_clicked();

    void updateGraph();

    void updateGraph2();

    void updateGraph3();


private:
    Ui::MainWindow *ui;

    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    int maxSize;
    QCustomPlot *customPlot1;
    QCustomPlot *customPlot2;
    QCustomPlot *customPlot3;

    QVector<double> x,y;
    QVector<double> x2,y2;
    QVector<double> x3,y3;

    void saveJsonToFile (const QString &filename);
    void loadJsonToFile (const QString &filename);
};

#endif // MAINWINDOW_H
