#ifndef FOURNISSEURETSTOCKS_H
#define FOURNISSEURETSTOCKS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <QMediaPlayer>
class fournisseur
{
public:
    fournisseur();
    fournisseur(int,int,QString,QString);
    QString get_email();
    QString get_produit();
    int get_telephone();
    int get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modification (int,int,QString,QString);
    QSqlQueryModel * Afficher_recherche(QString idd);



private:
    QString email,produitvendu;
    int id,telephone;
};
class produit
{
public:
    produit();
    produit(int,double,QString);
    QString get_nom();
    int get_id();
    double get_prix();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifierProduit(int,double,QString);
    QSqlQueryModel * Afficher_recherche(QString idd);
private:
    QString marque;
    int id;
    double prix;
};

namespace Ui {
class fournisseuretstocks;
}

class fournisseuretstocks : public QDialog
{
    Q_OBJECT

public:
    explicit fournisseuretstocks(QWidget *parent = nullptr);
    ~fournisseuretstocks();
        bool controleEmail(QString);
        bool controlenum(int test);
        QMediaPlayer* player;

private slots:
    void on_pushButton_ajout_clicked();

    void on_pushButton_modif_clicked();


    void on_buttonBox_2_accepted();

    void on_pushButton_ajout_2_clicked();

    void on_pushButton_modif_2_clicked();

    void on_buttonBox_3_accepted();



 void on_buttonBox_4_accepted();

 void on_buttonBox_accepted();


 void on_pushButton_3_clicked();

 void on_pushButton_4_clicked();

 void on_pushButton_5_clicked();

private:
    Ui::fournisseuretstocks *ui;
    fournisseur tmpfournisseur;
    produit tmpstocks;
};



#endif // FOURNISSEURETSTOCKS_H
