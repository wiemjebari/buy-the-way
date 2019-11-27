#include "facture.h"
#include <QDebug>


Facture::Facture()
{
    Ref_Facture=0;
    ID_Commande=0;
    montant=0;
    description=" ";
    etat=" ";
    date=" ";
}

Facture::Facture(int Ref_Facture,int ID_Commande,QString description,QString date,float montant,QString etat)
{
  this->Ref_Facture=Ref_Facture;
  this->ID_Commande=ID_Commande;
  this->description=description;
  this->montant=montant;
  this->etat=etat;
  this->date=date;

}
int Facture::get_Ref_Facture(){return  Ref_Facture;}
int Facture::get_ID_Commande(){return ID_Commande;}
QString Facture::get_description(){return  description;}
int Facture::get_montant(){return  montant;}
QString Facture::get_date(){return  date;}
QString Facture::get_etat(){return  etat;}



bool Facture::ajouter()
{
QSqlQuery query;
QString res= QString::number(Ref_Facture);
QString res1= QString::number(ID_Commande);
QString res2= QString::number(montant);
query.prepare("INSERT INTO facture (REF_Facture,ID_COMMANDE,DESCRIPTION,date_f, montant,etat) "
                    "VALUES (:Ref_Facture, :ID_Commande, :description,:date, :montant, :etat)");
query.bindValue(":Ref_Facture", res);
query.bindValue(":ID_Commande", res1);
query.bindValue(":description", description);
query.bindValue(":date", date);
query.bindValue(":montant", res2);
query.bindValue(":etat", etat);

return    query.exec();

}

QSqlQueryModel * Facture::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from facture ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ref_Facture"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Commande "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}

QSqlQueryModel * Facture::afficher_tri_date()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from facture order by date_f asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ref_Facture"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Commande "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}

QSqlQueryModel * Facture::afficher_tri_ref()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from facture order by Ref_Facture asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ref_Facture"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Commande "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}

QSqlQueryModel * Facture::afficher_tri_etat()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from facture order by etat asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ref_Facture"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Commande "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}



QSqlQueryModel * Facture::afficher_recherche(QString Ref_Facture)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from facture  where Ref_Facture like '"+Ref_Facture+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Ref_Facture"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Commande "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));
        return model;
}


bool Facture::supprimer(int Ref_Facture)
{
QSqlQuery query;
QString res= QString::number(Ref_Facture);
query.prepare("Delete from Facture where Ref_Facture = :Ref_Facture ");
query.bindValue(":Ref_Facture", res);
return    query.exec();
}


bool Facture::modifier_facture(int Ref_Facture, int ID_Commande, QString description, QString date, float montant, QString etat)
{
    QSqlQuery query;
    QString res= QString::number(Ref_Facture);
    QString res1= QString::number(ID_Commande);
    QString res2= QString::number(montant);
    query.prepare("UPDATE facture SET REF_FACTURE = :Ref_Facture,ID_COMMANDE= :ID_Commande,DESCRIPTION = :description,date_f = :date,montant = :montant,etat = :etat WHERE(Ref_Facture = :Ref_Facture)");
    query.bindValue(":Ref_Facture", res);
    query.bindValue(":ID_Commande", res1);
    query.bindValue(":description", description);
    query.bindValue(":date", date);
    query.bindValue(":montant", res2);
    query.bindValue(":etat",etat);
    return    query.exec();
}

/********************************************************************************/


Commande::Commande()
{
    ID_Commande=0;
    ID_Fournisseur=0;
    CategorieP="";
    Produit="";
    PrixU=0.0;
    Quantite=0;
}
Commande::Commande(int Com,int F,QString CP,QString P,float Pr,int Q)
{
    this->ID_Commande=Com;
    this->ID_Fournisseur=F;
    this->CategorieP=CP;
    this->Produit=P;
    this->PrixU=Pr;
    this->Quantite=Q;
}
QString Commande::get_Categorie(){return CategorieP;}
QString Commande::get_Produit(){return Produit;}
int Commande::get_ID_Commande(){return ID_Commande;}
int Commande::get_ID_Founisseur(){return ID_Fournisseur;}
int Commande::get_Quantite(){return Quantite;}
float Commande::get_Prix(){return PrixU;}
//float Commande::get_Total(){return Total;}

bool Commande::ajouter_commande()
{
    QSqlQuery query;
    QString res= QString::number(ID_Commande);
    QString res1= QString::number(ID_Fournisseur);
    QString res2= QString::number(PrixU);
    QString res3= QString::number(Quantite);
    query.prepare("INSERT INTO tabcommande (ID_COMMANDE,ID_FOURNISSEUR,CATEGORIEP, PRODUIT,PRIXU,QUANTITE) "
                        "VALUES (:ID_Commande, :ID_Fournisseur, :CategorieP, :Produit, :PrixU, :Quantite)");
    query.bindValue(":ID_Commande", res);
    query.bindValue(":ID_Fournisseur", res1);
    query.bindValue(":CategorieP", CategorieP);
    query.bindValue(":Produit", Produit);
    query.bindValue(":PrixU", res3);
    query.bindValue(":Quantite",res2);

    return    query.exec();
}

QSqlQueryModel * Commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from tabcommande ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
}

bool Commande::supprimer_commande(int ID_Commande)
{
QSqlQuery query;
QString res= QString::number(ID_Commande);
query.prepare("Delete from tabcommande where ID_Commande = :ID_Commande ");
query.bindValue(":ID_Commande", res);
return    query.exec();
}

bool Commande::modifier_commande(int id_commande,int id_fournisseur,QString categoriep,QString produit,float prixu,int quantite)
{
    QSqlQuery query;
    QString res= QString::number(id_commande);
    QString res1= QString::number(id_fournisseur);
    QString res2= QString::number(prixu);
    QString res3= QString::number(quantite);
    query.prepare("UPDATE tabcommande SET ID_COMMANDE = :ID_Commande,ID_FOURNISSEUR= :ID_Fournisseur,CATEGORIEP = :CategorieP,PRODUIT = :Produit,PRIXU = :PrixU,QUANTITE = :Quantite WHERE(ID_COMMANDE = :ID_Commande)");
    query.bindValue(":ID_Commande", res);
    query.bindValue(":ID_Fournisseur", res1);
    query.bindValue(":CategorieP", categoriep);
    query.bindValue(":Produit", produit);
    query.bindValue(":PrixU", res3);
    query.bindValue(":Quantite",res2);
    return    query.exec();
}

QSqlQueryModel * Commande::afficher_recherche(QString ID_Commande)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from tabcommande where ID_Commande like '"+ID_Commande+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
        return model;
    }
QSqlQueryModel * Commande::afficher_tri_ref()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from tabcommande order by id_commande asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
}

QSqlQueryModel * Commande::afficher_tri_quantite()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from tabcommande order by quantite asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
}

QSqlQueryModel * Commande::afficher_tri_categorie()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from tabcommande order by CategorieP asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
}
