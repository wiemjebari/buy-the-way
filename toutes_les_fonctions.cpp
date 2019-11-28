#include "toutes_les_fonctions.h"
#include <QSqlError>

#include <QDebug>

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
/////////////////////////////////////////////////////////////////////////////////

Produit::Produit()
{
    ID = 0;
    Nom = "";
    Quantitee = 0;
    Prix = 0;
    DLE = "";
    Num_rayon = 0;
}



Produit::Produit(int ID,QString Nom,int Quantitee,float Prix,QString DLE,int Num_rayon)
{
    this->ID = ID;
    this->Nom = Nom;
    this->Quantitee = Quantitee;
    this->Prix = Prix;
    this->DLE = DLE;
    this->Num_rayon = Num_rayon;
}



bool Produit::Ajouter()
{
    QSqlQuery query;
    QString res= QString::number(ID);
    QString res1= QString::number(Quantitee);
    QString res2= QString::number(Prix);
    QString res3= QString::number(Num_rayon);
    query.prepare("INSERT INTO produit (ID, NOM, QUANTITEE, PRIX, DLE,NUM) "
                        "VALUES (:id, :nom, :quantitee, :prix, :dle, :num)");
    query.bindValue(":id", res);
    query.bindValue(":nom", Nom);
    query.bindValue(":quantitee", res1);
    query.bindValue(":prix", res2);
    query.bindValue(":dle", DLE);
    query.bindValue(":num",res3);

    return    query.exec();
}

bool Produit::Supprimer(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("Delete from produit where ID = :id ");
    query.bindValue(":id", res);
    return    query.exec();
}

QSqlQueryModel * Produit::Afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from produit order by ID asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantitee"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DLE"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Num_rayon"));
    return model;
}



bool Produit::Modifier(int idd,QString nom,int qant,float prix,QString dlee,int num)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    QString res1= QString::number(qant);
    QString res2= QString::number(prix);
    QString res3= QString::number(num);
    query.prepare("UPDATE produit SET NOM = :nom,QUANTITEE= :quantitee,PRIX = :prix,DLE = :dle,NUM = :num WHERE(ID = :id)");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":quantitee", res1);
    query.bindValue(":prix", res2);
    query.bindValue(":dle", dlee);
    query.bindValue(":num",res3);
    return    query.exec();
}

QSqlQueryModel * Produit::Afficher_recherche(QString idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from produit where ID = '"+idd+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantitee"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DLE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Num_rayon"));
        return model;
}

float Produit::Prix_DB_PV(int idd,int qant)
{

    QSqlQueryModel q;
    q.setQuery("select * from produit");
    float P;


        for (int i = 0; i < q.rowCount(); i++) {
            int id = q.record(i).value("ID").toInt();
            if(id == idd)
            {
                P = q.record(i).value("PRIX").toFloat() * qant;
                break;
            }
            else
            {
                P = 0;
            }
        }





    return P;
}

int Produit::Decrementer_quantitee_produit(int idd,int qant)
{
    QSqlQueryModel q;
    q.setQuery("select * from produit");


    int quant;
    for (int i = 0; i < q.rowCount(); i++) {
        int id = q.record(i).value("ID").toInt();
        if(id == idd)
        {
            quant = q.record(i).value("QUANTITEE").toInt() - qant;
            break;
        }
        else
        {
            quant = 0;
        }
    }


    return quant;
}

bool Produit::Mise_a_jour_Qantitee(int idd,int q)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    QString res1= QString::number(Decrementer_quantitee_produit(idd,q));
    query.prepare("UPDATE produit SET QUANTITEE= :quantitee WHERE(ID = :id)");
    query.bindValue(":id", res);
    query.bindValue(":quantitee", res1);
    return    query.exec();
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

    totale = 0;
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
    Produit p;

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
