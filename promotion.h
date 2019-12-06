#ifndef PROMOTION_H
#define PROMOTION_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
namespace Ui {
class promotion;
}

class promotion
{public:
    promotion();
    promotion(int,QString,int,int);
    QString get_article();
    QSqlQueryModel * afficher2();
    QSqlQueryModel * afficher3(QString);
    QSqlQueryModel * recherchea(QString);

    int get_id();
    int get_quantite();
    int get_prix();




    bool ajouter();
    QSqlQueryModel * afficher();

bool supprimer(int);
bool modifier(int ,QString ,int ,int );

private:

    int id,quantite,prix;
    QString article;
};

class Promotion : public QDialog
{
    Q_OBJECT

public:
    explicit Promotion(QWidget *parent = nullptr);
    ~Promotion();
   void comboboxMarque();
private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();


   void on_pb_modifier_clicked();

   void on_pushButton_clicked();


   void on_pushButton_2_clicked();

   void on_lineEditida_textChanged(const QString &arg1);


private:
    Ui::promotion *ui;
    promotion tmppromotion;
};

#endif // PROMOTION_H
