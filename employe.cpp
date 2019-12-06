#include "employe.h"
#include "ui_employe.h"
#include <QDebug>
#include <QMessageBox>
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


ge::ge()
{
      CIN=0;
      nom="";
      prenom="";
 }

    ge::ge(long CIN,QString nom ,QString prenom,QString poste)
    {
        this->CIN=CIN;
        this->nom=nom;
        this->prenom=prenom;
        this->poste=poste;

    }
    long ge::get_CIN(){return CIN;}
    QString ge::get_NOM(){return nom;}
    QString ge::get_PRENOM(){return prenom;}
    QString ge::get_Poste(){return poste;}



    bool ge::ajouter()
    {
        QSqlQuery query;
        QString res= QString::number(CIN);
        query.prepare("insert into employe(CIN,PRENOM,NOM,POSTE)"
                      "VALUES(:CIN,:PRENOM,:NOM,:POSTE)");
        query.bindValue(":CIN",res);
        query.bindValue(":PRENOM",prenom);
        query.bindValue(":NOM", nom);
         query.bindValue(":POSTE", poste);

      return query.exec();
    }

    QSqlQueryModel * ge::afficher()
    {
        QSqlQueryModel * model= new QSqlQueryModel();
      model->setQuery("select * from employe ORDER BY CIN ");

      model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN"));
      model->setHeaderData(1, Qt::Horizontal,QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal,QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal,QObject::tr("poste"));
      return model;
    }



    QSqlQueryModel * ge::afficher2(QString val)
    {
        QSqlQueryModel * model= new QSqlQueryModel();
      model->setQuery("select * from employe where CIN='"+val+"'");
      model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN"));
      model->setHeaderData(1, Qt::Horizontal,QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal,QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal,QObject::tr("poste"));
      return model;
    }


    bool ge::supprimer(long CIN)
    {
        QSqlQuery query;
        QString res= QString::number(CIN);
        query.prepare("delete from employe where CIN = :CIN");
        query.bindValue(":CIN",res);
        return query.exec();
    }
    void ge::recherche()
    {

    }

    bool ge::modifier()
    {

          QSqlQuery query;
          QString res= QString::number(CIN);
        query.prepare("update employe set  Nom= :nom, Prenom= :prenom  , Poste= :poste where CIN= :CIN") ;
        query.bindValue(":CIN", res);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
         query.bindValue(":poste", poste);

        return    query.exec();
        }
    void employe::on_pb_ajouter_clicked()
    {
        long CIN = ui->lineEdit_CIN->text().toLong();
        QString nom= ui->lineEdit_nom->text();
        QString prenom= ui->lineEdit_prenom->text();
        QString poste= ui->comboBox->currentText();

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
       long CIN = ui->lineEdit_CIN_4->text().toLong();
            QString nom= ui->lineEdit_nom_2->text();
            QString prenom= ui->lineEdit_prenom_4->text();
            QString poste=  ui->comboBox->currentText();


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


            QString val = ui->lineEdit_CIN_3->text();

                  QSqlQuery query;
                query.prepare("select * from Employe where CIN= '"+val+"'") ;
                if (query.exec())
                ui->tabemploye_2->setModel(tmpemploye.afficher2(val));

    }
    bool ge::verifier_compte(QString identifiant, QString mdp)
    {
        QSqlQuery query;
        QString mdpbd,nombombd;
        if(mdp==""||identifiant=="")
        {
            return false;
        }
        query.exec("select cin,nom from employe");
        while (query.next())
        {
            nombombd=query.value("nom").toString();
            mdpbd=query.value("cin").toString();
            if(mdp==mdpbd && identifiant==nombombd)
                return true;
        }
        return false;

    }
int ge::verifier_statut(QString identifiant,QString mdp)
{
    QSqlQuery query;
    QString role;
    query.exec("SELECT POSTE FROM employe WHERE NOM='"+identifiant+"'AND CIN='"+mdp+"'");
    while (query.next())
    {
        role=query.value("POSTE").toString();

    }
    qDebug()<<role;
    if (role=="commerciale")
        return 1;
    else if (role=="resources_humaines")
        return 2;
    else if (role=="comptable")
        return 3;
    else if (role=="caissier")
        return 4;
    else return 5;
}



