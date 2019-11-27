#ifndef FACTURE_H
#define FACTURE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Facture
{public:
    Facture();
    Facture(int,int,QString,QString,float,QString);
    int get_Ref_Facture();
    int get_ID_Commande();
    int get_montant();
    QString get_description();
    QString get_date();
    QString get_etat();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_recherche(QString);
    QSqlQueryModel * afficher_tri_date();
    QSqlQueryModel * afficher_tri_ref();
    QSqlQueryModel * afficher_tri_etat();
    bool supprimer(int);
    bool modifier_facture(int,int,QString,QString,float,QString);
private:
   int Ref_Facture, ID_Commande;
   float montant;
   QString description,etat,date;
};
class Commande
{public:
    Commande();
    Commande(int,int,QString,QString,float,int);
    QString get_Categorie();
    QString get_Produit();
    int get_ID_Commande();
    int get_ID_Founisseur();
    int get_Quantite();
    float get_Prix();
    //float get_Total();
    bool ajouter_commande();
    QSqlQueryModel * afficher();
    bool supprimer_commande(int);
    bool modifier_commande(int,int,QString,QString,float,int);
    bool rechercher_commande(int);
    QSqlQueryModel * afficher_recherche(QString);
    QSqlQueryModel * afficher_tri_ref();
    QSqlQueryModel * afficher_tri_categorie();
    QSqlQueryModel * afficher_tri_quantite();

private:
    QString CategorieP,Produit;
    int ID_Commande,ID_Fournisseur,Quantite;
    float PrixU;
};

#endif // FACTURE_H
