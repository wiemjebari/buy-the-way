#ifndef GE_H
#define GE_H
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
private:
QString nom,prenom,poste;
long CIN;
};



#endif // GE_H
