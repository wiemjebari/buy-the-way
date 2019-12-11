#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include"fournisseuretstocks.h"
#include"facture.h"
#include"QPixmap"
#include <QThread>
#include"promotion.h"
#include "employe.h"
#include"caisseetrayon.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);


}



MainWindow::~MainWindow()
{

    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    ge e;
    QString name;
    QString mdp;
    int poste;
    name=ui->lineEdit_id->text();
    mdp=ui->lineEdit_mdp->text();
    poste=e.verifier_statut(name,mdp);
    qDebug()<<poste;
    if (e.verifier_compte(name,mdp))
   {
    if(poste==1)
    {
        QMessageBox::information(this,"Le Nom et le Mot de Passe sont Corrects","Bienvenue Le Directeur Commercial");

        fournisseuretstocks f;
        f.setModal(true);
        f.exec();
    }


    else if(poste==3)
    {
        QMessageBox::information(this,"Le Nom et le Mot de Passe sont Corrects","Bienvenue Le Comptable");

        facture f;
        f.setModal(true);
        f.exec();
    }
    else if(poste==5)
    {
        QMessageBox::information(this,"Le Nom et le Mot de Passe sont Corrects","Bienvenue Agent de Carte");

        Promotion p;
        p.setModal(true);
        p.exec();
    }
    else if(poste==4)
    {
        QMessageBox::information(this,"Le Nom et le Mot de Passe sont Corrects","Bienvenue Le Caissier");

        caisseetrayon c;
        c.setModal(true);
        c.exec();
    }
    else if(poste==2)
    {
        QMessageBox::information(this,"Le Nom et le Mot de Passe sont Corrects","Bienvenue Le Directeur des resources humaines ");
        employe e;
        e.setModal(true);
        e.exec();
    }
    else
     {
         QMessageBox::warning(this,name,"Le Nom et le Mot de Passe ne sont pas Corrects");
     }
    }
    ui->lineEdit_id->clear();
    ui->lineEdit_mdp->clear();
     /*player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
      player->play();
      qDebug()<<player->errorString();
      QThread::sleep(1);*/
}







