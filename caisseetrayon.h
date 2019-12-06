#ifndef CAISSEETRAYON_H
#define CAISSEETRAYON_H
#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include<QSound>
#include "fournisseuretstocks.h"
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

    void calculer_prix(int);
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
namespace Ui {
class caisseetrayon;
}

class caisseetrayon : public QDialog
{
    Q_OBJECT

public:
    explicit caisseetrayon(QWidget *parent = nullptr);
    ~caisseetrayon();
private slots:
    void on_pushButton_Ajouter_c_clicked();

    void on_pushButton_Supprimer_c_clicked();

    void on_pushButton_Ajouter_r_clicked();

    void on_pushButton_Supprimer_r_clicked();

    void on_pushButton_Modifier_c_clicked();

    void on_pushButton_Modifier_r_clicked();

    void on_pushButton_Ajouter_t_clicked();

    void on_pushButton_supprimer_t_clicked();

    void on_pushButton_Ajouter_t_4_clicked();

    void on_pushButton_recherche_clicked();

    void on_pushButton_recherche_3_clicked();

    void on_pushButton_recherche_4_clicked();

    void on_pushButton_recherche_5_clicked();

    void on_pushButton_recherche_2_clicked();

private:
    Ui::caisseetrayon *ui;
    QSound *son;
    Caisse tmpcaisse;
    Rayon tmprayon;
    produit tmpproduit;
    Produit_vendue tmpproduit_v;
    Ticket_caisse tmpticket;
};


#endif // CAISSEETRAYON_H
