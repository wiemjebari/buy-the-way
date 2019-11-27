#include "employe.h"
#include "ui_employe.h"
#include<QMainWindow>
#include<QMessageBox>
#include <QSound>
employe::employe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employe)
{
    ui->setupUi(this);
}

employe::~employe()
{
    delete ui;
}
void employe::on_pb_ajouter_clicked()
{
    QSound S ("C:/Users/hp/Documents/qt_pic/Clic-De-Souris.wav");
    S.play();

    long CIN = ui->lineEdit_CIN->text().toLong();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString poste= ui->lineEdit_poste->text();

  ge e(CIN,nom,prenom,poste);
  bool test=e.ajouter();
  if(test)
{ui->tabemploye->setModel(tmpemploye.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un employé"),
                  QObject::tr("employé ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un employe"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void employe::on_pb_supprimer_clicked()
{
    QSound S ("C:/Users/hp/Documents/qt_pic/Clic-De-Souris.wav");
    S.play();

long CIN = ui->lineEdit_CIN_2->text().toLong();
bool test=tmpemploye.supprimer(CIN);
if(test)
{ui->tabemploye->setModel(tmpemploye.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un employe"),
                QObject::tr("Employe supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un employé"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
void employe::on_pb_modifier_clicked()
{
    QSound S ("C:/Users/hp/Documents/qt_pic/Clic-De-Souris.wav");
    S.play();

   long CIN = ui->lineEdit_CIN_4->text().toLong();
        QString nom= ui->lineEdit_nom_2->text();
        QString prenom= ui->lineEdit_prenom_4->text();
        QString poste= ui->lineEdit_poste_2->text();


        ge e(CIN,nom,prenom,poste);
        bool test=e.modifier();


        if(test)
        {ui->tabemploye->setModel(tmpemploye.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Modifier un employe"),
                        QObject::tr("employe modifié.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Modifier Un employe"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
void employe::on_pb_recherche_clicked(  )
{

    QSound S ("C:/Users/hp/Documents/qt_pic/Clic-De-Souris.wav");
    S.play();

        QString val = ui->lineEdit_CIN_3->text();

           // QSqlQuery query;
            //query.prepare("select * from Employe where CIN= '"+val+"' ") ;
            //if (query.exec())
            ui->tabemploye_2->setModel(tmpemploye.afficher2(val));
           /* {while (query.next())

                   { ui->lineEdit_NOM->setText(query.value(2).toString());
                    ui->lineEdit_PRENOM->setText(query.value(1).toString());
                    ui->lineEdit_POSTE->setText(query.value(3).toString());
                    ui->lineEdit_CIN_3->setText(query.value(5).toString());}}*/



            /*else {
                QMessageBox::critical(nullptr, QObject::tr("Chercher un employe"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }*/

}

