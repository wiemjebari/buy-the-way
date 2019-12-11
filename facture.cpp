#include "mainwindow.h"
#include "ui_facture.h"
#include "facture.h"
#include <QMessageBox>
#include <QPixmap>
#include <QSerialPort>
#include <QSerialPortInfo>




facture::facture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facture)
{
ui->setupUi(this);

QPixmap pix("C:/Users/user/Desktop/Facture/ressource/commande.png");
QPixmap pix2("C:/Users/user/Desktop/Facture/ressource/facture.jpg");

//ui->label_29->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));
ui->label_30->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));
ui->label_31->setPixmap(pix2.scaled(280,280,Qt::KeepAspectRatio));
ui->label_32->setPixmap(pix2.scaled(280,280,Qt::KeepAspectRatio));


ui->TabCommandes_3->setModel(tmpCommande.afficher());
ui->tableView->setModel(tmpFacture.afficher());

ui->comboBox->addItem("");
ui->comboBox->addItem("En fonction de la date");
ui->comboBox->addItem("En fonction de la Reference");
ui->comboBox->addItem("En fonction de l'etat");

ui->comboBox_4->addItem("");
ui->comboBox_4->addItem("En fonction de la catégorie");
ui->comboBox_4->addItem("En fonction de la Reference");
ui->comboBox_4->addItem("En fonction de la quantité");

ui->comboBox_2->addItem("");
ui->comboBox_2->addItem("Marche frais");
ui->comboBox_2->addItem("Alimentaire");
ui->comboBox_2->addItem("Hygiene/Beaute");
ui->comboBox_2->addItem("Maison/Jardin");
ui->comboBox_2->addItem("H.T/Electro");
ui->comboBox_2->addItem("Textile");

ui->comboBox_3->addItem("");
ui->comboBox_3->addItem("Marche frais");
ui->comboBox_3->addItem("Alimentaire");
ui->comboBox_3->addItem("Hygiene/Beaute");
ui->comboBox_3->addItem("Maison/Jardin");
ui->comboBox_3->addItem("H.T/Electro");
ui->comboBox_3->addItem("Textile");

ui->comboBox_5->addItem("");
ui->comboBox_5->addItem("En fonction de l'ID livraison");
ui->comboBox_5->addItem("En fonction du fournisseur");
ui->comboBox_5->addItem("En fonction de la position de stockage");
ui->comboBox_5->addItem("En fonction de la date de livraison");

ui->comboBox_6->addItem("");
ui->comboBox_6->addItem("En fonction de la reference");
ui->comboBox_6->addItem("En fonction du numero");
ui->comboBox_6->addItem("En fonction de l'etat");

comboBox_commandeMarque();
    comboBox_5Marque();

       arduino = new QSerialPort();
       arduino->setPortName("COM6");
       arduino->open(QSerialPort::WriteOnly);
       arduino->setBaudRate(QSerialPort::Baud9600);
       arduino->setDataBits(QSerialPort::Data8);
       arduino->setParity(QSerialPort::NoParity);
       arduino->setStopBits(QSerialPort::OneStop);
       arduino->setFlowControl(QSerialPort::NoFlowControl);
       arduino->open(QIODevice::WriteOnly);

}

facture::~facture()
{
    delete ui;
    arduino->close();
}


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
    total=0;
}
Commande::Commande(int Com,int F,QString CP,QString P,float Pr,int Q,float t)
{
    this->ID_Commande=Com;
    this->ID_Fournisseur=F;
    this->CategorieP=CP;
    this->Produit=P;
    this->PrixU=Pr;
    this->Quantite=Q;
    this->total=0;
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
    QString res4= QString::number(total);

    query.prepare("INSERT INTO tabcommande (ID_COMMANDE,ID_FOURNISSEUR,CATEGORIEP, PRODUIT,PRIXU,QUANTITE,total) "
                        "VALUES (:ID_Commande, :ID_Fournisseur, :CategorieP, :Produit, :PrixU, :Quantite,:total)");
    query.bindValue(":ID_Commande", res);
    query.bindValue(":ID_Fournisseur", res1);
    query.bindValue(":CategorieP", CategorieP);
    query.bindValue(":Produit", Produit);
    query.bindValue(":PrixU", res2);
    query.bindValue(":Quantite",res3);
    query.bindValue(":total",res4);

    return    query.exec();
}

QSqlQueryModel * Commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select id_commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite,Quantite*prixu from tabcommande ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("total"));

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

bool Commande::modifier_commande(int id_commande,int id_fournisseur,QString categoriep,QString produit,float prixu,int quantite,float total)
{
    QSqlQuery query;
    QString res= QString::number(id_commande);
    QString res1= QString::number(id_fournisseur);
    QString res2= QString::number(prixu);
    QString res3= QString::number(quantite);
    QString res4= QString::number(total);
    query.prepare("UPDATE tabcommande SET ID_COMMANDE = :ID_Commande,ID_FOURNISSEUR= :ID_Fournisseur,CATEGORIEP = :CategorieP,PRODUIT = :Produit,PRIXU = :PrixU,QUANTITE = :Quantite,total= :total WHERE(ID_COMMANDE = :ID_Commande)");
    query.bindValue(":ID_Commande", res);
    query.bindValue(":ID_Fournisseur", res1);
    query.bindValue(":CategorieP", categoriep);
    query.bindValue(":Produit", produit);
    query.bindValue(":PrixU", res2);
    query.bindValue(":Quantite",res3);
    query.bindValue(":total",res4);

    return    query.exec();
}

QSqlQueryModel * Commande::afficher_recherche(QString ID_Commande)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id_commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite,Quantite*prixu from tabcommande where ID_Commande like '"+ID_Commande+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("total"));

        return model;
    }
QSqlQueryModel * Commande::afficher_tri_ref()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select id_commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite,Quantite*prixu from tabcommande order by id_commande asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("total"));

    return model;
}

QSqlQueryModel * Commande::afficher_tri_quantite()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select id_commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite,Quantite*prixu from tabcommande order by quantite asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("total"));

    return model;
}

QSqlQueryModel * Commande::afficher_tri_categorie()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select id_commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite,Quantite*prixu from tabcommande order by CategorieP asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CategorieP"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PrixU"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("total"));

    return model;
}

/******************************************************************************************/

Livraison::Livraison()
{
    id_livraison=0;
    ID_Commande=0;
    Ref_Fournisseur=0;
    position_livraison=0;
    heure_livraison="";
   date_livraison="";
    agent_responsable="";

}
Livraison::Livraison(int id_livraison,int Ref_Fournisseur,int ID_Commande,int position_livraison ,QString heure_livraison,QString date_livraison,QString agent_responsable)

{
    this->id_livraison=id_livraison;
    this->Ref_Fournisseur=Ref_Fournisseur;
    this->ID_Commande=ID_Commande;
    this->position_livraison=position_livraison;
    this->heure_livraison=heure_livraison;
    this->date_livraison=date_livraison;
    this->agent_responsable=agent_responsable;
}
QString Livraison::get_heure_livraison(){return heure_livraison;}
QString Livraison::get_date_livraison(){return date_livraison;}
QString Livraison::get_agent_responsable(){return agent_responsable;}
int Livraison::get_Ref_Fournisseur(){return Ref_Fournisseur;}
int Livraison::get_ID_Commande(){return ID_Commande;}
int Livraison::get_position(){return position_livraison;}
int Livraison::get_id_livraison(){return id_livraison;}


bool Livraison::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(Ref_Fournisseur);
    QString res1= QString::number(ID_Commande);
    QString res2= QString::number(position_livraison);
    QString res3= QString::number(id_livraison);



    query.prepare("INSERT INTO livraison (id_livraison,Ref_Fournisseur,ID_Commande,position_livraison, heure_livraison,date_livraison,agent_responsable) "
                        "VALUES (:id_livraison,:Ref_Fournisseur, :ID_Commande, :position_livraison, :heure_livraison, :date_livraison, :agent_responsable)");
    query.bindValue(":id_livraison", res3);
    query.bindValue(":Ref_Fournisseur", res);
    query.bindValue(":ID_Commande", res1);
    query.bindValue(":position_livraison", res2);
    query.bindValue(":heure_livraison", heure_livraison);
    query.bindValue(":date_livraison", date_livraison);
    query.bindValue(":agent_responsable",agent_responsable);

    return    query.exec();
}

QSqlQueryModel * Livraison::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select id_livraison,Ref_Fournisseur,ID_Commande,position_livraison,heure_livraison,date_livraison,agent_responsable from livraison ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Fournisseur"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_Commande "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("position_livraison"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("heure_livraison"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_livraison"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("agent_responsable"));

    return model;
}

bool Livraison::supprimer(int id_livraison)
{
QSqlQuery query;
QString res= QString::number(id_livraison);
query.prepare("Delete from livraison where id_livraison = :id_livraison ");
query.bindValue(":id_livraison", res);
return    query.exec();
}

bool Livraison::modifier_livraison(int id_livraison,int Ref_Fournisseur,int ID_Commande,int position_livraison ,QString heure_livraison,QString date_livraison,QString agent_responsable)
{   QSqlQuery query;
    QString res= QString::number(id_livraison);
    QString res1= QString::number(Ref_Fournisseur);
    QString res2= QString::number(ID_Commande);
    QString res3= QString::number(position_livraison);
    query.prepare("UPDATE livraison SET id_livraison = :id_livraison,Ref_Fournisseur= :Ref_Fournisseur,ID_Commande = :ID_Commande,position_livraison = :position_livraison,heure_livraison = :heure_livraison,date_livraison = :date_livraison,agent_responsable= :agent_responsable WHERE(id_livraison = :id_livraison)");
    query.bindValue(":id_livraison", res);
    query.bindValue(":Ref_Fournisseur", res1);
    query.bindValue(":ID_Commande", res2);
    query.bindValue(":position_livraison", res3);
    query.bindValue(":heure_livraison", heure_livraison);
    query.bindValue(":date_livraison",date_livraison);
    query.bindValue(":agent_responsable",agent_responsable);

    return    query.exec();
}

QSqlQueryModel * Livraison::afficher_recherche(QString id_livraison)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id_livraison,Ref_Fournisseur,ID_Commande,position_livraison,heure_livraison,date_livraison,agent_responsable from livraison where id_livraison like '"+id_livraison+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Fournisseur "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_Commande"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("position_livraison"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("heure_livraison"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_livraison"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("agent_responsable"));

        return model;
    }
QSqlQueryModel *  Livraison::afficher_tri_id_livraison()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select id_livraison,Ref_Fournisseur,ID_Commande,position_livraison,heure_livraison,date_livraison,agent_responsable from livraison order by id_livraison asc ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Fournisseur "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_Commande"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("position_livraison"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("heure_livraison"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_livraison"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("agent_responsable"));

    return model;
}

QSqlQueryModel * Livraison::afficher_tri_Ref_Fournisseur()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id_livraison,Ref_Fournisseur,ID_Commande,position_livraison,heure_livraison,date_livraison,agent_responsable from livraison order by Ref_Fournisseur asc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Fournisseur "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_Commande"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("position_livraison"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("heure_livraison"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_livraison"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("agent_responsable"));

    return model;
}

QSqlQueryModel * Livraison::afficher_tri_position_livraison()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id_livraison,Ref_Fournisseur,ID_Commande,position_livraison,heure_livraison,date_livraison,agent_responsable from livraison order by position_livraison asc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Fournisseur "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_Commande"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("position_livraison"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("heure_livraison"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_livraison"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("agent_responsable"));

    return model;
}

QSqlQueryModel * Livraison::afficher_tri_date_livraison()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id_livraison,Ref_Fournisseur,ID_Commande,position_livraison,heure_livraison,date_livraison,agent_responsable from livraison order by date_livraison asc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Fournisseur "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_Commande"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("position_livraison"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("heure_livraison"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_livraison"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("agent_responsable"));

    return model;
}
Recu::Recu()
{
    Num_Recu=0;
    Ref_Facture=0;
    etat="Non imprimee";
}

Recu::Recu(int Num_Recu,int Ref_Facture,QString etat)
{
  this->Num_Recu=Num_Recu;
  this->Ref_Facture=Ref_Facture;
  this->etat=etat;
}
int Recu::get_Num_Recu(){return  Num_Recu;}
int Recu::get_Ref_Facture(){return Ref_Facture;}
QString Recu::get_etat(){return  etat;}

bool Recu::ajouter()
{
QSqlQuery query;
QString res= QString::number(Num_Recu);
QString res1= QString::number(Ref_Facture);
query.prepare("INSERT INTO Recu (Num_Recu,Ref_Facture,etat) "
                    "VALUES (:Num_Recu, :Ref_Facture, :etat)");
query.bindValue(":Num_Recu", res);
query.bindValue(":Ref_Facture", res1);
query.bindValue(":etat", etat);
return    query.exec();

}

QSqlQueryModel * Recu::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Recu ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_Recu"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Facture "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}

QSqlQueryModel * Recu::afficher_tri_ref()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Recu order by Ref_Facture asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_Recu"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Facture "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}

QSqlQueryModel * Recu::afficher_tri_num()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Recu order by Num_Recu asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_Recu"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Facture "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}

QSqlQueryModel * Recu::afficher_tri_etat()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Recu order by etat asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_Recu"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Facture "));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));

    return model;
}



QSqlQueryModel * Recu::afficher_recherche(QString Num_Recu)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Recu  where Num_Recu like '"+Num_Recu+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_Recu"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ref_Facture "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("etat"));
        return model;
}

bool Recu::supprimer(int Num_Recu)
{
QSqlQuery query;
QString res= QString::number(Num_Recu);
query.prepare("Delete from Recu where Num_Recu = :Num_Recu ");
query.bindValue(":Num_Recu", res);
return    query.exec();
}


void facture::on_tableView_2_activated(const QModelIndex &index)
{
      ui->tableView_2->setModel(tmpFacture.afficher());
}

void facture::on_tableView_3_activated(const QModelIndex &index)
{
    ui->tableView_3->setModel(tmpCommande.afficher());
}


void facture::on_lineEdit_recherch_commande_textChanged(const QString &arg1)
{
    QString ID_Commande= ui->lineEdit_recherch_commande->text();
    ui->tableView_3->setModel(tmpCommande.afficher_recherche(ID_Commande));
}
void facture::comboBox_commandeMarque()
{
    QSqlQuery query;
    query.prepare("select ID_COMMANDE from TABCOMMANDE");
    query.exec();
    qDebug()<<query.first();
    QSqlQueryModel *modal =new QSqlQueryModel();
    modal->setQuery(query);
    qDebug()<<modal->rowCount();
    ui->comboBox_commande->setModel(modal);
    ui->comboBox_commande_2->setModel(modal);
    ui->comboBox_7->setModel(modal);
}
void facture::comboBox_5Marque()
{
    QSqlQuery query;
    query.prepare("select IDENTIFIANT from fournisseur");
    query.exec();
    qDebug()<<query.first();
    QSqlQueryModel *modal =new QSqlQueryModel();
    modal->setQuery(query);
    qDebug()<<modal->rowCount();
    ui->comboBox_5->setModel(modal);
    ui->comboBox_6->setModel(modal);

}

void facture::on_pb_ajouter_facture_clicked()
{
    //player = new QMediaPlayer;
   // player->setMedia((QUrl::fromLocalFile()));
    int Ref_Facture = ui->lineEdit_Reference_8->text().toInt();
    int ID_Commande= ui->lineEdit_Reference_10->text().toInt();
    QString description=ui->lineEdit_description_facture->text();
    QString date=ui->lineEdit_Date->text();
    float montant=ui->lineEdit_ID_Commande3_3->text().toFloat();
    QString etat;
    if(ui->radioButton->isChecked())
    {
        etat= ui->radioButton->text();
    }
    else if(ui->radioButton_2->isChecked())
    {
        etat= ui->radioButton_2->text();
    }

    Facture c(Ref_Facture,ID_Commande,description,date,montant,etat);

    bool test=c.ajouter();
    if(test)
    {
        ui->tableView->setModel(tmpFacture.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter une facture"),
                  QObject::tr("facture ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une facture"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void facture::on_pushButton_modifier_facture_clicked()
{
    int Ref_Facture = ui->lineEdit_Reference_12->text().toInt();
    int ID_Commande= ui->lineEdit_Reference_11->text().toInt();
    QString description=ui->lineEdit_ID_Fournisseur3_4->text();
    QString date=ui->lineEdit_ID_Fournisseur3_5->text();
    float montant=ui->lineEdit_ID_Commande3_4->text().toFloat();
    QString etat;
    if(ui->radioButton_3->isChecked())
    {
        etat= ui->radioButton_3->text();
    }
    else if(ui->radioButton_4->isChecked())
    {
        etat= ui->radioButton_4->text();
    }
    bool test= tmpFacture.modifier_facture(Ref_Facture,ID_Commande,description,date,montant,etat);
    if(test)
    {
        ui->tableView->setModel(tmpFacture.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier une facture"),
                  QObject::tr("facture modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
     {   QMessageBox::critical(nullptr, QObject::tr("Modifier une facture"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
}


void facture::on_pb_supprimer_facture_clicked()
{
    {
        int Ref_Facture = ui->lineEdit_Reference_9->text().toInt();
        bool test=tmpFacture.supprimer(Ref_Facture);
        if(test)
        {ui->tableView->setModel(tmpFacture.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer une facture"),
                        QObject::tr("facture supprimée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer une facture"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }



}

void facture::on_lineEdit_recherche_textChanged(const QString &arg1)
{
    QString Ref_Facture= ui->lineEdit_recherche->text();

        ui->tableView_2->setModel(tmpFacture.afficher_recherche(Ref_Facture));
}

void facture::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString tri=ui->comboBox->currentText();
    if(tri=="")
        ui->tableView->setModel(tmpFacture.afficher());
    else if(tri=="En fonction de la Reference")
        ui->tableView->setModel(tmpFacture.afficher_tri_ref());
    else if(tri=="En fonction de la date")
        ui->tableView->setModel(tmpFacture.afficher_tri_date());
    else if(tri=="En fonction de l'etat")
        ui->tableView->setModel(tmpFacture.afficher_tri_etat());
}

void facture::on_lineEdit_Reference_12_textChanged(const QString &arg1)
{
    QString Ref_Facture=ui->lineEdit_Reference_12->text();
    QSqlQuery gry;
    gry.prepare("select * from facture where REF_FACTURE='"+Ref_Facture+"'");
    if(gry.exec())
    {
        while (gry.next())
        {
         ui->lineEdit_Reference_11->setText(gry.value(1).toString());
         ui->lineEdit_ID_Fournisseur3_4->setText(gry.value(2).toString());
         ui->lineEdit_ID_Fournisseur3_5->setText(gry.value(3).toString());
         ui->lineEdit_ID_Commande3_4->setText(gry.value(4).toString());

        }
    }

}



/*********************************************************************************/


void facture::on_Commander_3_clicked()
{
    int ID_Commande = ui->lineEdit_ID_Commande_3->text().toInt();
    int ID_Fournisseur= ui->lineEdit_ID_Fournisseur_3->text().toInt();
    QString CategorieP=  ui->comboBox_2->currentText();
    QString Produit= ui->lineEdit_Produit_3->text();
    float PrixU= ui->lineEdit_PrixU_3->text().toFloat();
    int Quantite = ui->lineEdit_Quantite_3->text().toInt();
    float total=0;
  Commande e(ID_Commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite,total);
  bool test=e.ajouter_commande();


  if(test)
{
      arduino->write("1");

ui->TabCommandes_3->setModel(tmpCommande.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une Commande"),
                  QObject::tr("Commande ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

  else
  {  arduino->write("0");

      QMessageBox::critical(nullptr, QObject::tr("Ajouter une Commande"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }

}

void facture::on_pb_supprimer_5_clicked()
{
    int ID_Commande = ui->lineEdit_SupprimerCommande->text().toInt();
    bool test=tmpCommande.supprimer_commande(ID_Commande);
    if(test)
    {ui->TabCommandes_3->setModel(tmpCommande.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une Commande"),
                    QObject::tr("Commande supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une Commande"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void facture::on_pb_modifier_commande_clicked()
{
    int ID_Commande = ui->lineEdit_modifierID_commande->text().toInt();
    int ID_Fournisseur= ui->lineEdit_modifierID_fournisseur->text().toInt();
    QString CategorieP=  ui->comboBox_3->currentText();
    QString Produit= ui->lineEdit_modifierProduit->text();
    float PrixU= ui->lineEdit_modifier_PrixU->text().toFloat();
    int Quantite = ui->lineEdit_modifier_quantite->text().toInt();
float total=0;
          bool test=tmpCommande.modifier_commande(ID_Commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite,total);
          if(test)
            {ui->TabCommandes_3->setModel(tmpCommande.afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Modifier une commande"),
                            QObject::tr("Donnée modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
               { QMessageBox::critical(nullptr, QObject::tr("Modifier une commande"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
}






void facture::on_lineEdit_recherche_commande_textChanged(const QString &arg1)
{
    QString ID_Commande= ui->lineEdit_recherche_commande->text();

        ui->tableView_3->setModel(tmpCommande.afficher_recherche(ID_Commande));
}

void facture::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    QString tri=ui->comboBox_4->currentText();
    if(tri=="")
        ui->TabCommandes_3->setModel(tmpCommande.afficher());
    else if(tri=="En fonction de la quantité")
        ui->TabCommandes_3->setModel(tmpCommande.afficher_tri_quantite());
    else if(tri=="En fonction de la catégorie")
        ui->TabCommandes_3->setModel(tmpCommande.afficher_tri_categorie());
    else if(tri=="En fonction de la Reference")
        ui->TabCommandes_3->setModel(tmpCommande.afficher_tri_ref());
}

void facture::on_lineEdit_modifierID_commande_textChanged(const QString &arg1)
{
    QString ID_COMMANDE=ui->lineEdit_modifierID_commande->text();
    QSqlQuery gry;
    gry.prepare("select * from tabcommande where ID_COMMANDE='"+ID_COMMANDE+"'");
    if(gry.exec())
    {
        while (gry.next())
        {
         ui->lineEdit_modifierID_fournisseur->setText(gry.value(1).toString());
         ui->lineEdit_modifierProduit->setText(gry.value(3).toString());
         ui->lineEdit_modifier_PrixU->setText(gry.value(4).toString());
         ui->lineEdit_modifier_quantite->setText(gry.value(5).toString());

        }
    }
}
/*
// get input values:
float f = ui->inputWidget->text().toFloat();
// calculate something
// ...
// update output lineEdit or what so ever:
ui->outputLineEdit->setText(QString::number(f));
}@*/

/*********************************************************************************/


void facture::on_pushButton_ajouter_livraison_clicked()
{

    int id_livraison  = ui->lineEdit_livraison_ID_livraison->text().toInt();
    int ID_Commande= ui->lineEdit_livraison_ID_commande->text().toInt();
    int Ref_Fournisseur=ui->lineEdit_livraison_Ref_fournisseur->text().toInt();
    int  position=ui->lineEdit_6->text().toInt();
    QString heure_livraison=  ui->lineEdit__livraison_heure_livraison->text();
    QString date_livraison= ui->lineEdit_livraison_date_livraison->text();
    QString agent_responsable= ui->lineEdit_livraison_agent_livraison->text();

  Livraison e(id_livraison,ID_Commande,Ref_Fournisseur,position,heure_livraison,date_livraison,agent_responsable);
  bool test=e.ajouter();


  if(test)
{

ui->tableView_4->setModel(tmpLivraison.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une livraison"),
                  QObject::tr("livraison ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

  else
  {

      QMessageBox::critical(nullptr, QObject::tr("Ajouter une livraison"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }

}



void facture::on_pushButton_modifier_clicked()
{

    int id_livraison  = ui->lineEdit_livraison_ID_livraison_2->text().toInt();
    int ID_Commande= ui->lineEdit_livraison_ID_commande_4->text().toInt();
    int Ref_Fournisseur=ui->lineEdit_livraison_Ref_fournisseur_4->text().toInt();
    int  position=ui->lineEdit_9->text().toInt();
    QString heure_livraison=  ui->lineEdit__livraison_heure_livraison_4->text();
    QString date_livraison= ui->lineEdit_livraison_date_livraison_4->text();
    QString agent_responsable= ui->lineEdit_livraison_agent_livraison_4->text();

     bool test=tmpLivraison.modifier_livraison(id_livraison,ID_Commande,Ref_Fournisseur,position,heure_livraison,date_livraison,agent_responsable);
          if(test)
            {ui->tableView_4->setModel(tmpLivraison.afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Modifier une livraison"),
                            QObject::tr("livraison modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
               { QMessageBox::critical(nullptr, QObject::tr("Modifier une livraison"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
}

void facture::on_pushButton_supprimer_clicked()
{
    int id_livraison = ui->lineEdit_SupprimerCommande_2->text().toInt();
    bool test=tmpLivraison.supprimer(id_livraison);
    if(test)
    {ui->tableView_4->setModel(tmpLivraison.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une livraison"),
                    QObject::tr("livraison supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une livraison"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void facture::on_lineEdit_rechercher_livraison_textChanged(const QString &arg1)
{
    QString id_livraison= ui->lineEdit_rechercher_livraison->text();

        ui->tableView_5->setModel(tmpLivraison.afficher_recherche(id_livraison));
}

void facture::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    QString tri=ui->comboBox_5->currentText();
    if(tri=="")
        ui->tableView_4->setModel(tmpLivraison.afficher());
    else if(tri=="En fonction de l'ID livraison")
        ui->tableView_4->setModel(tmpLivraison.afficher_tri_id_livraison());
    else if(tri=="En fonction du fournisseur")
        ui->tableView_4->setModel(tmpLivraison.afficher_tri_Ref_Fournisseur());
    else if(tri=="En fonction de la position de stockage")
        ui->tableView_4->setModel(tmpLivraison.afficher_tri_position_livraison());
    else if(tri=="En fonction de la date de livraison")
        ui->tableView_4->setModel(tmpLivraison.afficher_tri_date_livraison());
}

void facture::on_lineEdit_livraison_ID_livraison_2_textChanged(const QString &arg1)
{

    QString id_livraison=ui->lineEdit_livraison_ID_livraison_2->text();
    QSqlQuery gry;
    gry.prepare("select * from livraison where id_livraison='"+id_livraison+"'");
    if(gry.exec())
    {
        while (gry.next())
        {
         ui->lineEdit_livraison_ID_commande_4->setText(gry.value(2).toString());
         ui->lineEdit_livraison_Ref_fournisseur_4->setText(gry.value(1).toString());
         ui->lineEdit_livraison_date_livraison_4->setText(gry.value(5).toString());
         ui->lineEdit__livraison_heure_livraison_4->setText(gry.value(4).toString());
         ui->lineEdit_livraison_agent_livraison_4->setText(gry.value(6).toString());
         ui->lineEdit_9->setText(gry.value(3).toString());



        }
    }

}




void facture::on_pb_ajouter_facture_2_clicked()
{
    int Num_Recu = ui->lineEdit_3->text().toInt();
    int Ref_Facture= ui->lineEdit_4->text().toInt();
    QString etat = ui->lineEdit_5->text();
    Recu c(Num_Recu,Ref_Facture,etat);
    bool test=c.ajouter();
    if(test)
    {
        ui->tableView_6->setModel(tmpRecu.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un Recu"),
                  QObject::tr("Recu ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un Recu"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void facture::on_pb_supprimer_facture_2_clicked()
{
        int Num_Recu = ui->lineEdit->text().toInt();
        bool test=tmpRecu.supprimer(Num_Recu);
        if(test)
        {ui->tableView_6->setModel(tmpRecu.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer un recu"),
                        QObject::tr("recu supprimée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un recu"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void facture::on_comboBox_6_editTextChanged(const QString &arg1)
{
    QString tri=ui->comboBox_6->currentText();
    if(tri=="")
        ui->tableView_6->setModel(tmpRecu.afficher());
    else if(tri=="En fonction du numero")
        ui->tableView_6->setModel(tmpRecu.afficher_tri_num());
    else if(tri=="En fonction de la reference")
        ui->tableView_6->setModel(tmpRecu.afficher_tri_ref());
    else if(tri=="En fonction de l'etat")
        ui->tableView_6->setModel(tmpRecu.afficher_tri_etat());
}

void facture::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString id_livraison= ui->lineEdit_2->text();

        ui->tableView_7->setModel(tmpRecu.afficher_recherche(id_livraison));
}
