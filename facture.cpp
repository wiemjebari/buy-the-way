#include "facture.h"
#include "ui_facture.h"
#include"QMessageBox"
#include<QDebug>
facture::facture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facture)
{
    ui->setupUi(this);
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
    comboBox_commandeMarque();
    comboBox_5Marque();

    arduino = new QSerialPort;

    arduino_port_name = "";
    arduino_is_available = false;

    /*for (QSerialPortInfo info : QSerialPortInfo::availablePorts())
    {
       qDebug() << "Port Name   :" << info.portName();
       qDebug() << "Description :" << info.description();
       qDebug() << "Manufacturer:" << info.manufacturer();
       qDebug() << "Vendor ID   :" << info.vendorIdentifier();
       qDebug() << "Product ID  :" << info.productIdentifier();
    }*/

    for (QSerialPortInfo info : QSerialPortInfo::availablePorts())
        {
           if(info.hasVendorIdentifier() && info.hasProductIdentifier())
           {
               if(info.vendorIdentifier() == arduino_uno_vendor_ID)
               {
                   if(info.productIdentifier() == arduino_uno_product_ID)
                   {
                       arduino_port_name = info.portName();
                       arduino_is_available = true;
                   }
               }
           }
        }
    if(arduino_is_available)
    {
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

    }
    else
    {
        QMessageBox::warning(this,"Port ERROR !","Couldn't find the arduino.\nPlease check your connection !");
    }
}

facture::~facture()
{
    if(arduino->isOpen())
    {
        arduino->close();
    }
    delete ui;
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

Facture::Facture(int Ref_Facture,int ID_Commande,QString description,QString date,int montant,QString etat)
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
query.prepare("INSERT INTO facture (REF_FACTURE,ID_COMMANDE,DESCRIPTION,DATE_F, MONTANT,ETAT) "
                    "VALUES (:Ref_Facture, :ID_Commande, :description,:date, :montant, :etat)");
query.bindValue(":Ref_Facture", res);
query.bindValue(":ID_Commande", res1);
query.bindValue(":description", description);
query.bindValue(":date", date);
query.bindValue(":montant", res2);
query.bindValue(":etat", etat);
return    query.exec();

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

QSqlQueryModel * Facture::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from facture order by Ref_Facture desc");
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

    model->setQuery("select * from facture  where Ref_Facture like '"+Ref_Facture+"%'");
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


bool Facture::modifier_facture(int Ref_Facture, int ID_Commande, QString description, QString date, int montant, QString etat)
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
    //QString res2= QString::number(PrixU);
    QString res3= QString::number(Quantite);
    query.prepare("INSERT INTO tabcommande (ID_COMMANDE,ID_FOURNISSEUR,CATEGORIEP, PRODUIT,QUANTITE,PRIXU) "
                        "VALUES (:ID_Commande, :ID_Fournisseur, :CategorieP, :Produit, :Quantite, :PrixU)");
    query.bindValue(":ID_Commande", res);
    query.bindValue(":ID_Fournisseur", res1);
    query.bindValue(":CategorieP", CategorieP);
    query.bindValue(":Produit", Produit);
    query.bindValue(":PrixU", 12.2);
    query.bindValue(":Quantite",res3);

    return    query.exec();
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


QSqlQueryModel * Commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from tabcommande order by ID_Commande desc ");
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



void facture::on_lineEdit_recherch_textChanged(const QString &arg1)
{
    QString Ref_Facture= ui->lineEdit_recherch->text();
    ui->tableView_2->setModel(tmpFacture.afficher_recherche(Ref_Facture));
}

/*********************************************************************************/


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
         //ui->lineEdit_Reference_11->setText(gry.value(1).toString());
         ui->lineEdit_ID_Fournisseur3_4->setText(gry.value(2).toString());
         ui->lineEdit_ID_Fournisseur3_5->setText(gry.value(3).toString());
         ui->lineEdit_ID_Commande3_4->setText(gry.value(4).toString());

        }
    }

}


void facture::on_pb_modifier_command_clicked()
{
    int ID_Commande = ui->lineEdit_modifierID_commande->text().toInt();
    int ID_Fournisseur= ui->comboBox_6->currentText().toInt();
    QString CategorieP= ui->comboBox_3->currentText();
    QString Produit= ui->lineEdit_modifierProduit->text();
    double PrixU= ui->lineEdit_modifier_PrixU->text().toDouble();
    int Quantite = ui->lineEdit_modifier_quantite->text().toInt();

          bool test=tmpCommande.modifier_commande(ID_Commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite);
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

void facture::on_pb_supprime_5_clicked()
{
    int ID_Commande = ui->comboBox_7->currentText().toInt();
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

void facture::on_pb_ajouter_factur_clicked()
{
    int Ref_Facture = ui->lineEdit_Reference_8->text().toInt();
    int ID_Commande= ui->comboBox_commande->currentText().toInt();
    QString description=ui->lineEdit_description_facture->text();
    QString date=ui->lineEdit_Date->text();
    int montant=ui->lineEdit_ID_Commande3_3->text().toInt();
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

void facture::on_pushButton_modifier_factur_clicked()
{
    int Ref_Facture = ui->lineEdit_Reference_12->text().toInt();
    int ID_Commande= ui->comboBox_commande_2->currentText().toInt();
    QString description=ui->lineEdit_ID_Fournisseur3_4->text();
    QString date=ui->lineEdit_ID_Fournisseur3_5->text();
    int montant=ui->lineEdit_ID_Commande3_4->text().toInt();
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
}


void facture::on_pb_supprime_facture_clicked()
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



void facture::on_Commander_3_clicked()
{
    int ID_Commande = ui->lineEdit_ID_Commande_3->text().toInt();
       int ID_Fournisseur= ui->comboBox_5->currentText().toInt();
       QString CategorieP= ui->comboBox_3->currentText();
       QString Produit= ui->lineEdit_Produit_3->text();
       float PrixU= ui->lineEdit_PrixU_3->text().toFloat();
       int Quantite = ui->lineEdit_Quantite_3->text().toInt();
     Commande e(ID_Commande,ID_Fournisseur,CategorieP,Produit,PrixU,Quantite);
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
         arduino->write("0");
         QMessageBox::critical(nullptr, QObject::tr("Ajouter une Commande"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

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
         //ui->lineEdit_modifierID_fournisseur->setText(gry.value(1).toString());
         ui->lineEdit_modifierProduit->setText(gry.value(3).toString());
         ui->lineEdit_modifier_PrixU->setText(gry.value(4).toString());
         ui->lineEdit_modifier_quantite->setText(gry.value(5).toString());

        }
    }
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

