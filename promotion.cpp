#include "promotion.h"
#include "ui_promotion.h"
#include "promotion.h"
#include <QDebug>
#include <QMessageBox>
Promotion::Promotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::promotion)
{
    ui->setupUi(this);
    ui->tabpromotion->setModel(tmppromotion.afficher());
    comboboxMarque();
}

Promotion::~Promotion()
{
    delete ui;
}


promotion::promotion()
{
id=0;
article="";
quantite=0;
prix=0;

}
promotion::promotion(int id,QString article,int quantite,int prix)
{
 this->id=id;
 this->article=article;
 this->quantite=quantite;
 this->prix=prix;



}

QString promotion::get_article(){return article;}

int promotion::get_id(){return id;}
int promotion::get_quantite(){return quantite;}
int promotion::get_prix(){return prix;}


bool promotion::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO promotion (id, article, quantite,prix) "
                   "VALUES (:id, :article, :quantite, :prix)");
query.bindValue(":id", res);
query.bindValue(":article", article);
query.bindValue(":quantite", quantite);
query.bindValue(":prix", prix);
return    query.exec();
}

QSqlQueryModel *promotion::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from promotion");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("article "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));

   return model;
}
QSqlQueryModel *promotion::afficher2()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from promotion ORDER BY quantite   ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("article "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));

    return model;
}
QSqlQueryModel *promotion::afficher3(QString id)
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from promotion where id like '"+id+"'   ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("article "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));

    return model;
}
QSqlQueryModel *promotion::recherchea(QString id)
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from promotion where id like '"+id+"%'   ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("article "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));

    return model;
}

bool promotion::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from promotion where id = :id ");
query.bindValue(":id", res);
return    query.exec();
}
bool promotion::modifier(int id,QString article,int quantite,int prix)
{QSqlQuery query;
   QString res= QString::number(id);
   query.prepare("UPDATE promotion SET ARTICLE=:article, QUANTITE=:quantite, PRIX= :prix,  WHERE ID=:id");
   query.bindValue(":id", res);
   query.bindValue(":article", article);
   query.bindValue(":quantite", quantite);
   query.bindValue(":prix", prix);
   return    query.exec();

}
void Promotion::on_pb_ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString article= ui->comboBox->currentText();
    int quantite= ui->lineEdit_quantite->text().toInt();
    int prix= ui->lineEdit_prix->text().toInt();

  promotion e(id,article,quantite,prix);
  bool test=e.ajouter();
  if(test)
{ui->tabpromotion->setModel(tmppromotion.afficher());//refresh

QMessageBox::information(nullptr, QObject::tr("Ajouter une promotion"),
                  QObject::tr("promotion ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une promotion"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void Promotion::on_pb_supprimer_clicked()
{
int id = ui->lineEdit_ids->text().toInt();
bool test=tmppromotion.supprimer(id);
if(test)
{ui->tabpromotion->setModel(tmppromotion.afficher());//refresh

    QMessageBox::information(nullptr, QObject::tr("Supprimer un trajet"),
                QObject::tr("trajet supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un trajet"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}


void Promotion::on_pb_modifier_clicked()
{int id = ui->lineEdit_idm->text().toInt();
    QString article= ui->comboBox->currentText();
    int quantite= ui->lineEdit_quantitem->text().toInt();
    int prix= ui->lineEdit_prixm->text().toInt();

bool test=tmppromotion.modifier(id,article,quantite,prix);

if (test)
  {  ui->tabpromotion->setModel(tmppromotion.afficher());//refresh

QMessageBox::information(nullptr, QObject::tr("modifier un trajet"),
                QObject::tr("trajet modidier.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("modifier un trajet"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
void Promotion::on_pushButton_clicked()
{
    ui->tabletrie->setModel(tmppromotion.afficher2());

}



void Promotion::on_pushButton_2_clicked()
{
    QString id = ui->lineEditid->text();
     ui->tablerecherche->setModel(tmppromotion.afficher3(id));
}


void Promotion::on_lineEditida_textChanged(const QString &arg1)
{    QString id = ui->lineEditida->text();
     ui->tableViewav->setModel(tmppromotion.recherchea(id));
}

void Promotion::comboboxMarque()
{
    QSqlQuery query;
    query.prepare("select MARQUE from produit");
    query.exec();
    QSqlQueryModel *modal =new QSqlQueryModel();
    modal->setQuery(query);
    qDebug()<<modal->rowCount();
    ui->comboBox->setModel(modal);
    ui->comboBox_2->setModel(modal);

}



