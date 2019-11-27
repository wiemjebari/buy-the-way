#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QPixmap>
#include<QObject>
#include<QSound>
#include"employe.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix2("C:/Users/hp/Documents/qt_pic/bg6.jpg");
    ui->label_5->setPixmap(pix2.scaled(800,700,Qt::KeepAspectRatio));
    QPixmap pix("C:/Users/hp/Documents/qt_pic/buy the way.png");
    ui->label_6->setPixmap(pix.scaled(200,100,Qt::KeepAspectRatio));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{ QSound S ("C:/Users/hp/Documents/qt_pic/Clic-De-Souris.wav");
    S.play();


    QString username = ui->lineEdit->text();
    QString password = ui ->lineEdit_2 ->text();



    if (username== "employe" && password== "employe")
    {
       // QMessageBox::information(this, "login","username and password is correct");
       // hide();
        empl= new employe(this);
        empl->show();
        ui->statusbar->showMessage( "login username and password is correct");
    }
    else
    {
      // QMessageBox::warning(this, "login","username and password is not correct");

        ui->statusbar->showMessage( "login username and password is not correct");
    }

}
