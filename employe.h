#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QDialog>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlRecord>



class ge
{
public:
    ge();
    ge(long,QString,QString,QString);
    long get_CIN();
    QString get_NOM();
    QString get_PRENOM();
    QString get_Poste();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2(QString);
    bool supprimer(long);
    void recherche();
    bool modifier();
    bool verifier_compte(QString identifiant, QString mdp);
    int verifier_statut(QString identifiant,QString mdp);
private:
QString nom,prenom,poste;
long CIN;
};

namespace Ui {
class employe;
}

class employe : public QDialog
{
    Q_OBJECT

public:
    explicit employe(QWidget *parent = nullptr);
    ~employe();
private slots:
    void on_pb_ajouter_clicked();


    void on_pb_supprimer_clicked();

    void on_pb_recherche_clicked();

    void on_pb_modifier_clicked();

    void on_pushButton_clicked();

private:
    Ui::employe *ui;
    ge tmpemploye;
};

#endif // EMPLOYE_H
