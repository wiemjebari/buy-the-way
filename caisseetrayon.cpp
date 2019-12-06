#include "caisseetrayon.h"
#include "ui_caisseetrayon.h"
#include<fournisseuretstocks.h>
#include<QMessageBox>
#include <QDebug>
caisseetrayon::caisseetrayon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::caisseetrayon)
{
    ui->setupUi(this);
    ui->tableView_c->setModel(tmpcaisse.Afficher());
    ui->tableView_r->setModel(tmprayon.Afficher());
    ui->tableView_aff_t->setModel(tmpticket.Afficher());//refresh
    ui->tableView_p_v->setModel(tmpproduit_v.Afficher_PV());//refresh
    ui->tableView_p->setModel(tmpproduit.afficher());


    ui->comboBox_Type->addItem("Marche frais");
    ui->comboBox_Type->addItem("Alimentaire");
    ui->comboBox_Type->addItem("Hygiene/Beaute");
    ui->comboBox_Type->addItem("Maison/Jardin");
    ui->comboBox_Type->addItem("H.T/Electro");
    ui->comboBox_Type->addItem("Textile");

    ui->comboBox_Type_3->addItem("Marche frais");
    ui->comboBox_Type_3->addItem("Alimentaire");
    ui->comboBox_Type_3->addItem("Hygiene/Beaute");
    ui->comboBox_Type_3->addItem("Maison/Jardin");
    ui->comboBox_Type_3->addItem("H.T/Electro");
    ui->comboBox_Type_3->addItem("Textile");
}

caisseetrayon::~caisseetrayon()
{
    delete ui;
}

Caisse::Caisse()
{
    ID_Caisse = 0;
    Etat_Caisse = "";
}

Caisse::Caisse(int ID_Caisse,QString Etat_Caisse)
{
    this->ID_Caisse = ID_Caisse;
    this->Etat_Caisse = Etat_Caisse;
}

bool Caisse::Ajouter()
{
QSqlQuery query;
QString res= QString::number(ID_Caisse);
query.prepare("INSERT INTO caisse (ID, ETAT) "
                    "VALUES (:id, :etat)");
query.bindValue(":id", res);
query.bindValue(":etat", Etat_Caisse);

return    query.exec();
}

QSqlQueryModel * Caisse::Afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from caisse order by ID asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
    return model;
}


bool Caisse::Supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from caisse where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Caisse::Modifier(int idd,QString etaat)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("UPDATE caisse SET ETAT = :etat WHERE(ID = :id)");
    query.bindValue(":id", res);
    query.bindValue(":etat", etaat);
    return    query.exec();
}

QSqlQueryModel * Caisse::Afficher_recherche(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from caisse where ID = '"+idd+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Etat"));
        return model;
}
///////////////////////////////////////////////////////////////////////////////////////////

Produit_vendue::Produit_vendue()
{
    ID = 0;
    Quantitee = 0;
    Num = 0;
}

Produit_vendue::Produit_vendue(int ID,int Quantitee,int Num)
{
    this->ID = ID;
    this->Quantitee = Quantitee;
    this->Num = Num;
}

bool Produit_vendue::Ajouter_PV()
{

    QSqlQuery query;
    QString res= QString::number(ID);
    QString res1= QString::number(Quantitee);
    QString res2= QString::number(Num);

    query.prepare("INSERT INTO produit_vendue (ID, NUM_TICKET, QUANTITEE) "
                        "VALUES (:id, :num, :quantitee)");
    query.bindValue(":id", res);
    query.bindValue(":quantitee", res1);
    query.bindValue(":num",res2);

    return query.exec();
}

QSqlQueryModel * Produit_vendue::Afficher_PV()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from produit_vendue order by ID asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num_ticket"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantitee"));
    return model;
}

void Produit_vendue::calculer_prix(int idd)
{
    Produit_vendue p;

    QSqlQuery query("SELECT QUANTITEE FORM produit_vendue WHERE ID = :id");
    QSqlRecord rec = query.record();
    QString res= QString::number(idd);
    query.bindValue(":id",res);


}

QSqlQueryModel * Produit_vendue::Afficher_PV_recherche(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from produit_vendue where NUM_TICKET = '"+idd+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num_ticket"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantitee"));
        return model;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

Rayon::Rayon()
{
    Num_rayon = 0;
    Type = "";
}
Rayon::Rayon(int Num_rayon,QString Type)
{
    this->Num_rayon = Num_rayon;
    this->Type = Type;
}

bool Rayon::Ajouter()
{
QSqlQuery query;
QString res= QString::number(Num_rayon);
query.prepare("INSERT INTO rayon (NUM, TYPE) "
                    "VALUES (:num, :type)");
query.bindValue(":num", res);
query.bindValue(":type", Type);

return    query.exec();
}

QSqlQueryModel * Rayon::Afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from rayon order by NUM asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    return model;
}


bool Rayon::Supprimer(int Numm)
{
QSqlQuery query;
QString res= QString::number(Numm);
query.prepare("Delete from rayon where NUM = :num ");
query.bindValue(":num", res);
return    query.exec();
}

bool Rayon::Modifier(int numm,QString typpe)
{
    QSqlQuery query;
    QString res= QString::number(numm);
    query.prepare("UPDATE rayon SET TYPE = :type WHERE(NUM = :num)");
    query.bindValue(":num", res);
    query.bindValue(":type", typpe);
    return    query.exec();
}

QSqlQueryModel * Rayon::Afficher_recherche(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from rayon where NUM = '"+idd+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
        return model;
}
////////////////////////////////////////////////////////////////////////////////////////////////

Ticket_caisse::Ticket_caisse()
{
    Num = 0;
    Date = "";
}

Ticket_caisse::Ticket_caisse(int Num,QString Date)
{
    this->Num = Num;
    this->Date = Date;

    totale = 12;
}

bool Ticket_caisse::Ajouter()
{
    QSqlQuery query;
    QString res= QString::number(Num);
    QString res1= QString::number(totale);

    query.prepare("INSERT INTO ticket (NUM_TICKET, DATE_TICKET,TOTALE) "
                        "VALUES (:num, :date, :totale)");
    query.bindValue(":num", res);
    query.bindValue(":date", Date);
    query.bindValue(":totale", res1);

    return    query.exec();
}

QSqlQueryModel * Ticket_caisse::Afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from ticket order by NUM_TICKET asc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_ticket"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date_ticket"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Totale"));
        return model;
}

bool Ticket_caisse::Supprimer(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    QString res1= QString::number(totale);

    query.prepare("Delete from ticket where NUM_TICKET = :num ");
    query.bindValue(":num", res);
    return    query.exec();
}

QSqlQueryModel * Ticket_caisse::Afficher_recherche(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from ticket where NUM_TICKET = '"+idd+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_ticket"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date_ticket"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Totale"));
        return model;
}
float Ticket_caisse::calculer_prix(int idd,int numm,int qant)
{
    produit p;
    float t;

    QSqlQueryModel q;
    q.setQuery("select * from ticket");



    for (int i = 0; i < q.rowCount(); i++) {
        int id = q.record(i).value("NUM_TICKET").toInt();
        if(id == numm)
        {
            t = q.record(i).value("TOTALE").toFloat() + p.Prix_DB_PV(idd,qant);
            break;
        }
        else
        {
            t = 0;
        }
    }
   return t;
}

bool Ticket_caisse::Mettre_a_jour_Ticket(int idd,int numm,int qant)
{
    QSqlQuery query;
    QString res= QString::number(numm);
    QString res1= QString::number(calculer_prix(idd,numm,qant));
    query.prepare("UPDATE ticket SET TOTALE = :totale WHERE(NUM_TICKET = :num)");
    query.bindValue(":num", res);
    query.bindValue(":totale", res1);
    return    query.exec();
}
//////////////////////////////////////////////////////////////////////////////////////////
void caisseetrayon::on_pushButton_Ajouter_c_clicked()
{
    int id = ui->lineEdit_ID->text().toInt();
    QString etat;
    if(ui->radioButton_fonc_2->isChecked())
    {
        etat= ui->radioButton_fonc_2->text();
    }
    else if(ui->radioButton_rep_2->isChecked())
    {
        etat= ui->radioButton_rep_2->text();
    }
    else if(ui->radioButton_panne_2->isChecked())
    {
        etat= ui->radioButton_panne_2->text();
    }

    Caisse c(id,etat);

    bool test=c.Ajouter();
    if(test)
    {
        ui->tableView_c->setModel(tmpcaisse.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter une caisse"),
                  QObject::tr("Caisse ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une caisse"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void caisseetrayon::on_pushButton_Supprimer_c_clicked()
{
    int id = ui->lineEdit_ID_s->text().toInt();
    bool test=tmpcaisse.Supprimer(id);
    if(test)
    {ui->tableView_c->setModel(tmpcaisse.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une caisse"),
                    QObject::tr("Caisse supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une caisse"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}
void caisseetrayon::on_pushButton_Modifier_c_clicked()
{
    int id = ui->lineEdit_ID_2->text().toInt();
    QString etat;
    if(ui->radioButton_fonc->isChecked())
    {
        etat= ui->radioButton_fonc->text();
    }
    else if(ui->radioButton_rep->isChecked())
    {
        etat= ui->radioButton_rep->text();
    }
    else if(ui->radioButton_panne->isChecked())
    {
        etat= ui->radioButton_panne->text();
    }

    bool test=tmpcaisse.Modifier(id,etat);
    if(test)
    {ui->tableView_c->setModel(tmpcaisse.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier une caisse"),
                    QObject::tr("Caisse modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une caisse"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void caisseetrayon::on_pushButton_Ajouter_r_clicked()
{
    int id = ui->lineEdit_Num->text().toInt();
    QString type= ui->comboBox_Type->currentText();

    Rayon r(id,type);
    bool test=r.Ajouter();
    if(test)
    {
        ui->tableView_r->setModel(tmprayon.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un rayon"),
                  QObject::tr("Rayon ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un rayon"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void caisseetrayon::on_pushButton_Supprimer_r_clicked()
{
    int id = ui->lineEdit_Num_s->text().toInt();
    bool test=tmprayon.Supprimer(id);
    if(test)
    {ui->tableView_r->setModel(tmprayon.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un rayon"),
                    QObject::tr("Rayon supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un rayon"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void caisseetrayon::on_pushButton_Modifier_r_clicked()
{
    int id = ui->lineEdit_Num_3->text().toInt();
    QString type= ui->comboBox_Type_3->currentText();
    bool test=tmprayon.Modifier(id,type);
    if(test)
    {ui->tableView_r->setModel(tmprayon.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un rayon"),
                    QObject::tr("Rayon modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un rayon"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void caisseetrayon::on_pushButton_Ajouter_t_clicked()
{
    int num = ui->lineEdit_ID_t->text().toInt();
    QString date= ui->lineEdit_Date->text();

    Ticket_caisse t(num,date);
    bool test = t.Ajouter();


    if(test)
    {
        ui->tableView_aff_t->setModel(tmpticket.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un ticket"),
                  QObject::tr("ticket ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un ticket"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void caisseetrayon::on_pushButton_supprimer_t_clicked()
{
    int id = ui->lineEdit_IDt_s->text().toInt();
    bool test=tmpticket.Supprimer(id);
    if(test)
    {ui->tableView_aff_t->setModel(tmpticket.Afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un ticket"),
                    QObject::tr("Ticket supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un ticket"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void caisseetrayon::on_pushButton_Ajouter_t_4_clicked()
{
    int id = ui->lineEdit_ID_t_r->text().toInt();
    int idp = ui->lineEdit_p_v_4->text().toInt();
    int quant= ui->lineEdit_quant_t_4->text().toInt();

    Produit_vendue pv(idp,quant,id);
    bool test = pv.Ajouter_PV();


    if(test)
    {
        ui->tableView_p_v->setModel(tmpproduit_v.Afficher_PV());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un produit au ticket"),
                  QObject::tr("Produit ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un produit au ticket"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    }

    pv.calculer_prix(idp);
}



void caisseetrayon::on_pushButton_recherche_clicked()
{
    QString id= ui->lineEdit_recherche->text();


        ui->tableView_p_v->setModel(tmpproduit_v.Afficher_PV_recherche(id));//refresh
}

void caisseetrayon::on_pushButton_recherche_3_clicked()
{
    QString id= ui->lineEdit_recherche_3->text();


        ui->tableView_c->setModel(tmpcaisse.Afficher_recherche(id));
}

void caisseetrayon::on_pushButton_recherche_4_clicked()
{
    QString id= ui->lineEdit_recherche_4->text();


    ui->tableView_r->setModel(tmprayon.Afficher_recherche(id));
}

void caisseetrayon::on_pushButton_recherche_5_clicked()
{
    QString id= ui->lineEdit_recherche_5->text();


    ui->tableView_aff_t->setModel(tmpticket.Afficher_recherche(id));
}





void caisseetrayon::on_pushButton_recherche_2_clicked()
{     produit p;
      QString id= ui->lineEdit_recherche_2->text();
      ui->tableView_p->setModel(tmpproduit.afficher());
      ui->tableView_p->setModel(tmpproduit.Afficher_recherche(id));
}
