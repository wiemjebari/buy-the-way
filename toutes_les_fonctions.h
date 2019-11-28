#ifndef TOUTES_LES_FONCTIONS_H
#define TOUTES_LES_FONCTIONS_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>


class Caisse
{
private:
    int ID_Caisse;
    QString Etat_Caisse;
public:
    Caisse();
    Caisse(int,QString);
    bool Ajouter();
    bool Supprimer(int);
    QSqlQueryModel * Afficher();
    QSqlQueryModel * Afficher_recherche(QString);
    bool Modifier(int,QString);

    int get_ID(){return ID_Caisse;}
    QString get_Etat(){return  Etat_Caisse;}

};
////////////////////////////////////////////////////////////////////

class Produit
{
protected:
    int ID;
    QString Nom;
    int Quantitee;
    float Prix;
    QString DLE;

    int Num_rayon;

public:
    Produit();
    Produit(int,QString,int,float,QString,int);

    int get_ID(){return ID;}

    QString get_Nom(){return Nom;}
    void set_Nom(QString n){Nom = n;}

    int get_Quantitee(){return Quantitee;}
    void set_Quantitee(int q){Quantitee = q;}

    float get_Prix(){return Prix;}

    int get_NUM(){return Num_rayon;}

    bool Ajouter();
    bool Supprimer(int);
    QSqlQueryModel * Afficher();
    QSqlQueryModel * Afficher_recherche(QString);
    bool Modifier(int,QString,int,float,QString,int);
    float Prix_DB_PV(int,int);
    int Decrementer_quantitee_produit(int,int);
    bool Mise_a_jour_Qantitee(int,int);
};
///////////////////////////////////////////////////////////////////////////

class Produit_vendue
{
    int ID;
    int Quantitee;
    int Num;

    int Prix;
public:
    Produit_vendue();
    Produit_vendue(int,int,int);
    bool Ajouter_PV();
    bool Supprimer_PV(int);
    QSqlQueryModel * Afficher_PV();
    QSqlQueryModel * Afficher_PV_recherche(QString);


    int get_Prix(){return Prix;}
};
////////////////////////////////////////////////////////////////////////////////

class Rayon
{
private:
    int Num_rayon;
    QString Type;
public:
    Rayon();
    Rayon(int,QString);
    bool Ajouter();
    bool Supprimer(int);
    QSqlQueryModel * Afficher();
    QSqlQueryModel * Afficher_recherche(QString);
    bool Modifier(int,QString);

    int get_Num(){return Num_rayon;}
    QString get_Type(){return  Type;}
};
/////////////////////////////////////////////////////////////////////////////////////

class Ticket_caisse
{
    int Num;
    QString Date;
    float totale;
public:
    Ticket_caisse();
    Ticket_caisse(int,QString);
    bool Ajouter();
    bool Supprimer(int);
    QSqlQueryModel * Afficher();
    QSqlQueryModel * Afficher_recherche(QString);

    int get_Num(){return Num;}
    float calculer_prix(int,int,int);
    bool Mettre_a_jour_Ticket(int,int,int);
};
/////////////////////////////////////////////////////////////////////////////////////////////

#endif // TOUTES_LES_FONCTIONS_H
