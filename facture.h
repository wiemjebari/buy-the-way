#ifndef FACTURE_H
#define FACTURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>


class Facture
{public:
    Facture();
    Facture(int,int,QString,QString,int,QString);
    int get_Ref_Facture();
    int get_ID_Commande();
    int get_montant();
    QString get_description();
    QString get_date();
    QString get_etat();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_recherche(QString);
    bool supprimer(int);
    bool modifier_facture(int,int,QString,QString,int,QString);
    QSqlQueryModel * afficher_tri_date();
    QSqlQueryModel * afficher_tri_ref();
    QSqlQueryModel * afficher_tri_etat();

private:
   int Ref_Facture, ID_Commande, montant;
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

namespace Ui {
class facture;
}
class QSerialPort;

class facture : public QDialog
{
    Q_OBJECT

public:
    explicit facture(QWidget *parent = nullptr);
    ~facture();
    void comboBox_commandeMarque();
    void comboBox_5Marque();

private slots:

    void on_pb_modifier_command_clicked();

    void on_pb_supprime_5_clicked();

    void on_pb_ajouter_factur_clicked();

    void on_pushButton_modifier_factur_clicked();

    void on_pb_supprime_facture_clicked();

    void on_Commander_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_lineEdit_Reference_12_textChanged(const QString &arg1);

    void on_lineEdit_modifierID_commande_textChanged(const QString &arg1);

    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_tableView_2_activated(const QModelIndex &index);

    void on_tableView_3_activated(const QModelIndex &index);

    void on_lineEdit_recherch_commande_textChanged(const QString &arg1);
    void  on_lineEdit_recherch_textChanged(const QString &arg1);

private:
    Ui::facture *ui;
    Facture tmpFacture;
    Commande tmpCommande;
    QSerialPort *arduino;

};

#endif // FACTURE_H
