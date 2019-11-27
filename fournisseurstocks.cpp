#include "fournisseurstocks.h"
#include <QDebug>
#include <QMessageBox>
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
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TELEPHONE"));
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


void AjoutModifFournisseur::on_pushButton_ajout_clicked()
{   fournisseur f;
    int id =ui->lineEdit_fid->text().toInt();
    QString produit= ui->lineEdit_fproduit->text();
    QString email= ui->lineEdit_femail->text();
    int num = ui->lineEdit_fnum->text().toInt();
  fournisseur f(id,num,produit,email);
  bool test=f.ajouter();
  AffichageFournisseur af;
  if(test)
{ QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                  QObject::tr("Fournisseur ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}



void AjoutModifFournisseur::on_pushButton_modif_clicked()
{
    int id = ui->lineEdit_fid->text().toInt();
    QString produit= ui->lineEdit_fproduit->text();
    QString email= ui->lineEdit_femail->text();
    int num = ui->lineEdit_fnum->text().toInt();
  fournisseur f(id,num,produit,email);
  bool test1=f.supprimer(id);
  if(test1)
 { bool test=f.ajouter();
  AffichageFournisseur af;
  if(test)
{ QMessageBox::information(nullptr, QObject::tr("modifier un fournisseur"),
                  QObject::tr("Fournisseur modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  }
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier un fournisseur"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
AffichageFournisseur::AffichageFournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffichageFournisseur)
{
    ui->setupUi(this);
    ui->tabfournisseur->setModel(tmpfournisseur.afficher());
}


void SupprimerFournisseur::on_buttonBox_2_accepted()
{   fournisseur f;
    int id = ui->lineEdit_fid->text().toInt();
    bool test=f.supprimer(id);
  if(test)
{ QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                  QObject::tr("Fournisseur ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void GestionFournisseur::on_pushButton_notif_clicked()
{
    Notification n;
    this->hide();
    n.setModal(true);
    n.exec();
  }


