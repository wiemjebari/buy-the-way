#include "fournisseuretstocks.h"
#include "ui_fournisseuretstocks.h"
#include "fournisseuretstocks.h"
#include <QMediaPlayer>
#include <QDebug>
#include <QMessageBox>
#include<QSqlError>
#include<QThread>
#include<QSortFilterProxyModel>


fournisseuretstocks::fournisseuretstocks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fournisseuretstocks)
{
    ui->setupUi(this);
    ui->tabfournisseur->setModel(tmpfournisseur.afficher());
     ui->tabproduit->setModel(tmpstocks.afficher());
     player= new QMediaPlayer(this);
}

fournisseuretstocks::~fournisseuretstocks()
{
    delete ui;
}

fournisseur::fournisseur()
{
id=0;
telephone=0;
email="";
produitvendu="";
}
fournisseur::fournisseur(int id,int telephone,QString produitvendu,QString email)
{
 this->id=id;
 this->telephone=telephone;
 this->produitvendu=produitvendu;
 this->email=email;

}
QString fournisseur::get_produit(){return  produitvendu;}
QString fournisseur::get_email(){return email;}
int fournisseur::get_id(){return  id;}


bool fournisseur::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO fournisseur (IDENTIFIANT, PRODUITVENDU, EMAIL,TELEPHONE) "
                   "VALUES (:id, :produitvendu, :email, :telephone)");
query.bindValue(":id", res);
query.bindValue(":produitvendu", produitvendu);
query.bindValue(":email", email);
query.bindValue(":telephone", telephone);

return    query.exec();
}

QSqlQueryModel * fournisseur::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from fournisseur");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRODUITVENDU"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
   return model;
}

bool fournisseur::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from fournisseur where IDENTIFIANT = :id ");
query.bindValue(":id", res);
return    query.exec();
}

void fournisseuretstocks::on_pushButton_ajout_clicked()
{

    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
       int id =ui->lineEdit_fid->text().toInt();
       QString produit= ui->lineEdit_fproduit->text();
       QString email= ui->lineEdit_femail->text();
       int num = ui->lineEdit_fnum->text().toInt();
        bool test1=(controleEmail(email)&&controlenum(num));

        player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
        player->play();
        qDebug()<<player->errorString();
        QThread::sleep(1);
        if (test1)
        {
            fournisseur f(id,num,produit,email);
             bool test=f.ajouter();
            if(test)
            {
             ui->tabfournisseur->setModel(tmpfournisseur.afficher());
            QMessageBox::information(nullptr, QObject::tr("ajouter un fournisseur"),
                     QObject::tr("Fournisseur ajouté.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_fid->clear();
            ui->lineEdit_fproduit->clear();
            ui->lineEdit_femail->clear();
            ui->lineEdit_fnum->clear();

             }
              else
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                   QObject::tr("l'adresse email doit être \nsous la forme xxx@xxx.\n"
                               "Le Numero De Telephone doit comporter 8 Chiffres"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}


bool fournisseur::modification(int id,int telephone,QString produitvendu,QString email)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString tel= QString::number(telephone);
    query.prepare("UPDATE fournisseur SET PRODUITVENDU=:produitvendu,EMAIL=:email,TELEPHONE=:telephone where IDENTIFIANT=:id");
    query.bindValue(":id", res);
    query.bindValue(":produitvendu", produitvendu);
    query.bindValue(":email", email);
    query.bindValue(":telephone", tel);

    return    query.exec();
}
bool fournisseuretstocks::controleEmail(QString test)
{
    for(int i=0;i<test.length();i++)
    {
        if (test.at(i)=='@')
        {
            return true;
        }
    }
    return false;
}
bool fournisseuretstocks::controlenum(int test)
{
    QString tel= QString::number(test);
    for(int i=0;i<tel.length();i++)
    {
        if (tel.length()==8)
        {
            return true;
        }
    }
    return false;
}

void fournisseuretstocks::on_pushButton_modif_clicked()
{     int id = ui->lineEdit_fid_2->text().toInt();
     QString produit= ui->lineEdit_fproduit_2->text();
    QString email= ui->lineEdit_femail_2->text();
    int num = ui->lineEdit_fnum_2->text().toInt();
    fournisseur f;
      player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
      player->play();
      qDebug()<<player->errorString();
      QThread::sleep(1);
    bool test1=(controleEmail(email)&&controlenum(num));
    if (test1)
    {
    bool test=f.modification(id,num,produit,email);
    if(test)
    {
        ui->tabfournisseur->setModel(tmpfournisseur.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier un fournisseur"),
                    QObject::tr("Fournisseur modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabfournisseur->setModel(tmpfournisseur.afficher());
        ui->lineEdit_fid_2->clear();
        ui->lineEdit_fproduit_2->clear();
        ui->lineEdit_femail_2->clear();
        ui->lineEdit_fnum_2->clear();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un fournisseur"),
               QObject::tr("l'adresse email doit être \nsous la forme xxx@xxx.\n"

                          "Click Cancel to exit."), QMessageBox::Cancel);




}



void fournisseuretstocks::on_buttonBox_2_accepted()
{
    fournisseur f;
       int id = ui->lineEdit_fid_3->text().toInt();
       qDebug()<<id;
       bool test=f.supprimer(id);
       player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
       player->play();
       qDebug()<<player->errorString();
       QThread::sleep(1);
     if(test)
   {
         QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                     QObject::tr("Fournisseur supprimé.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tabfournisseur->setModel(tmpfournisseur.afficher());
         ui->lineEdit_fid_3->clear();

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}


produit::produit()
{
id=0;
prix=0;
marque="";
}



produit::produit(int id,double prix,QString marque)
{
  this->id=id;
  this->prix=prix;
  this->marque=marque;
}




QString produit::get_nom(){return  marque;}
int produit::get_id(){return  id;}
double produit::get_prix(){return  prix;}

bool produit::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
QString p= QString::number(prix);
query.prepare("INSERT INTO produit (MARQUE, PRIX , IDENTIFIANT) "
                    "VALUES (:marque, :prix, :id)");
query.bindValue(":id", res);
query.bindValue(":marque", marque);
query.bindValue(":prix", p);

return    query.exec();
}

QSqlQueryModel * produit::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from produit");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("MARQUE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    return model;
}

bool produit::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from produit where IDENTIFIANT = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool produit::modifierProduit(int id, double prix, QString marque)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString p= QString::number(prix);
    query.prepare("UPDATE produit SET MARQUE=:marque,PRIX=:prix where IDENTIFIANT=:id");
    query.bindValue(":id", res);
    query.bindValue(":marque", marque);
    query.bindValue(":prix", p);
    return    query.exec();
}


void fournisseuretstocks::on_pushButton_ajout_2_clicked()
{
    int id = ui->lineEdit_pid->text().toInt();
    QString marque= ui->lineEdit_pnom->text();
    double prix = ui->lineEdit_prix->text().toDouble();
  produit p(id,prix,marque);
  bool test=p.ajouter();
  player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
  player->play();
  qDebug()<<player->errorString();
  QThread::sleep(1);
  if(test)
{ ui->tabproduit->setModel(tmpstocks.afficher());
      QMessageBox::information(nullptr, QObject::tr("Ajouter un Produit"),
                  QObject::tr("Produit ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      ui->lineEdit_pid->clear();
      ui->lineEdit_pnom->clear();
      ui->lineEdit_prix->clear();

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Produit"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}



void fournisseuretstocks::on_pushButton_modif_2_clicked()
{
    int id = ui->lineEdit_pid_2->text().toInt();
    QString marque= ui->lineEdit_pnom_2->text();
    double prix = ui->lineEdit_prix_2->text().toDouble();
    produit p;
    bool test=p.modifierProduit(id,prix,marque);
    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier un Produit"),
                    QObject::tr("produit mofidié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabproduit->setModel(tmpstocks.afficher());
        ui->lineEdit_pid_2->clear();
        ui->lineEdit_pnom_2->clear();
        ui->lineEdit_prix_2->clear();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un Produit"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}


void fournisseuretstocks::on_buttonBox_3_accepted()
{
    int id = ui->lineEdit_fid_5->text().toInt();
  produit p;
  bool test=p.supprimer(id);
  player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
  player->play();
  qDebug()<<player->errorString();
  QThread::sleep(1);
  if(test)
{
      QMessageBox::information(nullptr, QObject::tr("Supprimer un Produit"),
                  QObject::tr("Produit supprimé.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_fid_5->clear();
      ui->tabproduit->setModel(tmpstocks.afficher());

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Supprimer un Produit"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

QSqlQueryModel * produit::Afficher_recherche(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from produit where IDENTIFIANT = '"+idd+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));

        return model;
}
QSqlQueryModel * fournisseur::Afficher_recherche(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    model->setQuery("select * from fournisseur where IDENTIFIANT = '"+idd+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRODUITVENDU"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));

        return model;
}


void fournisseuretstocks::on_buttonBox_4_accepted()
{
    QSqlQuery query;
    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
        QString search=ui->lineEdit_fid_6->text();
        qDebug()<<"Search: "<<search;
        qDebug()<<search;
        search =search+"%";
        query.prepare("select * from produit where (IDENTIFIANT LIKE :search)");
        query.bindValue(":search",search);
        if(!query.exec()){
            qDebug()<<"Query error: "<<query.lastError();
        }
        QSqlQueryModel *modal =new QSqlQueryModel();
        modal->setQuery(query);
        qDebug()<<modal->rowCount();
        ui->tabproduit_2->setModel(modal);
       ui->lineEdit_fid_6->clear();

}

void fournisseuretstocks::on_buttonBox_accepted()
{
    QSqlQuery query;
    player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/Projet/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
        QString search=ui->lineEdit_fid_4->text();
        qDebug()<<"Search: "<<search;
        qDebug()<<search;
        search =search+"%";
        query.prepare("select * from fournisseur where (IDENTIFIANT LIKE :search)");
        query.bindValue(":search",search);
        if(!query.exec()){
            qDebug()<<"Query error: "<<query.lastError();
        }
        QSqlQueryModel *modal =new QSqlQueryModel();
        modal->setQuery(query);
        qDebug()<<modal->rowCount();
        ui->tabfournisseur_2->setModel(modal);
       ui->lineEdit_fid_4->clear();

}



void fournisseuretstocks::on_pushButton_3_clicked()
{
    int id = ui->lineEdit_fid_2->text().toInt();
         QString val= QString::number(id);
           QSqlQuery query;
           query.prepare("SELECT * from fournisseur where IDENTIFIANT='"+val+"'");
                  if(query.exec())
                  {
                      while(query.next())
                      {
                          ui->lineEdit_fproduit_2->setText(query.value(1).toString());
                          ui->lineEdit_femail_2->setText(query.value(2).toString());
                          ui->lineEdit_fnum_2->setText(query.value(3).toString());
                      }

                  }
                  else
                  {
                      QMessageBox::critical(nullptr, QObject::tr("Chercher fournisseur!"),
                                            QObject::tr("Erreur!.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
                  }
}

void fournisseuretstocks::on_pushButton_4_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("select *from fournisseur");
    qry.exec();
    model->setQuery(qry);

    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(model);
    ui->tabfournisseur->setModel(m);
    ui->tabfournisseur->setSortingEnabled(true);
}

void fournisseuretstocks::on_pushButton_5_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("select *from produit");
    qry.exec();
    model->setQuery(qry);

    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
    m->setDynamicSortFilter(true);
    m->setSourceModel(model);
    ui->tabproduit->setModel(m);
    ui->tabproduit->setSortingEnabled(true);
}
