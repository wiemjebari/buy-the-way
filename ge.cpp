#include "ge.h"
#include "mainwindow.h"

#include <QDebug>

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
      model->setQuery("select * from employe ORDER BY POSTE ");

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

