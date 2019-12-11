#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSql>
#include <QMainWindow>
#include"fournisseurstocks.h"
#include <QMediaPlayer>
#include<QThread>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


 QMediaPlayer* player;

private slots:
    void on_pushButton_clicked();





private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
